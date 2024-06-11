@ECHO OFF
REM Build Everything

ECHO "Building everything..."


REM PUSHD engine
REM CALL build.bat
REM POPD
REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)
REM
REM PUSHD testbed
REM CALL build.bat
REM POPD
REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM engine
make -f "Makefile.engine.windows.mak" all
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM testbed
make -f "Makefile.testbed.windows.mak" all
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully."

PAUSE
