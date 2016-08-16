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
static Standard_Integer AddVertex(Handle(WfObjMesh_Mesh) &mesh,
                                  BRepBuilderAPI_CellFilter &filter,
                                  BRepBuilderAPI_VertexInspector &inspector,
                                  const gp_XYZ &p) {
    Standard_Integer index;
    inspector.SetCurrent(p);
    gp_XYZ minp = inspector.Shift(p, -Precision::Confusion());
    gp_XYZ maxp = inspector.Shift(p, +Precision::Confusion());
    filter.Inspect(minp, maxp, inspector);
    const TColStd_ListOfInteger &indices = inspector.ResInd();
    if (indices.IsEmpty() == Standard_False) {
        index = indices.First(); // it should be only one
        inspector.ClearResList();
    } else {
        index = mesh->AddVertex(p.X(), p.Y(), p.Z());
        filter.Add(index, p);
        inspector.Add(p);
    }
    return index;
}

// constants
static const size_t HEADER_SIZE = 84;
static const size_t SIZEOF_STL_FACET = 50;
static const size_t STL_MIN_FILE_SIZE = 284;
static const size_t ASCII_LINES_PER_FACET = 7;

static const int IND_THRESHOLD = 1000; // increment the indicator every 1k triangles

//=======================================================================
//function : WriteInteger
//purpose  : writing a Little Endian 32 bits integer
//=======================================================================

inline static void WriteInteger(OSD_File &ofile, const Standard_Integer value) {
    union {
        Standard_Integer i;// don't be afraid, this is just an unsigned int
        char c[4];
    } bidargum;

    bidargum.i = value;

    Standard_Integer entier;

    entier = bidargum.c[0] & 0xFF;
    entier |= (bidargum.c[1] & 0xFF) << 0x08;
    entier |= (bidargum.c[2] & 0xFF) << 0x10;
    entier |= (bidargum.c[3] & 0xFF) << 0x18;

    ofile.Write((char *) &entier, sizeof(bidargum.c));
}

//=======================================================================
//function : WriteDouble2Float
//purpose  : writing a Little Endian 32 bits float
//=======================================================================

inline static void WriteDouble2Float(OSD_File &ofile, Standard_Real value) {
    union {
        Standard_ShortReal f;
        char c[4];
    } bidargum;

    bidargum.f = (Standard_ShortReal) value;

    Standard_Integer entier;

    entier = bidargum.c[0] & 0xFF;
    entier |= (bidargum.c[1] & 0xFF) << 0x08;
    entier |= (bidargum.c[2] & 0xFF) << 0x10;
    entier |= (bidargum.c[3] & 0xFF) << 0x18;

    ofile.Write((char *) &entier, sizeof(bidargum.c));
}


//=======================================================================
//function : readFloat2Double
//purpose  : reading a Little Endian 32 bits float
//=======================================================================

inline static Standard_Real ReadFloat2Double(OSD_File &aFile) {
    union {
        Standard_Integer i;// don't be afraid, this is just an unsigned int
        Standard_ShortReal f;
    } bidargum;

    char c[4];
    Standard_Address adr;
    adr = (Standard_Address) c;
    Standard_Integer lread;
    aFile.Read(adr, 4, lread);
    bidargum.i = c[0] & 0xFF;
    bidargum.i |= (c[1] & 0xFF) << 0x08;
    bidargum.i |= (c[2] & 0xFF) << 0x10;
    bidargum.i |= (c[3] & 0xFF) << 0x18;

    return (Standard_Real) (bidargum.f);
}

//=======================================================================
//function : WriteAscii
//purpose  : write an ASCII STL file
//=======================================================================

Standard_Boolean RWWfObj::WriteFile(const Handle(WfObjMesh_Mesh) &theMesh,
                                    const OSD_Path &thePath,
                                    const Handle(Message_ProgressIndicator) &theProgInd) {
    OSD_File theFile(thePath);
    theFile.Build(OSD_WriteOnly, OSD_Protection());
    TCollection_AsciiString buf("# OCC Mesh\n");
    theFile.Write(buf, buf.Length());
    buf.Clear();

    Standard_Real x1, y1, z1;
    Standard_Real x2, y2, z2;
    Standard_Real x3, y3, z3;
    char sval[512];

    // create progress sentry for domains
    Standard_Integer aNbDomains = theMesh->NbDomains();
    Message_ProgressSentry aDPS(theProgInd, "Mesh domains", 0, aNbDomains, 1);
    WfObjMesh_MeshExplorer aMexp(theMesh);

    Standard_Integer vertexIndex = 1;
    for (Standard_Integer nbd = 1; nbd <= aNbDomains && aDPS.More(); nbd++, aDPS.Next()) {
        // create progress sentry for triangles in domain
        Message_ProgressSentry aTPS(theProgInd, "Triangles", 0,
                                    theMesh->NbTriangles(nbd), IND_THRESHOLD);
        Standard_Integer aTriangleInd = 0;

        for (aMexp.InitTriangle(nbd); aMexp.MoreTriangle(); aMexp.NextTriangle()) {
            aMexp.TriangleVertices(x1, y1, z1, x2, y2, z2, x3, y3, z3);

            Sprintf(sval, "v %12e %12e %12e\n", x1, y1, z1);
            buf += sval;

            Sprintf(sval, "v %12e %12e %12e\n", x2, y2, z2);
            buf += sval;

            Sprintf(sval, "v %12e %12e %12e\n", x3, y3, z3);
            buf += sval;

            theFile.Write(buf, buf.Length());
            buf.Clear();

            Sprintf(sval, "f %d %d %d\n", vertexIndex, vertexIndex + 1, vertexIndex + 2);
            buf += sval;
            theFile.Write(buf, buf.Length());
            buf.Clear();

            vertexIndex += 3;

            // update progress only per 1k triangles
            if (++aTriangleInd % IND_THRESHOLD == 0) {
                if (!aTPS.More())
                    break;
                aTPS.Next();
            }
        }
    }

    theFile.Close();
    Standard_Boolean isInterrupted = !aDPS.More();
    return !isInterrupted;
}
//=======================================================================
//function : ReadFile
//Design   :
//Warning  :
//=======================================================================

