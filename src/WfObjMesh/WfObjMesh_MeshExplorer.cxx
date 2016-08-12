// Created on: 1995-09-25
// Created by: Philippe GIRODENGO
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//=======================================================================
#include <WfObjMesh_MeshExplorer.ixx>
#include <WfObjMesh_MeshTriangle.hxx>
#include <WfObjMesh_MeshPolygon.hxx>

//=======================================================================
//function : WfObjMesh_MeshExplorer
//design   :
//warning  :
//=======================================================================


WfObjMesh_MeshExplorer::WfObjMesh_MeshExplorer(const Handle(WfObjMesh_Mesh) &M)
        : domainIndex(0), nbTriangles(0), triangleIndex(0),
          nbPolygons(0), polygonIndex(0) { mesh = M; }


//=======================================================================
//function : Deflection
//design   :
//warning  :
//=======================================================================

Standard_Real WfObjMesh_MeshExplorer::Deflection() const { return mesh->Deflection(domainIndex); }


//=======================================================================
//function : InitTriangle
//design   :
//warning  :
//=======================================================================

void WfObjMesh_MeshExplorer::InitTriangle(const Standard_Integer DomainIndex) {
    triangleIndex = 1;
    domainIndex = DomainIndex;
    nbTriangles = mesh->NbTriangles(domainIndex);
    if (nbTriangles > 0) {
        trianglesdef.Assign(mesh->Triangles(DomainIndex));
        trianglesVertex.Assign(mesh->Vertices(DomainIndex));
        const Handle (WfObjMesh_MeshTriangle) trian = trianglesdef.First();
        trian->GetVertexAndOrientation(v1, v2, v3, xn, yn, zn);
    }
}

//=======================================================================
//function : NextTriangle
//design   :
//warning  :
//=======================================================================

void WfObjMesh_MeshExplorer::NextTriangle() {
    triangleIndex++;
    if (triangleIndex <= nbTriangles) {
        const Handle (WfObjMesh_MeshTriangle) trian = trianglesdef.Value(triangleIndex);
        trian->GetVertexAndOrientation(v1, v2, v3, xn, yn, zn);
    }
}

//=======================================================================
//function : TriangleVertices
//design   :
//warning  :
//=======================================================================

void WfObjMesh_MeshExplorer::TriangleVertices(Standard_Real &X1, Standard_Real &Y1,
                                              Standard_Real &Z1, Standard_Real &X2,
                                              Standard_Real &Y2, Standard_Real &Z2,
                                              Standard_Real &X3, Standard_Real &Y3,
                                              Standard_Real &Z3) const {
    Standard_NoSuchObject_Raise_if (triangleIndex > nbTriangles, " WfObjMesh_MeshExplorer::TriangleVertices");

    X1 = (trianglesVertex.Value(v1)).X();
    Y1 = (trianglesVertex.Value(v1)).Y();
    Z1 = (trianglesVertex.Value(v1)).Z();
    X2 = (trianglesVertex.Value(v2)).X();
    Y2 = (trianglesVertex.Value(v2)).Y();
    Z2 = (trianglesVertex.Value(v2)).Z();
    X3 = (trianglesVertex.Value(v3)).X();
    Y3 = (trianglesVertex.Value(v3)).Y();
    Z3 = (trianglesVertex.Value(v3)).Z();
}

//=======================================================================
//function : TriangleDirection
//design   :
//warning  :
//=======================================================================

void WfObjMesh_MeshExplorer::TriangleOrientation(Standard_Real &Xn, Standard_Real &Yn, Standard_Real &Zn) const {
    Xn = xn;
    Yn = yn;
    Zn = zn;
}

void WfObjMesh_MeshExplorer::InitPolygon(const Standard_Integer DomainIndex) {
    polygonIndex = 1;
    domainIndex = DomainIndex;
    nbPolygons = mesh->NbPolygons(domainIndex);
    if (nbPolygons > 0) {
        polygonsdef.Assign(mesh->Polygons(DomainIndex));
        trianglesVertex.Assign(mesh->Vertices(DomainIndex));
        const Handle (WfObjMesh_MeshPolygon) poly = polygonsdef.First();
        poly->GetOrientation(xn, yn, zn);
    }
}

void WfObjMesh_MeshExplorer::NextPolygon() {
    polygonIndex++;
    if (polygonIndex <= nbPolygons) {
        const Handle (WfObjMesh_MeshPolygon) poly = polygonsdef.Value(polygonIndex);
        poly->GetOrientation(xn, yn, zn);
    }
}

Standard_Integer WfObjMesh_MeshExplorer::PolygonVertexCount() {
    const Handle (WfObjMesh_MeshPolygon) poly = polygonsdef.Value(polygonIndex);
    return poly->GetVertexCount();
}

void WfObjMesh_MeshExplorer::PolygonVertex(Standard_Integer VI, Standard_Real &X, Standard_Real &Y, Standard_Real &Z)
{
    const Handle (WfObjMesh_MeshPolygon) poly = polygonsdef.Value(polygonIndex);

    Standard_Integer v1 = poly->GetVertex(VI);
    X = (trianglesVertex.Value(v1)).X();
    Y = (trianglesVertex.Value(v1)).Y();
    Z = (trianglesVertex.Value(v1)).Z();
}

void WfObjMesh_MeshExplorer::PolygonOrientation(Standard_Real &Xn, Standard_Real &Yn, Standard_Real &Zn)  {
    if (polygonIndex <= nbPolygons) {
        const Handle (WfObjMesh_MeshPolygon) poly = polygonsdef.Value(polygonIndex);
        poly->GetOrientation(xn, yn, zn);
    }
    Xn = xn;
    Yn = yn;
    Zn = zn;
}

