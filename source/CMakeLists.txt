cmake_minimum_required (VERSION 3.4.1)

message("will begin scripting for $ENV{PROJECT_NAME}")

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
#
#SET_TARGET_PROPERTIES($ENV{PROJECT_NAME}
#    PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
#     ARCHIVE_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
#     RUNTIME_OUTPUT_DIRECTORY "$ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}"
#)

SET(PJHE_DEFINITION_OPTIONS __PJHENGINE_LIBRARY)
if(${arg.outputtype} STREQUAL "dll")
    SET(PJHE_DEFINITION_OPTIONS ${PJHE_DEFINITION_OPTIONS} -D__PJH_DLL_API)
endif()
target_compile_definitions($ENV{PROJECT_NAME}
    PUBLIC ${PJHE_DEFINITION_OPTIONS} 
)

get_target_property(TEST_CMAKE_RUNTIME $ENV{PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
message("TEST_CMAKE_RUNTIME : ${TEST_CMAKE_RUNTIME}")

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
    file(GLOB PJHE_EXT_LINK_FILE_LIST 
            "$ENV{VAR_EXT_LINK_PATH}/*.lib"
            #"$ENV{VAR_EXT_LINK_PATH}/*.dll"
    )
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

if(EXISTS $ENV{VAR_EXT_LINK_PATH})
    target_link_libraries($ENV{PROJECT_NAME} ${PJHE_EXT_LINK_FILE_LIST})
endif()


