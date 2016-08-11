#ifndef _WfObjMesh_MeshExplorer_HeaderFile
#define _WfObjMesh_MeshExplorer_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_WfObjMesh_Mesh.hxx>
#include <Standard_Real.hxx>
#include <Standard_Integer.hxx>
#include <TColgp_SequenceOfXYZ.hxx>
#include <WfObjMesh_SequenceOfMeshTriangle.hxx>
#include <Standard_Boolean.hxx>
class WfObjMesh_Mesh;
class Standard_OutOfRange;
class Standard_NoMoreObject;
class Standard_NoSuchObject;


//! Provides  facilities to explore  the triangles  of
//! each mesh domain.
class WfObjMesh_MeshExplorer 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT WfObjMesh_MeshExplorer(const Handle(WfObjMesh_Mesh)& M);
  
  //! Returns the mesh deflection of the current domain.
  Standard_EXPORT   Standard_Real Deflection()  const;
  
  //! Initializes the exploration  of the  triangles  of
  //! the mesh domain of range <DomainIndex>.
  //! Raised if <DomainIndex> is lower than 1 or greater
  //! than the number of domains.
  Standard_EXPORT   void InitTriangle (const Standard_Integer DomainIndex = 1) ;
  
      Standard_Boolean MoreTriangle()  const;
  
  //! Raised if there is no more triangle in the current
  //! domain.
  Standard_EXPORT   void NextTriangle() ;
  
  //! Raised if there is no more triangle in the current
  //! domain.
  Standard_EXPORT   void TriangleVertices (Standard_Real& X1, Standard_Real& Y1, Standard_Real& Z1, Standard_Real& X2, Standard_Real& Y2, Standard_Real& Z2, Standard_Real& X3, Standard_Real& Y3, Standard_Real& Z3)  const;
  
  //! Raised if there is no more triangle in the current
  //! domain.
  Standard_EXPORT   void TriangleOrientation (Standard_Real& Xn, Standard_Real& Yn, Standard_Real& Zn)  const;




protected:





private:



  Handle(WfObjMesh_Mesh) mesh;
  Standard_Real xn;
  Standard_Real yn;
  Standard_Real zn;
  Standard_Integer v1;
  Standard_Integer v2;
  Standard_Integer v3;
  Standard_Integer domainIndex;
  Standard_Integer nbTriangles;
  Standard_Integer triangleIndex;
  TColgp_SequenceOfXYZ trianglesVertex;
  WfObjMesh_SequenceOfMeshTriangle trianglesdef;


};


#include <WfObjMesh_MeshExplorer.lxx>





#endif // _WfObjMesh_MeshExplorer_HeaderFile
