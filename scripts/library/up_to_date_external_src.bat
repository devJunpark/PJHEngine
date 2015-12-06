@call _set_variables.bat

@setlocal ENABLEDELAYEDEXPANSION 

@for /f "delims=| tokens=1-3" %%i in (%EXTERNALLIB_INCLUDE_LIST_FILE_NAME%) do @(
	@set libpath=%EXTERNAL_LIB_ROOTPATH%\%%i\%%j
	@echo libtype:[%%i] libname:[%%j] libpath:[!libpath!] git:[%%k]
	IF NOT EXIST !libpath! (
		pushd !libpath!\..
		@echo !libpath! doesn't exist. This lib's related repo is %%k.
		call git clone %%k
		popd
	)
	pushd !libpath!
	call git pull
	popd
)

@echo. &@echo %~n0 Done. &@echo.

@endlocal
