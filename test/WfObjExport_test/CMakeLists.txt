if (OCE_DATAEXCHANGE)
	set(wfobj_file_1     ${CMAKE_SOURCE_DIR}/test/data/wfobj/model1.obj)
	set(wfobj_out_file_1 ${CMAKE_SOURCE_DIR}/test/data/wfobj/out1.obj)

	configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/WfObjExport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/WfObjExport_test_config.h )
	include_directories(${CMAKE_BINARY_DIR}/test_inc)

	add_oce_test(WfObjExport_test "TKernel;TKWFOBJ;TKBRep;TKMath;TKTopAlgo;TKPrim;TKMesh")
endif (OCE_DATAEXCHANGE)
