cmake_minimum_required (VERSION 3.4.1)

PROJECT($ENV{PROJECT_NAME})

SET(PJHE_ROOT_PATH "${CMAKE_BINARY_DIR}/../..")
SET(PROTO_ROOT_PATH "${PJHE_ROOT_PATH}/$ENV{VAR_PROTOTYPE_PROJECT_NAME}")
SET(BUILD_SHARED_LIBS TRUE)

add_definitions(-DDEBUG -DTEST)

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

#### ------------------------------------- ####
#### setting Main libraries include folder ####
#### ------------------------------------- ####
target_include_directories(PJHEngine PUBLIC
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
            -D:arg.debug=true 
            -D:arg.locale="kor"
			#-D:arg.rebuild="$ENV{VAR_EXT_LINK_REBUILD}"
			-D:arg.rebuild="true"
        RESULT_VARIABLE PARSING_RESULT
        OUTPUT_VARIABLE PARSING_OUTPUT
        ERROR_VARIABLE PARSING_ERROR
    )
    message("Output : ${PARSING_OUTPUT}")
    if(${PARSING_RESULT})
        message("Error that reason : ${PARSING_ERROR}")
        message("Failed to add includes directory of external libraries. Check targetname build-library in PJHEngine.build file")
    endif()
    link_directories("$ENV{VAR_EXT_LINK_PATH}")
    file(GLOB PJHE_EXT_LINK_FILE_LIST 
            "$ENV{VAR_EXT_LINK_PATH}/*.lib"
            #"$ENV{VAR_EXT_LINK_PATH}/*.dll"
    )
    target_link_libraries(PJHEngine ${PJHE_EXT_LINK_FILE_LIST})
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
    target_include_directories(PJHEngine PUBLIC "${PJHE_EXT_INC_PATH}")
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
        message("    was included source file - ${_srcfolder}")
        LIST(APPEND PROTO_SRC_FILE_LIST ${_srcfolder})
    else()
        message("    was included source folder - ${_srcfolder}")
        file(GLOB _srcfiles 
                "${_srcfolder}/*.cpp" 
                "${_srcfolder}/*.c"
        )
        get_filename_component(_foldername ${_srcfolder} NAME)
        LIST(APPEND PROTO_SRC_FILE_LIST ${_srcfiles})    
        source_group("${_foldername}" FILES ${_srcfiles})
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
    else()
        message("    was included header folder - ${_incfolder}")
        file(GLOB _incfiles
            "${_incfolder}/*.h"
            "${_incfolder}/*.hpp"
        )
        get_filename_component(_foldername ${_incfolder} NAME)
        LIST(APPEND PROTO_INC_FILE_LIST ${_incfiles})
        source_group("${_foldername}" FILES ${_incfiles})
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


### ------------- ###
### For test code ###
### ------------- ###



