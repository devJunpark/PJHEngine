@call _set_variables.bat

@set copyoption=/NJH /NJS /NDL

@if exist %PROJECT_ROOT_PATH%\CMakeLists.txt (
    ::@echo robocopy %copyoption% %PROJECT_ROOT_PATH%\ %VAR_PACKAGE_PATH%\%PROJECT_NAME%\ CMakeLists.txt 
    robocopy %copyoption% %PROJECT_ROOT_PATH%\ %VAR_PACKAGE_PATH%\%PROJECT_NAME%\ CMakeLists.txt
)

::@set COPY_PROJECT_CMAKE_PATH=%PROJECT_ROOT_PATH%\source\
::@if exist %COPY_PROJECT_CMAKE_PATH%CMakeLists.txt (
::    ::@echo robocopy %copyoption% %COPY_PROJECT_CMAKE_PATH% %VAR_PROJECT_BUILD_OUTPUT_PATH%\ CMakeLists.txt
::    robocopy %copyoption% %COPY_PROJECT_CMAKE_PATH% %VAR_PROJECT_BUILD_OUTPUT_PATH%\ CMakeLists.txt
::)
::
::@set COPY_PROTOTYPE_CMAKE_PATH=%PROJECT_ROOT_PATH%\%VAR_PROTOTYPE_PROJECT_NAME%\
::@if exist %COPY_PROTOTYPE_CMAKE_PATH%CMakeLists.txt (
::    ::@echo robocopy %copyoption% %COPY_PROTOTYPE_CMAKE_PATH% %VAR_PROTOTYPE_BUILD_OUTPUT_PATH%\ CMakeLists.txt
::    robocopy %copyoption% %COPY_PROTOTYPE_CMAKE_PATH% %VAR_PROTOTYPE_BUILD_OUTPUT_PATH%\ CMakeLists.txt
::)

@echo copy Done.
