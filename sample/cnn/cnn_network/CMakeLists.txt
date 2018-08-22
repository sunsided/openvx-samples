include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR} 
					 ${CMAKE_SOURCE_DIR}/utils
					 ${CMAKE_SOURCE_DIR}/include )
	
message (${CMAKE_SOURCE_DIR})				 
# set target name
set( TARGET_NAME cnn_network )

FIND_SOURCES()

if ((WIN32) OR (CYGWIN))
    set( DEF_FILE cnn_network.def )
endif ((WIN32) OR (CYGWIN))

link_directories( ${CMAKE_CURRENT_SOURCE_DIR}  )

# add a target named ${TARGET_NAME}
add_library (${TARGET_NAME} SHARED ${SOURCE_FILES} ${DEF_FILE} )


add_definitions( ${OPENVX_BUILDING_EXPORT_DEF} )



target_link_libraries( ${TARGET_NAME} openvx vxu half  )


install ( TARGETS ${TARGET_NAME} 
          RUNTIME DESTINATION bin
          ARCHIVE DESTINATION lib
          LIBRARY DESTINATION bin )
