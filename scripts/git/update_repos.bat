@pushd ..\..\
@goto label_update
@popd

@echo Done.
@exit /b

:label_update
@echo function called label_udpate
@for /D %%d in ("*") do @(
    @echo Current Directory[%%d]
    @cd %%d
    goto label_update
    @call git pull PJHEngine master
    @cd ..
)
