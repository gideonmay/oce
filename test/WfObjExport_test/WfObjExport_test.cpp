#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <gtest/gtest.h>

#include <TopoDS_Shape.hxx>
#include <WfObjAPI.hxx>


#include "WfObjExport_test_config.h"

TEST(WfObjExportTestSuite, testExportWfObj1)
{
    Standard_CString aFileName = (Standard_CString) wfobj_file_1;
    Standard_CString outFileName = (Standard_CString) wfobj_out_file_1;

    TopoDS_Shape aShape;
    WfObjAPI::Read(aShape,aFileName);
    WfObjAPI::Write(aShape,outFileName);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
