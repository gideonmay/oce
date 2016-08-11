#ifndef _WfObjAPI_Writer_HeaderFile
#define _WfObjAPI_Writer_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_Boolean.hxx>
#include <Standard_Real.hxx>
#include <Handle_WfObjMesh_Mesh.hxx>
#include <Standard_CString.hxx>
class WfObjMesh_Mesh;
class TopoDS_Shape;

class WfObjAPI_Writer 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Creates a writer object with
  //! default parameters: RelativeMode, SetCoefficent,
  //! SetDeflection. These parameters may be modified.
  Standard_EXPORT WfObjAPI_Writer();
  
  //! Sets the deflection of the meshing algorithm.
  //! Deflection is used, only if relative mode is false
  Standard_EXPORT   void SetDeflection (const Standard_Real aDeflection) ;
  
  //! Sets the coeffiecient for computation of deflection through
  //! relative size of shape. Default value = 0.001
  Standard_EXPORT   void SetCoefficient (const Standard_Real aCoefficient) ;
  
  //! Returns the address to the
  //! flag defining the relative mode for writing the file.
  //! This address may be used to either read or change the flag.
  //! If the mode returns True (default value), the
  //! deflection is calculated from the relative size of the
  //! shape. If the mode returns False, the user defined deflection is used.
  //! Example
  //! Read:
  //! Standard_Boolean val = Writer.RelativeMode( );
  //! Modify:
  //! Writer.RelativeMode( ) = Standard_True;
  Standard_EXPORT   Standard_Boolean& RelativeMode() ;
  
  //! Converts a given shape to STL format and writes it to file with a given filename.
  Standard_EXPORT   void Write (const TopoDS_Shape& aShape, const Standard_CString aFileName, const Standard_Boolean theInParallel) ;
private:
  Standard_Boolean theRelativeMode;
  Standard_Real theDeflection;
  Standard_Real theCoefficient;
  Handle(WfObjMesh_Mesh) theWfObjMesh;
};

#endif // _WfObjAPI_Writer_HeaderFile
