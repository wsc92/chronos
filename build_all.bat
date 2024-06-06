@ECHO OFF
REM Build Everything

ECHO "Building everything..."

PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ = (echo Error:%ERRORLEVEL% && exit)

PUSHD testbed
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ = (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully"
