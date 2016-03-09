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
SET(arg.outputtype "dll" CACHE STRING "determine format of output of PJHEngine. can be lib or dll.")

### --------------------------------------- ###
### add pre-definitions for all of projects ###
### --------------------------------------- ###
SET(DEFINITION_OPTIONS "/D \"__PJHENGINE\"")
if(${arg.outputtype} STREQUAL "dll")
    SET(DEFINITION_OPTIONS "${DEFINITION_OPTIONS} /D \"__PJH_USE_DLL\"")
endif()
add_definitions(
    ${DEFINITION_OPTIONS}
)             
message("Global definition options ---")
message(${DEFINITION_OPTIONS})

#add_subdirectory($ENV{VAR_PROJECT_BUILD_OUTPUT_PATH}) # Add PJHEngine project
#add_subdirectory($ENV{VAR_PROTOTYPE_BUILD_OUTPUT_PATH}) # Add Prototype project for that will use library of PJHEngine.
include($ENV{PROJECT_ROOT_PATH}\\source\\CMakeLists.txt)
include($ENV{PROJECT_ROOT_PATH}\\$ENV{VAR_PROTOTYPE_PROJECT_NAME}\\CMakeLists.txt)

message("CMakeLists ROOT Done.")
