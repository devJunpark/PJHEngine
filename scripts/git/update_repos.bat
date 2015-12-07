@pushd ..\..\
@call :label_update %1
@popd

@echo Done.
@exit /b

:label_update
@echo function called label_udpate with %1
@for /D %%d in ("*") do @(
    @echo Current Directory[%%d]
    @cd %%d
    @call :label_update %1
    @git pull PJHEngine %1
    @cd ..
)
