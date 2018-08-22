					 
# set target name
set( TARGET_NAME cnn_convert )



# add a target named ${TARGET_NAME}
add_executable (${TARGET_NAME} cnn_convert.cpp )


install ( TARGETS ${TARGET_NAME} 
          RUNTIME DESTINATION bin
          ARCHIVE DESTINATION bin
          LIBRARY DESTINATION bin )
