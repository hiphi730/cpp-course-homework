@echo off
setlocal
chcp 65001 >nul
set "COURSE_ROOT=%~dp0.."
cmake -S "%COURSE_ROOT%" -B "%COURSE_ROOT%\build" -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 exit /b 1
cmake --build "%COURSE_ROOT%\build" --config Debug --parallel
if errorlevel 1 exit /b 1
pushd "%COURSE_ROOT%\build"
if errorlevel 1 exit /b 1
ctest -C Debug --output-on-failure
set "TEST_RESULT=%ERRORLEVEL%"
popd
exit /b %TEST_RESULT%
