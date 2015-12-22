::@call get_util_from_github.bat
@call _set_variables.bat

@setlocal ENABLEDELAYEDEXPANSION
@set path=%MAKE_PATH%;!path!
@for /f "delims=| tokens=1-4" %%i in (%UTIL_LIST_FILE_NAME%) do @(
	@echo.
	@set toolname=%%i
	@set toolpath=%PROJECT_ROOT_PATH%\%%j\!toolname!
	@echo Processing.. toolname[!toolname!] path[!toolpath!] 
	IF NOT EXIST !toolpath! (
		@echo Not ready for building.
	) else (
		pushd !toolpath!
		@call mingw32-make.exe %%l
		popd
	)
)

@endlocal


