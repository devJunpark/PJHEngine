@call _set_variables.bat

@pushd %PROJECT_ROOT_PATH%

call %TOOL_NANT_PATH%\Nant.exe -buildfile:PJHEngine.build -D:arg.debug=true -D:arg.locale="kor" %*

@popd 

