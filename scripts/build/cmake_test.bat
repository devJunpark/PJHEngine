@call _set_variables.bat

@pushd %PROJECT_ROOT_PATH%

@set optional=-A x64 -G "Visual Studio 12 2013"

@if exist CMakeCache.txt (
    @del CMakeCache.txt
)

call %TOOL_CMAKE_PATH%\cmake.exe %optional% scripts\build\CMakeLists.txt 

@popd 

