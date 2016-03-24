### **************************************************************************************** ###
### **************************************************************************************** ###
###                                    FOR PROTOTYPE PROJECT                                 ###
### **************************************************************************************** ###
### **************************************************************************************** ###

message("will begin scripting for $ENV{VAR_PROTOTYPE_PROJECT_NAME}")

### --------------------------------- ###
### add sources for Prototype project ###
### --------------------------------- ###
message("Add source files for Prototype...")
file(GLOB PROTO_SRC_DIR_LIST
    "${PROTO_ROOT_PATH}/source/*"
)

SET (PROTO_SRC_FILE_LIST "")
foreach( _srcfolder ${PROTO_SRC_DIR_LIST})
    if(NOT IS_DIRECTORY ${_srcfolder})
        message("    was included source file for Prototype- ${_srcfolder}")
        LIST(APPEND PROTO_SRC_FILE_LIST ${_srcfolder})
        source_group("source" FILES ${_srcfolder})
    else()
        message("    was included source folder for Prototype - ${_srcfolder}")
        file(GLOB _srcfiles 
                "${_srcfolder}/*.cpp" 
                "${_srcfolder}/*.c"
        )
        get_filename_component(_foldername ${_srcfolder} NAME)
        LIST(APPEND PROTO_SRC_FILE_LIST ${_srcfiles})    
        source_group("source\\${_foldername}" FILES ${_srcfiles})
    endif()
endforeach()
file(GLOB PROTO_SRC_FILE_PATH "${PROTO_SRC_FILE_LIST}")
message("Done")

### ---------------------------------- ###
### add includes for Prototype project ###
### ---------------------------------- ###
message("Add include files for Prototype...")
file(GLOB PROTO_INC_DIR_LIST
    "${PROTO_ROOT_PATH}/include/*"
)

SET (PROTO_INC_FILE_LIST "")
foreach( _incfolder ${PROTO_INC_DIR_LIST})
    if(NOT IS_DIRECTORY ${_incfolder})
        message("    was included header file - ${_incfolder}")
        LIST(APPEND PROTO_INC_FILE_LIST ${_incfolder})
        source_group("include" FILES ${_incfolder})
    else()
        message("    was included header folder - ${_incfolder}")
        file(GLOB _incfiles
            "${_incfolder}/*.h"
            "${_incfolder}/*.hpp"
        )
        get_filename_component(_foldername ${_incfolder} NAME)
        LIST(APPEND PROTO_INC_FILE_LIST ${_incfiles})
        source_group("include\\${_foldername}" FILES ${_incfiles})
    endif()
endforeach()
file(GLOB PROTO_INC_DIR_LIST "${PROTO_INC_FILE_LIST}")
message("Done")              

### ----------------------------------------------------------------------- ###
### add Prototype project for that is capable for testing of PJHEngine Dll. ###
### ----------------------------------------------------------------------- ###
ADD_EXECUTABLE($ENV{VAR_PROTOTYPE_PROJECT_NAME}
    ${PROTO_SRC_FILE_LIST}
    ${PROTO_INC_FILE_LIST}
)
ADD_DEPENDENCIES($ENV{VAR_PROTOTYPE_PROJECT_NAME} $ENV{PROJECT_NAME})

#SET_TARGET_PROPERTIES($ENV{VAR_PROTOTYPE_PROJECT_NAME}
#    PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
#    ARCHIVE_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
#    RUNTIME_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
#)
#

### --------------------------------------------------------------------------------------- ###
### ** FOR PROTOTYPE PROJECT **                                                             ###
### add includes folder of External libraires.                                              ### 
### It was made by PJHEngine.build file and It must execute build scripts as Administrator. ###
### --------------------------------------------------------------------------------------- ###
SET( PJHE_EXT_INC_PATH "${PJHE_ROOT_PATH}/packages/includes")
if(EXISTS "${PJHE_EXT_INC_PATH}")
    message("Add external include dirs for prototype......")
    target_include_directories($ENV{VAR_PROTOTYPE_PROJECT_NAME} PUBLIC "${PJHE_EXT_INC_PATH}")
    message("Done")   
endif()

if(EXISTS "${PJHE_ROOT_PATH}/include")
    message("Add PJHEngine Header's path for prototype.....")
    target_include_directories($ENV{VAR_PROTOTYPE_PROJECT_NAME} PUBLIC "${PJHE_ROOT_PATH}/include")
    message("Done")
endif()

if(EXISTS $ENV{VAR_EXT_LINK_PATH} AND ${arg.outputtype} STREQUAL "lib")
    target_link_libraries($ENV{VAR_PROTOTYPE_PROJECT_NAME} ${PJHE_EXT_LINK_FILE_LIST})
endif()

target_link_libraries($ENV{VAR_PROTOTYPE_PROJECT_NAME} 
    "$ENV{VAR_PACKAGE_PATH}/$ENV{PROJECT_NAME}/${BUILD_MODE}/$ENV{PROJECT_NAME}.lib"
)

SET(PROTO_DEFINITION_OPTIONS __PJHENGINE_PROTOTYPE)
#SET(PROTO_DEFINITION_OPTIONS ${PROTO_DEFINITION_OPTIONS} -DBOOST_ALL_NO_LIB)
target_compile_definitions($ENV{VAR_PROTOTYPE_PROJECT_NAME}
    PUBLIC ${PROTO_DEFINITION_OPTIONS} 
)

#if(${arg.outputtype} STREQUAL "dll")
#    add_custom_command(TARGET $ENV{VAR_PROTOTYPE_PROJECT_NAME}
#        PRE_BUILD 
#        COMMAND robocopy ARGS \"$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}/${BUILD_MODE}/\"
#                         ARGS \"$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}/${BUILD_MODE}/\"
#                         ARGS \"$ENV{PROJECT_NAME}.dll\"
#        COMMENT "Copy PJHEngine.dll for Prototype"
#    )
#endif()

#target_compile_definitions($ENV{VAR_PROTOTYPE_PROJECT_NAME}
#    PUBLIC __PJH_DLL_API 
#)

### ------------- ###
### For test code ###
### ------------- ###



