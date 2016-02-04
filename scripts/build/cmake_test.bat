@call _set_variables.bat

@call clean.bat

@set VAR_SCRIPT_BUILD_PATH=%cd%

@pushd %PROJECT_ROOT_PATH%

@set optional=-A x64 -G "Visual Studio 12 2013"

@if exist %VAR_SCRIPT_BUILD_PATH%\CMakeLists.txt (
    robocopy %VAR_SCRIPT_BUILD_PATH%\ %VAR_PACKAGE_PATH%\%PROJECT_NAME%\ CMakeLists.txt
    call %TOOL_CMAKE_PATH%\cmake.exe %optional% "%VAR_PACKAGE_PATH%\%PROJECT_NAME%\CMakeLists.txt"
    ::del %VAR_PACKAGE_PATH%\%PROJECT_NAME%\CMakeLists.txt
    echo Done.
)

@popd 

@if exist CMakeCache.txt (
    @del CMakeCache.txt
)

