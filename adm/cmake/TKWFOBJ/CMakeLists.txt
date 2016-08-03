set(TOOLKIT TKWFOBJ)

set(TOOLKIT_MODULES
	WfObjMesh
	WfObjAPI
	WfObjTransfer
	RWWfObj
)
set(TOOLKIT_DEPENDS
	TKernel
	TKMath
	TKBRep
	TKG2d
	TKG3d
	TKMesh
	TKTopAlgo
)

include(../BuildToolkit.cmake)

