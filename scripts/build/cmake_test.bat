@call _set_variables.bat

@call clean.bat

@set VAR_SCRIPT_BUILD_PATH=%cd%

@pushd %PROJECT_ROOT_PATH%

@set optional=-A x64 -G "Visual Studio 12 2013"
@set optional=%optional% -Darg.debug:String="true"
@set optional=%optional% -Darg.locale:String="kor"
@set optional=%optional% -Darg.rebuild:String="true"
@set optional=%optional% -Darg.outputtype:String="dll"

@echo --- Build options ---
@echo   %optional%

@if exist %VAR_SCRIPT_BUILD_PATH%\CMakeLists.txt (
    robocopy %VAR_SCRIPT_BUILD_PATH%\ %VAR_PACKAGE_PATH%\%PROJECT_NAME%\ CMakeLists.txt
    call %TOOL_CMAKE_PATH%\cmake.exe %optional% "%VAR_PACKAGE_PATH%\%PROJECT_NAME%\CMakeLists.txt"
    echo Done.
    
    @popd
    @call opensln.bat
) else (
    @popd 
)
