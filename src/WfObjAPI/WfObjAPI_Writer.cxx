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

#include <WfObjAPI_Writer.ixx>
#include <WfObjTransfer.hxx>
#include <TopoDS_Shape.hxx>
#include <Bnd_Box.hxx>
#include <RWWfObj.hxx>
#include <BRepBndLib.hxx>
#include <OSD_Path.hxx>

#define MAX2(X, Y)      (  Abs(X) > Abs(Y)? Abs(X) : Abs(Y) )
#define MAX3(X, Y, Z)   ( MAX2 ( MAX2(X,Y) , Z) )

WfObjAPI_Writer::WfObjAPI_Writer() {
    theWfObjMesh = new WfObjMesh_Mesh;
    theDeflection = 0.01;
    theRelativeMode = Standard_True;
    theCoefficient = 0.001;
}

void WfObjAPI_Writer::SetDeflection(const Standard_Real aDeflection) {
    theDeflection = aDeflection;
}

void WfObjAPI_Writer::SetCoefficient(const Standard_Real aCoefficient) {
    theCoefficient = aCoefficient;
}

Standard_Boolean &WfObjAPI_Writer::RelativeMode() {
    return theRelativeMode;
}

void WfObjAPI_Writer::Write(const TopoDS_Shape &theShape, const Standard_CString theFileName,
                            const Standard_Boolean theInParallel) {
    OSD_Path aFile(theFileName);
    if (theRelativeMode) {
        Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
        Bnd_Box Total;
        BRepBndLib::Add(theShape, Total);
        Total.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
        theDeflection = MAX3(aXmax - aXmin, aYmax - aYmin, aZmax - aZmin) * theCoefficient;
    }
    WfObjTransfer::BuildIncrementalMesh(theShape, theDeflection, theInParallel, theWfObjMesh);
    // Write the built mesh
    RWWfObj::WriteFile(theWfObjMesh, aFile);
}

