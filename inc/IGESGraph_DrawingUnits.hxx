// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESGraph_DrawingUnits_HeaderFile
#define _IGESGraph_DrawingUnits_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_IGESGraph_DrawingUnits.hxx>

#include <Standard_Integer.hxx>
#include <Handle_TCollection_HAsciiString.hxx>
#include <IGESData_IGESEntity.hxx>
#include <Standard_Real.hxx>
class TCollection_HAsciiString;


//! defines IGESDrawingUnits, Type <406> Form <17>
//! in package IGESGraph
//!
//! Specifies the drawing space units as outlined
//! in the Drawing entity
class IGESGraph_DrawingUnits : public IGESData_IGESEntity
{

public:

  
  Standard_EXPORT IGESGraph_DrawingUnits();
  
  //! This method is used to set the fields of the class
  //! DrawingUnits
  //! - nbProps : Number of property values (NP = 2)
  //! - aFlag   : DrawingUnits Flag
  //! - aUnit   : DrawingUnits Name
  Standard_EXPORT   void Init (const Standard_Integer nbProps, const Standard_Integer aFlag, const Handle(TCollection_HAsciiString)& aUnit) ;
  
  //! returns the number of property values in <me>
  Standard_EXPORT   Standard_Integer NbPropertyValues()  const;
  
  //! returns the drawing space units of <me>
  Standard_EXPORT   Standard_Integer Flag()  const;
  
  //! returns the name of the drawing space units of <me>
  Standard_EXPORT   Handle(TCollection_HAsciiString) Unit()  const;
  
  //! Computes the value of the unit, in meters, according Flag
  //! (same values as for GlobalSection from IGESData)
  Standard_EXPORT   Standard_Real UnitValue()  const;




  DEFINE_STANDARD_RTTI(IGESGraph_DrawingUnits)

protected:




private: 


  Standard_Integer theNbPropertyValues;
  Standard_Integer theFlag;
  Handle(TCollection_HAsciiString) theUnit;


};







#endif // _IGESGraph_DrawingUnits_HeaderFile