Handle(WfObjMesh_Mesh) RWWfObj::ReadFile(const OSD_Path &thePath,
                                         const Handle(Message_ProgressIndicator) &theProgInd) {
    TCollection_AsciiString filename;
    long ipos;
    Standard_Integer nbLines = 0;
    Standard_Integer nbTris = 0;
    Standard_Integer nbPolys = 0;
    Standard_Integer nbVertices = 0;
    Standard_Integer iTri;
    Standard_Integer i1, i2, i3;
    Handle(WfObjMesh_Mesh) ReadMesh;

    thePath.SystemName(filename);

    // Open the file
    FILE *file = OSD_OpenFile(filename.ToCString(), "r");

    fseek(file, 0L, SEEK_END);

    long filesize = ftell(file);

    rewind(file);

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read;
    while ((read = getline(&line, &line_len, file)) != -1) {
        if (read < 3) continue;
        if (line[0] == 'f') {
            nbPolys++;
        }
        if (strncmp(line, "v ", 2) == 0) {
            nbVertices ++;
        }
    }

    // go back to the beginning of the file
    rewind(file);

#ifdef OCCT_DEBUG
    cout << "start mesh\n";
    cout << "nbPolys : " << nbPolys << std::endl;
    cout << "nbVertices : " << nbVertices << std::endl;
#endif
    int * vindex = (int *) calloc(nbVertices, sizeof(vindex[0]));

    ReadMesh = new WfObjMesh_Mesh();
    ReadMesh->AddDomain();

    // Filter unique vertices to share the nodes of the mesh.
    BRepBuilderAPI_CellFilter uniqueVertices(Precision::Confusion());
    BRepBuilderAPI_VertexInspector inspector(Precision::Confusion());

    int vcount = 0;
    int fcount = 0;
    Message_ProgressSentry aPS (theProgInd, "Polygons", 0, (nbPolys - 1) * 1.0 / IND_THRESHOLD, 1);
    while ((read = getline(&line, &line_len, file)) != -1 && aPS.More()) {
        if (read < 2) continue;

        // Skip comments
        if (line[0] == '#') {
//            fprintf(stderr, "%s", line);
            continue;
        }

        if (strncmp(line, "v ", 2) == 0) {
            char x[256] = "", y[256] = "", z[256] = "";
            if (sscanf(line, "v %80s %80s %80s\n", x, y, z) != 3) {
                continue;
            }

            gp_XYZ aV(Atof(x), Atof(y), Atof(z));
            int i = AddVertex(ReadMesh, uniqueVertices, inspector, aV);
            vindex[vcount] = i;
            vcount ++;
            continue;
        }

        if (strncmp(line, "f ", 2) == 0) {
            Standard_Integer vertex_list[256];
            Standard_Integer vertex_count = 0;
            char * cp = line + 2;
            while (* cp != '\n') {
                int vi = atoi(cp);
                vi = vi - 1; // Fix start index from 1 to 0
                vertex_list[vertex_count ++] = vindex[vi];

                // Skip over rest of v/n/t
                while (* cp && * cp != ' ') cp ++;
                // Skip over blank spaces
                while (* cp && (*cp == ' ' || *cp == '\n' || *cp == '\r')) cp ++;
                if (* cp == 0) break;
            }
            gp_XYZ aN (0, 0, 0);
            ReadMesh->AddPolygon (vertex_count, vertex_list, aN.X(), aN.Y(), aN.Z());

            if (++fcount % IND_THRESHOLD == 0) aPS.Next();
            continue;
        }
    }

    free(vindex);
    fclose(file);
    free(line);

#ifdef OCCT_DEBUG
    cout << "end mesh\n";
#endif
   return ReadMesh;
}
