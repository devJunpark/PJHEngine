@call up_to_date_external_src.bat

@setlocal ENABLEDELAYEDEXPANSION

@for /f "delims=| tokens=1,2" %%i in (%EXTERNALLIB_INCLUDE_LIST_FILE_NAME%) do @(
	@set fromLibpath=%EXTERNAL_LIB_ROOTPATH%\%%i\%%j
	@set toLibpath=%INPROJECT_LIB_ROOTPATH%\%%i\%%j 
	@echo try to copy from !fromLibpath! to !toLibpath!
	@robocopy !fromLibpath! !toLibpath! *.* /E /TEE
	echo.
)
@endlocal
		
@echo. &@echo %~n0 Done. &@echo.
