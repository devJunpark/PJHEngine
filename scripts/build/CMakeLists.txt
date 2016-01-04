cmake_minimum_required (VERSION 3.4.1)

PROJECT(PJHEngine)


add_custom_target(PJHEngine_target 
    WORKING_DIRECTORY ../../
)

set_target_properties(PJHEngine_target
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin"
)


#ADD_SUBDIRECTORY(../../source)
#ADD_SUBDIRECTORY(../../include)
#ADD_SUBDIRECTORY(../../packages)



