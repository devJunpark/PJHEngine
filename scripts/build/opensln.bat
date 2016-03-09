@call _set_variables.bat

@set pjhe_targetpath=%VAR_PACKAGE_PATH%\%PROJECT_NAME%

:: couldn't find path of sln. 
@if not exist %pjhe_targetpath% ( @goto OPEN_FAILED )
@set pjhe_targetpath=%pjhe_targetpath%\%PROJECT_NAME%.sln
:: couldn't find sln file.
@if not exist %pjhe_targetpath% ( @goto OPEN_FAILED )

@echo will open the solution of %PROJECT_NAME%. Wait......
@call %pjhe_targetpath%
@exit /b

:OPEN_FAILED
@echo not found %pjhe_targetpath%. &echo please check %pjhe_targetpath% either it exists or else.
@exit /b
