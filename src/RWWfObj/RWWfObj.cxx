#include <RWWfObj.ixx>
#include <OSD_Protection.hxx>
#include <OSD_File.hxx>
#include <Message_ProgressSentry.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_TypeMismatch.hxx>
#include <Precision.hxx>
#include <WfObjMesh_MeshExplorer.hxx>
#include <OSD.hxx>
#include <OSD_Host.hxx>
#include <gp_XYZ.hxx>
#include <gp.hxx>
#include <stdio.h>
#include <gp_Vec.hxx>
#include <OSD_OpenFile.hxx>

#include <BRepBuilderAPI_CellFilter.hxx>
#include <BRepBuilderAPI_VertexInspector.hxx>

// A static method adding nodes to a mesh and keeping coincident (sharing) nodes.
static Standard_Integer AddVertex(Handle(WfObjMesh_Mesh)& mesh,
                                  BRepBuilderAPI_CellFilter& filter, 
                                  BRepBuilderAPI_VertexInspector& inspector,
                                  const gp_XYZ& p)
{
  Standard_Integer index;
  inspector.SetCurrent(p);
  gp_XYZ minp = inspector.Shift(p, -Precision::Confusion());
  gp_XYZ maxp = inspector.Shift(p, +Precision::Confusion());
  filter.Inspect(minp, maxp, inspector);
  const TColStd_ListOfInteger& indices = inspector.ResInd();
  if (indices.IsEmpty() == Standard_False)
  {
    index = indices.First(); // it should be only one
    inspector.ClearResList();
  }
  else
  {
    index = mesh->AddVertex(p.X(), p.Y(), p.Z());
    filter.Add(index, p);
    inspector.Add(p);
  }
  return index;
}

// constants
static const size_t HEADER_SIZE           =  84;
static const size_t SIZEOF_STL_FACET      =  50;
static const size_t STL_MIN_FILE_SIZE     = 284;
static const size_t ASCII_LINES_PER_FACET =   7;

static const int IND_THRESHOLD = 1000; // increment the indicator every 1k triangles

//=======================================================================
//function : WriteInteger
//purpose  : writing a Little Endian 32 bits integer
//=======================================================================

inline static void WriteInteger(OSD_File& ofile,const Standard_Integer value)
{
  union {
    Standard_Integer i;// don't be afraid, this is just an unsigned int
    char c[4];
  } bidargum;

  bidargum.i = value;

  Standard_Integer entier;

  entier  =  bidargum.c[0] & 0xFF;
  entier |= (bidargum.c[1] & 0xFF) << 0x08;
  entier |= (bidargum.c[2] & 0xFF) << 0x10;
  entier |= (bidargum.c[3] & 0xFF) << 0x18;

  ofile.Write((char *)&entier,sizeof(bidargum.c));
}

//=======================================================================
//function : WriteDouble2Float
//purpose  : writing a Little Endian 32 bits float
//=======================================================================

inline static void WriteDouble2Float(OSD_File& ofile,Standard_Real value)
{
  union {
    Standard_ShortReal f;
    char c[4];
  } bidargum;

  bidargum.f = (Standard_ShortReal)value;

  Standard_Integer entier;

  entier  =  bidargum.c[0] & 0xFF;
  entier |= (bidargum.c[1] & 0xFF) << 0x08;
  entier |= (bidargum.c[2] & 0xFF) << 0x10;
  entier |= (bidargum.c[3] & 0xFF) << 0x18;

  ofile.Write((char *)&entier,sizeof(bidargum.c));
}


//=======================================================================
//function : readFloat2Double
//purpose  : reading a Little Endian 32 bits float
//=======================================================================

inline static Standard_Real ReadFloat2Double(OSD_File &aFile)
{
  union {
    Standard_Integer i;// don't be afraid, this is just an unsigned int
    Standard_ShortReal f;
  }bidargum;

  char c[4];
  Standard_Address adr;
  adr = (Standard_Address)c;
  Standard_Integer lread;
  aFile.Read(adr,4,lread);
  bidargum.i  =  c[0] & 0xFF;
  bidargum.i |=  (c[1] & 0xFF) << 0x08;
  bidargum.i |=  (c[2] & 0xFF) << 0x10;
  bidargum.i |=  (c[3] & 0xFF) << 0x18;

  return (Standard_Real)(bidargum.f);
}

//=======================================================================
//function : WriteAscii
//purpose  : write an ASCII STL file
//=======================================================================

