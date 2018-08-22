include_directories( BEFORE
					 ${CMAKE_SOURCE_DIR}/include
					 ${CMAKE_SOURCE_DIR}/utils
                     ${CMAKE_CURRENT_SOURCE_DIR}/../cnn_network )
					 
# set target name
set( TARGET_NAME cnn_test )



# add a target named ${TARGET_NAME}
add_executable (${TARGET_NAME} test.cpp )

target_link_libraries( ${TARGET_NAME} openvx vxu cnn_network )

install ( TARGETS ${TARGET_NAME} 
          RUNTIME DESTINATION bin
          ARCHIVE DESTINATION bin
          LIBRARY DESTINATION bin )