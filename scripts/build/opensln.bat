@call _set_variables.bat

@set targetpath=%VAR_PACKAGE_PATH%\%PROJECT_NAME%

:: couldn't find path of sln. 
@if not exist %targetpath% ( @goto OPEN_FAILED )
@set targetpath=%targetpath%\%PROJECT_NAME%.sln
:: couldn't find sln file.
@if not exist %targetpath% ( @goto OPEN_FAILED )

@echo will open the solution of %PROJECT_NAME%. Wait......
@call %targetpath%
@exit /b

:OPEN_FAILED
@echo not found %targetpath%. &echo please check %targetpath% either it exists or else.
@exit /b
