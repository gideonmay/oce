#ifndef _RWWfObj_HeaderFile
#define _RWWfObj_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_Boolean.hxx>
#include <Handle_WfObjMesh_Mesh.hxx>
#include <Handle_Message_ProgressIndicator.hxx>
class WfObjMesh_Mesh;
class OSD_Path;
class Message_ProgressIndicator;


//! This package contains the methods to be used in
//! the Stereo Lithograpy Application. The main
//! features of this application are ,starting from a
//! Shape :
//! - mesh this shape with a maximun tolerance,
//! - display the meshing,
//! - write the meshing in a file,
//! - read of file and display it,
class RWWfObj 
{
public:

  DEFINE_STANDARD_ALLOC

    Standard_EXPORT static Standard_Boolean WriteFile (const Handle(WfObjMesh_Mesh)& aMesh, const OSD_Path& aPath, const Handle(Message_ProgressIndicator)& aProgInd = NULL) ;
  
  Standard_EXPORT static Handle(WfObjMesh_Mesh) ReadFile (const OSD_Path& aPath, const Handle(Message_ProgressIndicator)& aProgInd = NULL) ;
};

#endif // _RWWfObj_HeaderFile
