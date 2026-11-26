@echo off
setlocal
chcp 65001 >nul
set "COURSE_ROOT=%~dp0.."
where g++ >nul 2>&1
if errorlevel 1 goto default_build
where ninja >nul 2>&1
if errorlevel 1 (
    echo Install Ninja and add it to PATH to build with MinGW in Unicode paths.
    exit /b 1
)
set "BUILD_DIR=%COURSE_ROOT%\build-mingw-ninja"
cmake -S "%COURSE_ROOT%" -B "%BUILD_DIR%" -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug
goto build
:default_build
set "BUILD_DIR=%COURSE_ROOT%\build"
cmake -S "%COURSE_ROOT%" -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=Debug
:build
if errorlevel 1 exit /b 1
cmake --build "%BUILD_DIR%" --config Debug --parallel 2
if errorlevel 1 exit /b 1
pushd "%BUILD_DIR%"
if errorlevel 1 exit /b 1
ctest -C Debug --output-on-failure
set "TEST_RESULT=%ERRORLEVEL%"
popd
exit /b %TEST_RESULT%
