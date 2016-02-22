cmake_minimum_required (VERSION 3.4.1)

PROJECT($ENV{PROJECT_NAME})

SET(PJHE_ROOT_PATH "${CMAKE_BINARY_DIR}/../..")
SET(PROTO_ROOT_PATH "${PJHE_ROOT_PATH}/$ENV{VAR_PROTOTYPE_PROJECT_NAME}")
SET(BUILD_SHARED_LIBS TRUE)

SET(BUILD_MODE "debug")
if(${arg.debug} STREQUAL "false")
    SET(BUILD_MODE "release")
endif()

### --------------------------------- ###
### Arguments that was passed by user ###
### --------------------------------- ###
SET(arg.debug "true" CACHE STRING "need to set either debug or release. If it set true, then PJHEngine will be build a debug mode")
SET(arg.locale "kor" CACHE STRING "target locale of PJHEngine")
SET(arg.rebuild "false" CACHE STRING "set either need to rebulid or not.")
SET(arg.outputtype "lib" CACHE STRING "determine format of output of PJHEngine. can be lib or dll.")

### --------------------------------------- ###
### add pre-definitions for all of projects ###
### --------------------------------------- ###
add_definitions(-DTEST)             

###################################

message("Project root path is ${PJHE_ROOT_PATH}")

#### ---------------------------- ####
#### add sources for Main library ####
#### ---------------------------- ####
message("Add source files...")
file(GLOB PJHE_SRC_DIR_LIST
    "${PJHE_ROOT_PATH}/source/*"
)

SET (PJHE_SRC_FILE_LIST "")
foreach( _srcfolder ${PJHE_SRC_DIR_LIST})
    message("    ${_srcfolder}")
    if(NOT IS_DIRECTORY ${_srcfolder})
        LIST(APPEND PJHE_SRC_FILE_LIST ${_srcfolder})
        source_group("source" FILES ${_srcfolder})
    else()
        file(GLOB _srcfiles 
                "${_srcfolder}/*.cpp" 
                "${_srcfolder}/*.c"
        )
        get_filename_component(_foldername ${_srcfolder} NAME)
        LIST(APPEND PJHE_SRC_FILE_LIST ${_srcfiles})    
        source_group("source\\${_foldername}" FILES ${_srcfiles})
    endif()
endforeach()
file(GLOB PJHE_SRC_FILE_PATH "${PJHE_SRC_FILE_LIST}")
message("Done")

###----------------------------- ###
###add includes for Main Library ###
###----------------------------- ###
message("Add include files...")
file(GLOB PJHE_INC_DIR_LIST
    "${PJHE_ROOT_PATH}/include/*"
)
SET (PJHE_INC_FILE_LIST "")
foreach( _incfolder ${PJHE_INC_DIR_LIST})
    message("    ${_incfolder}")
    if(NOT IS_DIRECTORY ${_incfolder})
        LIST(APPEND PJHE_INC_FILE_LIST ${_incfolder})
        source_group("include" FILES ${_incfolder})
    else()
        file(GLOB _incfiles
            "${_incfolder}/*.h"
            "${_incfolder}/*.hpp"
        )
        get_filename_component(_foldername ${_incfolder} NAME)
        LIST(APPEND PJHE_INC_FILE_LIST ${_incfiles})
        source_group("include\\${_foldername}" FILES ${_incfiles})
    endif()
endforeach()
file(GLOB PJHE_INC_FILE_PATH "${PJHE_INC_FILE_LIST}")
message("Done")

#### ------------------- ####
#### create main library #### 
#### ------------------- ####
SET(_outputtype STATIC)
if( ${arg.outputtype} STREQUAL "dll" )
    SET(_outputtype SHARED)
endif()
add_library($ENV{PROJECT_NAME} ${_outputtype} 
    ${PJHE_SRC_FILE_LIST}
    ${PJHE_INC_FILE_LIST}
)

SET_TARGET_PROPERTIES($ENV{PROJECT_NAME}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
    ARCHIVE_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
)

target_compile_definitions($ENV{PROJECT_NAME}
    PUBLIC __PJH_DLL_API 
)

