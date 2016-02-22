@call _set_variables.bat

@pushd %PROJECT_ROOT_PATH%

@if exist %VAR_PACKAGE_PATH%\%PROJECT_NAME% (
    echo %VAR_PACKAGE_PATH%\%PROJECT_NAME% was already generated... will remove.
    rmdir /s /q %VAR_PACKAGE_PATH%\%PROJECT_NAME%
)
@if exist %VAR_EXT_LINK_PATH% (
    echo %VAR_EXT_LINK_PATH% was already generated... will remove.
    rmdir /s /q %VAR_EXT_LINK_PATH%
)
@if exist %VAR_PROJECT_BUILD_OUTPUT_PATH% (
    echo %VAR_PROJECT_BUILD_OUTPUT_PATH% was already generated... will remove it.
    rmdir /s /q %VAR_PROJECT_BUILD_OUTPUT_PATH%
)
@if exist %VAR_PROTOTYPE_BUILD_OUTPUT_PATH% (
    echo %VAR_PROTOTYPE_BUILD_OUTPUT_PATH% was already generated... will remove it.
    rmdir /s /q %VAR_PROTOTYPE_BUILD_OUTPUT_PATH%
)

@popd

@echo Clean Done.
