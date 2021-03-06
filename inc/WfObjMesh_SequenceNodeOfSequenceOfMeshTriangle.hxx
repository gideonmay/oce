// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle_HeaderFile
#define _WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle.hxx>

#include <Handle_WfObjMesh_MeshTriangle.hxx>
#include <TCollection_SeqNode.hxx>
#include <TCollection_SeqNodePtr.hxx>
class WfObjMesh_MeshTriangle;
class WfObjMesh_SequenceOfMeshTriangle;

class WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle : public TCollection_SeqNode
{

public:
    WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle(const Handle(WfObjMesh_MeshTriangle)& I, const TCollection_SeqNodePtr& n, const TCollection_SeqNodePtr& p);
  
    Handle(WfObjMesh_MeshTriangle)& Value()  const;

    DEFINE_STANDARD_RTTI(WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle)

private:



  Handle(WfObjMesh_MeshTriangle) myValue;


};

#define SeqItem Handle(WfObjMesh_MeshTriangle)
#define SeqItem_hxx <WfObjMesh_MeshTriangle.hxx>
#define TCollection_SequenceNode WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle
#define TCollection_SequenceNode_hxx <WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle.hxx>
#define Handle_TCollection_SequenceNode Handle_WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle
#define TCollection_SequenceNode_Type_() WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle_Type_()
#define TCollection_Sequence WfObjMesh_SequenceOfMeshTriangle
#define TCollection_Sequence_hxx <WfObjMesh_SequenceOfMeshTriangle.hxx>

#include <TCollection_SequenceNode.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx




#endif // _WfObjMesh_SequenceNodeOfSequenceOfMeshTriangle_HeaderFile
