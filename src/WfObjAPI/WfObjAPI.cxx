#include <WfObjAPI.ixx>
#include <WfObjAPI_Writer.hxx>
#include <WfObjAPI_Reader.hxx>

void WfObjAPI::Write(const TopoDS_Shape& aShape, const Standard_CString aFile)
{
  WfObjAPI_Writer writer;
  writer.Write (aShape, aFile, false);
}

void WfObjAPI::Read(TopoDS_Shape& aShape,const Standard_CString aFile)
{
  WfObjAPI_Reader reader;
  reader.Read (aShape, aFile);
}
