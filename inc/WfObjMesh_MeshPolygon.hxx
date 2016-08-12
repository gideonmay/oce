//
// Created by gideon may on 12/08/16.
//

#ifndef OCE_WFOBJMESH_MESHPOLYGON_HXX_H
#define OCE_WFOBJMESH_MESHPOLYGON_HXX_H

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_WfObjMesh_MeshPolygon.hxx>

#include <Standard_Integer.hxx>
#include <Standard_Real.hxx>
#include <MMgt_TShared.hxx>
class Standard_NegativeValue;


//! A  mesh polygon is defined with
//! three or more geometric vertices and an orientation
class WfObjMesh_MeshPolygon : public MMgt_TShared
{

public:
    static const int WFOBJ_POLYGON_MAX_VERTICES=20;

    //! empty constructor
    Standard_EXPORT WfObjMesh_MeshPolygon();

    Standard_EXPORT WfObjMesh_MeshPolygon(const Standard_Integer VertexCount, const Standard_Integer * VertexList, const Standard_Real Xn, const Standard_Real Yn, const Standard_Real Zn);

    //! Add a new vertex index
    //! Raised if Vertex count is larger than WFOBJ_POLYGON_MAX_VERTICES or V is lower than zero
    Standard_EXPORT   void AddVertex(const Standard_Integer V);

    Standard_EXPORT   Standard_Integer GetVertexCount() const;

    Standard_EXPORT   Standard_Integer GetVertex(Standard_Integer idx) const;

    Standard_EXPORT   void SetOrientation( const Standard_Real Xn, const Standard_Real Yn, const Standard_Real Zn) ;

    Standard_EXPORT   void GetOrientation(  Standard_Real& Xn,  Standard_Real& Yn,  Standard_Real& Zn) const;

    DEFINE_STANDARD_RTTI(WfObjMesh_MeshPolygon)

protected:




private:

    Standard_Integer MyVertexCount;
    Standard_Integer MyVertices[WFOBJ_POLYGON_MAX_VERTICES];

    Standard_Real MyXn;
    Standard_Real MyYn;
    Standard_Real MyZn;
};

#endif //OCE_WFOBJMESH_MESHPOLYGON_HXX_H
