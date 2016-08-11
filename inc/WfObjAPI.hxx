#ifndef _WfObjAPI_HeaderFile
#define _WfObjAPI_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_CString.hxx>
#include <Standard_Boolean.hxx>
class TopoDS_Shape;
class WfObjAPI_Writer;
class WfObjAPI_Reader;

//! Offers the API for Wavefront Obj data manipulation.
class WfObjAPI 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT static void Write (const TopoDS_Shape& aShape, const Standard_CString aFile) ;
  
  Standard_EXPORT static void Read (TopoDS_Shape& aShape, const Standard_CString aFile) ;
  
private:
  friend class WfObjAPI_Writer;
  friend class WfObjAPI_Reader;
};

#endif // _WfObjAPI_HeaderFile
