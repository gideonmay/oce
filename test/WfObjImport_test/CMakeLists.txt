if (OCE_DATAEXCHANGE)
	set(wfobj_file_1 ${CMAKE_SOURCE_DIR}/test/data/wfobj/model1.obj)
	set(wfobj_file_2 ${CMAKE_SOURCE_DIR}/test/data/wfobj/model2.obj)
	set(wfobj_file_3 ${CMAKE_SOURCE_DIR}/test/data/wfobj/model3.obj)
	set(wfobj_file_4 ${CMAKE_SOURCE_DIR}/test/data/wfobj/model4.obj)

	configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/WfObjImport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/WfObjImport_test_config.h )
	include_directories(${CMAKE_BINARY_DIR}/test_inc)

	add_oce_test(WfObjImport_test "TKernel;TKWFOBJ")
endif (OCE_DATAEXCHANGE)
