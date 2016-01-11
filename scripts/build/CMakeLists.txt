cmake_minimum_required (VERSION 3.4.1)

PROJECT(PJHEngine)

SET(PJHE_ROOT_PATH "${CMAKE_BINARY_DIR}/../..")

SET (BUILD_SHARED_LIBS TRUE)

add_definitions(-DDEBUG -DTEST)

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
    file(GLOB _srcfiles 
            "${_srcfolder}/*.cpp" 
            "${_srcfolder}/*.c"
    )
    get_filename_component(_foldername ${_srcfolder} NAME)
    LIST(APPEND PJHE_SRC_FILE_LIST ${_srcfiles})    
    source_group("source\\${_foldername}" FILES ${_srcfiles})
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
    file(GLOB _incfiles
        "${_incfolder}/*.h"
        "${_incfolder}/*.hpp"
    )
    get_filename_component(_foldername ${_incfolder} NAME)
    LIST(APPEND PJHE_INC_FILE_LIST ${_incfiles})
    source_group("include\\${_foldername}" FILES ${_incfiles})
endforeach()
file(GLOB PJHE_INC_FILE_PATH "${PJHE_INC_FILE_LIST}")
message("Done")

#### ------------------- ####
#### create main library #### 
#### ------------------- ####
add_library(PJHEngine SHARED
    ${PJHE_SRC_FILE_LIST}
    ${PJHE_INC_FILE_LIST}
)

#### -------------------------------- ####
#### setting libraries include folder ####
#### -------------------------------- ####
target_include_directories(PJHEngine PUBLIC
    "${PJHE_ROOT_PATH}/include"
)

### ------------------------------------------- ###
### setting include files of External libraries ###
### ------------------------------------------- ###
if(EXISTS "$ENV{TOOL_NANT_PATH}" )
    message("Nunt located $ENV{TOOL_NANT_PATH}")
    message("${PJHE_ROOT_PATH}/PJHEngine.build will be opend")
    execute_process(COMMAND 
        $ENV{TOOL_NANT_PATH}/nant build-library
            -buildfile:${PJHE_ROOT_PATH}/PJHEngine.build 
            -D:arg.debug=true 
            -D:arg.locale="kor"
        RESULT_VARIABLE PARSING_RESULT
        OUTPUT_VARIABLE PARSING_OUTPUT
        ERROR_VARIABLE PARSING_ERROR
    )
    message("Output : ${PARSING_OUTPUT}")
    if(${PARSING_RESULT})
        message("Error that reason : ${PARSING_ERROR}")
        message("Failed to add includes directory of external libraries. Check ExternalLibries.Build File.")
    endif()
    link_directories("$ENV{VAR_EXT_LINK_PATH}")
    file(GLOB PJHE_EXT_LINK_FILE_LIST 
            "$ENV{VAR_EXT_LINK_PATH}/*.lib"
            "$ENV{VAR_EXT_LINK_PATH}/*.dll"
    )
    target_link_libraries(PJHEngine ${PJHE_EXT_LINK_FILE_LIST})
else()
    message("Not found nunt path. Nunt path was not defined in TOOL_NANT_PATH variable.")
    message("Failed")
endif()

### ------------- ###
### For test code ###
### ------------- ###






