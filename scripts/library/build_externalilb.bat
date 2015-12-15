@call _set_variables.bat

@setlocal ENABLEDELAYEDEXPANSION
@echo.

@for /f "delims=| tokens=1-4" %%i in (%PACKAGES_INCLUDE_LIST_FILE_NAME%) do @(
	@SET type=%%i
	@SET path=%PACKAGES_ROOTPATH%\%%j
	@SET name=%%k
	@SET isBuild=%%l
	@echo Type:[!type!] Path:[!path!] Name:[!name!] isBuild:[!isBuild!]
	pushd !path!	
)


@endlocal

@echo. & @echo %~dpn0 Done!.
