//
// Created by gideon may on 12/08/16.
//

//=======================================================================

#include <WfObjMesh_MeshPolygon.ixx>
#include <Precision.hxx>
#include <gp_XYZ.hxx>

//=======================================================================
//function : WfObjMesh_MeshPolygon
//design   : 
//warning  : 
//=======================================================================

WfObjMesh_MeshPolygon::WfObjMesh_MeshPolygon()
        : MyVertexCount(0), MyXn (0.0), MyYn (0.0), MyZn (0.0) { }

//=======================================================================
//function : WfObjMesh_MeshPolygon
//design   :
//warning  :
//=======================================================================

WfObjMesh_MeshPolygon::WfObjMesh_MeshPolygon(const Standard_Integer VertexCount,
                                             const Standard_Integer * VertexList,
                                             const Standard_Real Xn, const Standard_Real Yn, const Standard_Real Zn)
        : MyVertexCount(VertexCount), MyXn (Xn), MyYn (Yn), MyZn (Zn)
{
    if (MyVertexCount >= WFOBJ_POLYGON_MAX_VERTICES || MyVertexCount < 0) {
        Standard_Failure::Raise("Too many vertices in WfObjMesh_MeshPolygon");
    }
    for (int v=0; v<MyVertexCount; v++) {
        MyVertices[v] = VertexList[v];
    }
}


//=======================================================================
//function : AddVertex
//design   :
//warning  :
//=======================================================================

void WfObjMesh_MeshPolygon::AddVertex(const Standard_Integer V)
{
    if (MyVertexCount == WFOBJ_POLYGON_MAX_VERTICES -1) {
        Standard_Failure::Raise("Too many vertices in WfObjMesh_MeshPolygon");
    }
    if (V < 0) {
        Standard_Failure::Raise("Vertex id is less than zero in WfObjMesh_MeshPolygon");
    }
    MyVertices[MyVertexCount ++] = V;
}

//=======================================================================
//function : GetVertex
//design   :
//warning  :
//=======================================================================

Standard_Integer WfObjMesh_MeshPolygon::GetVertexCount() const
{
    return MyVertexCount;
}


//=======================================================================
//function : GetVertex
//design   : 
//warning  : 
//=======================================================================

Standard_Integer WfObjMesh_MeshPolygon::GetVertex(Standard_Integer idx) const
{
    return MyVertices[idx];
}

//=======================================================================
//function : SetOrientation
//design   : 
//warning  : 
//=======================================================================

void WfObjMesh_MeshPolygon::SetOrientation(const Standard_Real Xn, const Standard_Real Yn, const Standard_Real Zn)
{
    MyXn = Xn;
    MyYn = Yn;
    MyZn = Zn;
}

//=======================================================================
//function : GetOrientation
//design   : 
//warning  : 
//=======================================================================

void WfObjMesh_MeshPolygon::GetOrientation(  Standard_Real& Xn,  Standard_Real& Yn,  Standard_Real& Zn) const
{
    Xn = MyXn;
    Yn = MyYn;
    Zn = MyZn;
}