#### ------------------------------------- ####
#### setting Main libraries include folder ####
#### ------------------------------------- ####
target_include_directories($ENV{PROJECT_NAME} PUBLIC
    "${PJHE_ROOT_PATH}/include"
)

### ------------------------------------------- ###
### setting include files of External libraries ###
### ------------------------------------------- ###
if(EXISTS "$ENV{TOOL_NANT_PATH}" )
    message("Nunt located $ENV{TOOL_NANT_PATH}")
    message("${PJHE_ROOT_PATH}/PJHEngine.build will be opend")
    message("Buliding.... Wait a minute...")
    execute_process(COMMAND 
        $ENV{TOOL_NANT_PATH}/nant build-library
            -buildfile:${PJHE_ROOT_PATH}/PJHEngine.build 
            -D:arg.debug=${arg.debug}
            -D:arg.locale=${arg.locale}
			-D:arg.rebuild=${arg.rebuild}
            -D:arg.outputtype=${arg.outputtype}
            #$ENV{VAR_EXT_LINK_REBUILD}
            #-D:arg.rebuild="true"
        RESULT_VARIABLE PARSING_RESULT
        OUTPUT_VARIABLE PARSING_OUTPUT
        ERROR_VARIABLE PARSING_ERROR
    )
    message("Output : ${PARSING_OUTPUT}")
    if(${PARSING_RESULT})
        message("Error that reason : ${PARSING_ERROR}")
        message("Failed to add includes directory of external libraries. Check targetname build-library in PJHEngine.build file")
    endif()
    #link_directories("$ENV{VAR_EXT_LINK_PATH}")
    file(GLOB PJHE_EXT_LINK_FILE_LIST 
            "$ENV{VAR_EXT_LINK_PATH}/*.lib"
            #"$ENV{VAR_EXT_LINK_PATH}/*.dll"
    )
    target_link_libraries($ENV{PROJECT_NAME} ${PJHE_EXT_LINK_FILE_LIST})
    #add_library(boost_library STATIC IMPORTED ${PJHE_EXT_LINK_FILE_LIST})
    #set_target_properties(boost_library PROPERTIES IMPORTED_LOCATION "$ENV{VAR_EXT_LINK_PATH}")
    #target_link_libraries($ENV{PROJECT_NAME} boost_library)

else()
    message("Not found nunt path. Nunt path was not defined in TOOL_NANT_PATH variable.")
    message("Failed")
endif()

### --------------------------------------------------------------------------------------- ###
### add includes folder of External libraires.                                              ### 
### It was made by PJHEngine.build file and It must execute build scripts as Administrator. ###
### --------------------------------------------------------------------------------------- ###
SET( PJHE_EXT_INC_PATH "${PJHE_ROOT_PATH}/packages/includes")
if(EXISTS "${PJHE_EXT_INC_PATH}")
    message("Add external include dirs...")
    target_include_directories($ENV{PROJECT_NAME} PUBLIC "${PJHE_EXT_INC_PATH}")
    message("Done")   
endif()


### **************************************************************************************** ###
### **************************************************************************************** ###
###                                    FOR PROTOTYPE PROJECT                                 ###
### **************************************************************************************** ###
### **************************************************************************************** ###

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

SET_TARGET_PROPERTIES($ENV{VAR_PROTOTYPE_PROJECT_NAME}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
    ARCHIVE_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}"
)


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


target_link_libraries($ENV{VAR_PROTOTYPE_PROJECT_NAME} 
    "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}/${BUILD_MODE}/$ENV{PROJECT_NAME}.lib"
)

add_custom_command(TARGET $ENV{VAR_PROTOTYPE_PROJECT_NAME}
    PRE_BUILD 
    COMMAND robocopy ARGS \"$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}/${BUILD_MODE}/\"
                     ARGS \"$ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}/${BUILD_MODE}/\"
                     ARGS \"$ENV{PROJECT_NAME}.dll\"
    COMMENT "Copy PJHEngine.dll for Prototype"
)

#target_compile_definitions($ENV{VAR_PROTOTYPE_PROJECT_NAME}
#    PUBLIC __PJH_DLL_API 
#)

### ------------- ###
### For test code ###
### ------------- ###



