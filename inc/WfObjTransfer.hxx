#ifndef _WfObjTransfer_HeaderFile
#define _WfObjTransfer_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_Real.hxx>
#include <Standard_Boolean.hxx>
#include <Handle_WfObjMesh_Mesh.hxx>
class TopoDS_Shape;
class WfObjMesh_Mesh;


//! The  package   Algorithm  for Meshing   implements
//! facilities to compute  the Mesh data-structure, as
//! defined in package WfObjMesh, from a shape of package
//! TopoDS.  The triangulation  is  computed  with the
//! Delaunay      algorithm   implemented in   package
//! BRepMesh.  The  result   is  stored  in  the  mesh
//! data-structure Mesh from package WfObjMesh.
class WfObjTransfer 
{
public:

  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static   void BuildIncrementalMesh (const TopoDS_Shape& Shape, const Standard_Real Deflection, const Standard_Boolean InParallel, const Handle(WfObjMesh_Mesh)& Mesh) ;

};

#endif // _WfObjTransfer_HeaderFile
