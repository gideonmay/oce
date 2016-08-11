#ifndef _WfObjAPI_Reader_HeaderFile
#define _WfObjAPI_Reader_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_CString.hxx>
class TopoDS_Shape;

class WfObjAPI_Reader 
{
public:
  DEFINE_STANDARD_ALLOC
  
  Standard_EXPORT WfObjAPI_Reader();
  
  Standard_EXPORT void Read (TopoDS_Shape& aShape, const Standard_CString aFileName) ;
};

#endif // _WfObjAPI_Reader_HeaderFile
