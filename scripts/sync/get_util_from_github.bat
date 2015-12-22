@call _set_variables.bat

@setlocal ENABLEDELAYEDEXPANSION

@for /f "delims=| tokens=1-3" %%i in (%UTIL_LIST_FILE_NAME%) do @(
	@set toolname=%%i
	@set toolpath=%PROJECT_ROOT_PATH%\%%j\!toolname!
	@set gitaddr=%%k
	@echo toolname[!toolname!] path[!toolpath!] gitaddr[!gitaddr!]
	IF NOT EXIST !toolpath! (
		mkdir !toolpath!
		call git clone !gitaddr! !toolpath!
	) else (
		pushd !toolpath!
		call git pull
		popd
	)
)

@endlocal
