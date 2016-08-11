#include <TopoDS_Shape.hxx>
#include <WfObjAPI.hxx>
#include <gtest/gtest.h>

#include "WfObjImport_test_config.h"

TEST(WfObjImportTestSuite, testImportWfObj1)
{
    Standard_CString aFileName = (Standard_CString) wfobj_file_1;
    TopoDS_Shape aShape;
    /*
    Standard_Boolean result = WfObjAPI::Read(aShape,aFileName);
    ASSERT_TRUE(result);
    */
    WfObjAPI::Read(aShape,aFileName);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(WfObjImportTestSuite, testImportWfObj2)
{
    Standard_CString aFileName = (Standard_CString) wfobj_file_2;
    TopoDS_Shape aShape;
    WfObjAPI::Read(aShape,aFileName);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(WfObjImportTestSuite, testImportWfObj3)
{
    Standard_CString aFileName = (Standard_CString) wfobj_file_3;
    TopoDS_Shape aShape;
    WfObjAPI::Read(aShape,aFileName);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(WfObjImportTestSuite, testImportWfObj4)
{
    Standard_CString aFileName = (Standard_CString) wfobj_file_4;
    TopoDS_Shape aShape;
    WfObjAPI::Read(aShape,aFileName);
    ASSERT_FALSE(aShape.IsNull());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
