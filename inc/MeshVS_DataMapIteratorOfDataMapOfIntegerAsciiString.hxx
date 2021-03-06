// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString_HeaderFile
#define _MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BasicMapIterator.hxx>
#include <Standard_Integer.hxx>
#include <Handle_MeshVS_DataMapNodeOfDataMapOfIntegerAsciiString.hxx>
class Standard_NoSuchObject;
class TCollection_AsciiString;
class TColStd_MapIntegerHasher;
class MeshVS_DataMapOfIntegerAsciiString;
class MeshVS_DataMapNodeOfDataMapOfIntegerAsciiString;



class MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString  : public TCollection_BasicMapIterator
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString();
  
  Standard_EXPORT MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString(const MeshVS_DataMapOfIntegerAsciiString& aMap);
  
  Standard_EXPORT   void Initialize (const MeshVS_DataMapOfIntegerAsciiString& aMap) ;
  
  Standard_EXPORT  const  Standard_Integer& Key()  const;
  
  Standard_EXPORT  const  TCollection_AsciiString& Value()  const;




protected:





private:





};







#endif // _MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString_HeaderFile