Standard_Boolean RWWfObj::WriteFile (const Handle(WfObjMesh_Mesh)& theMesh,
                                    const OSD_Path& thePath,
                                    const Handle(Message_ProgressIndicator)& theProgInd)
{
  OSD_File theFile (thePath);
  theFile.Build(OSD_WriteOnly,OSD_Protection());
  TCollection_AsciiString buf ("solid\n");
  theFile.Write (buf,buf.Length());buf.Clear();

  Standard_Real x1, y1, z1;
  Standard_Real x2, y2, z2;
  Standard_Real x3, y3, z3;
  char sval[512];

  // create progress sentry for domains
  Standard_Integer aNbDomains = theMesh->NbDomains();
  Message_ProgressSentry aDPS (theProgInd, "Mesh domains", 0, aNbDomains, 1);
  WfObjMesh_MeshExplorer aMexp (theMesh);
  for (Standard_Integer nbd = 1; nbd <= aNbDomains && aDPS.More(); nbd++, aDPS.Next())
  {
    // create progress sentry for triangles in domain
    Message_ProgressSentry aTPS (theProgInd, "Triangles", 0,
        theMesh->NbTriangles (nbd), IND_THRESHOLD);
    Standard_Integer aTriangleInd = 0;
    for (aMexp.InitTriangle (nbd); aMexp.MoreTriangle(); aMexp.NextTriangle())
    {
      aMexp.TriangleVertices (x1,y1,z1,x2,y2,z2,x3,y3,z3);

//      Standard_Real x, y, z;
//      aMexp.TriangleOrientation (x,y,z);

      gp_XYZ Vect12 ((x2-x1), (y2-y1), (z2-z1));
      gp_XYZ Vect23 ((x3-x2), (y3-y2), (z3-z2));
      gp_XYZ Vnorm = Vect12 ^ Vect23;
      Standard_Real Vmodul = Vnorm.Modulus ();
      if (Vmodul > gp::Resolution())
      {
        Vnorm.Divide (Vmodul);
      }
      else
      {
        // si Vnorm est quasi-nul, on le charge a 0 explicitement
        Vnorm.SetCoord (0., 0., 0.);
      }
      Sprintf (sval,
          " facet normal % 12e % 12e % 12e\n"
          "   outer loop\n"
          "     vertex % 12e % 12e % 12e\n"
          "     vertex % 12e % 12e % 12e\n"
          "     vertex % 12e % 12e % 12e\n"
          "   endloop\n"
          " endfacet\n",
          Vnorm.X(), Vnorm.Y(), Vnorm.Z(),
          x1, y1, z1,
          x2, y2, z2,
          x3, y3, z3);
      buf += sval;
      theFile.Write (buf, buf.Length()); buf.Clear();

      // update progress only per 1k triangles
      if (++aTriangleInd % IND_THRESHOLD == 0)
      {
        if (!aTPS.More())
            break;
        aTPS.Next();
      }
    }
  }

  buf += "endsolid\n";
  theFile.Write (buf, buf.Length()); buf.Clear();
  theFile.Close();
  Standard_Boolean isInterrupted = !aDPS.More();
  return !isInterrupted;
}
//=======================================================================
//function : ReadFile
//Design   :
//Warning  :
//=======================================================================

Handle(WfObjMesh_Mesh) RWWfObj::ReadFile (const OSD_Path& thePath,
                                     const Handle(Message_ProgressIndicator)& theProgInd)
{
  TCollection_AsciiString filename;
  long ipos;
  Standard_Integer nbLines = 0;
  Standard_Integer nbTris = 0;
  Standard_Integer iTri;
  Standard_Integer i1,i2,i3;
  Handle(WfObjMesh_Mesh) ReadMesh;

  thePath.SystemName (filename);

  // Open the file
  FILE* file = OSD_OpenFile(filename.ToCString(),"r");

  fseek(file,0L,SEEK_END);

  long filesize = ftell(file);

  rewind(file);

  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, file)) != -1 ) {
    printf("Retrieved line of length %zu : \n", read);
    printf("%s", line);
  }

  // count the number of lines
  for (ipos = 0; ipos < filesize; ++ipos) {
	  if (getc(file) == '\n')
        nbLines++;
  }

  // compute number of triangles
  nbTris = (nbLines / ASCII_LINES_PER_FACET);

  // go back to the beginning of the file
  rewind(file);

#ifdef OCCT_DEBUG
  cout << "start mesh\n";
#endif
  ReadMesh = new WfObjMesh_Mesh();
  ReadMesh->AddDomain();

  // Filter unique vertices to share the nodes of the mesh.
  BRepBuilderAPI_CellFilter uniqueVertices(Precision::Confusion());
  BRepBuilderAPI_VertexInspector inspector(Precision::Confusion());

  while (1) {
    char c = getc(file);
    if (c == '\n') continue;
    if (c == ' ') continue;

    // Skip comments
    if (c == '#' ) {
      while (getc(file) != '\n') {}
      continue;
    }
    if (c == 'v') {
      char x[256]="", y[256]="", z[256]="";
      if (3 != fscanf(file, "%80s %80s %80s\n", x, y, z)) {
        break;
      }
      gp_XYZ aV (Atof(x), Atof(y), Atof(z));
      i1 = AddVertex(ReadMesh, uniqueVertices, inspector, aV);
    }
  }



  // main reading
  Message_ProgressSentry aPS (theProgInd, "Triangles", 0, (nbTris - 1) * 1.0 / IND_THRESHOLD, 1);
  for (iTri = 0; iTri < nbTris && aPS.More();)
  {
    char x[256]="", y[256]="", z[256]="";

    // reading the facet normal
    if (3 != fscanf(file,"%*s %*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aN (Atof(x), Atof(y), Atof(z));

    // skip the keywords "outer loop"
    if (0 != fscanf(file,"%*s %*s"))
      break;

    // reading vertex
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV1 (Atof(x), Atof(y), Atof(z));
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV2 (Atof(x), Atof(y), Atof(z));
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV3 (Atof(x), Atof(y), Atof(z));

    // here the facet must be built and put in the mesh datastructure

    i1 = AddVertex(ReadMesh, uniqueVertices, inspector, aV1);
    i2 = AddVertex(ReadMesh, uniqueVertices, inspector, aV2);
    i3 = AddVertex(ReadMesh, uniqueVertices, inspector, aV3);
    ReadMesh->AddTriangle (i1, i2, i3, aN.X(), aN.Y(), aN.Z());

    // skip the keywords "endloop"
    if (0 != fscanf(file,"%*s"))
      break;

    // skip the keywords "endfacet"
    if (0 != fscanf(file,"%*s"))
      break;

    // update progress only per 1k triangles
    if (++iTri % IND_THRESHOLD == 0)
      aPS.Next();
  }
#ifdef OCCT_DEBUG
  cout << "end mesh\n";
#endif
  fclose(file);
  return ReadMesh;
}
