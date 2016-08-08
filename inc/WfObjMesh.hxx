#ifndef _WfObjMesh_HeaderFile
#define _WfObjMesh_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_WfObjMesh_Mesh.hxx>
class WfObjMesh_Mesh;
class WfObjMesh_Mesh;
class WfObjMesh_MeshExplorer;
class WfObjMesh_MeshDomain;
class WfObjMesh_MeshTriangle;
class WfObjMesh_SequenceOfMeshDomain;
class WfObjMesh_SequenceOfMeshTriangle;
class WfObjMesh_SequenceOfMesh;
class WfObjMesh_SequenceNodeOfSequenceOfMeshDomain;
class WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle;
class WfObjMesh_SequenceNodeOfSequenceOfMesh;


//! Implements a  basic  mesh data-structure  for  the
//! needs of the application fast prototyping.
class WfObjMesh 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Sequence of meshes
  //! Make a merge of two Mesh and returns a new Mesh.
  //! Very useful if you want to merge partMesh and CheckSurfaceMesh
  //! for example
  Standard_EXPORT static   Handle(WfObjMesh_Mesh) Merge (const Handle(WfObjMesh_Mesh)& mesh1, const Handle(WfObjMesh_Mesh)& mesh2) ;

private:

friend class WfObjMesh_Mesh;
friend class WfObjMesh_MeshExplorer;
friend class WfObjMesh_MeshDomain;
friend class WfObjMesh_MeshTriangle;
friend class WfObjMesh_SequenceOfMeshDomain;
friend class WfObjMesh_SequenceOfMeshTriangle;
friend class WfObjMesh_SequenceOfMesh;
friend class WfObjMesh_SequenceNodeOfSequenceOfMeshDomain;
friend class WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle;
friend class WfObjMesh_SequenceNodeOfSequenceOfMesh;

};

#endif // _WfObjMesh_HeaderFile
