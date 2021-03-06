// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESControl_ToolContainer_HeaderFile
#define _IGESControl_ToolContainer_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_IGESControl_ToolContainer.hxx>

#include <IGESToBRep_ToolContainer.hxx>
#include <Handle_IGESToBRep_IGESBoundary.hxx>
class IGESToBRep_IGESBoundary;



class IGESControl_ToolContainer : public IGESToBRep_ToolContainer
{

public:

  
  //! Empty constructor
  Standard_EXPORT IGESControl_ToolContainer();
  
  //! Returns IGESControl_IGESBoundary
  Standard_EXPORT virtual   Handle(IGESToBRep_IGESBoundary) IGESBoundary()  const;




  DEFINE_STANDARD_RTTI(IGESControl_ToolContainer)

protected:




private: 




};







#endif // _IGESControl_ToolContainer_HeaderFile
