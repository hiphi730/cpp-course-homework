@echo off
setlocal
chcp 65001 >nul
set "COURSE_ROOT=%~dp0.."
where g++ >nul 2>&1
if errorlevel 1 goto default_build
where mingw32-make >nul 2>&1
if not errorlevel 1 goto course_build
where ninja >nul 2>&1
if errorlevel 1 (
    echo Please add the MinGW bin folder containing mingw32-make.exe to PATH.
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

:course_build
pushd "%COURSE_ROOT%" || exit /b 1
if not exist build-mingw-course mkdir build-mingw-course
mingw32-make -f script/course.mk framework || exit /b 1
set /a STAGES=0
for /d %%D in (*) do if exist "%%D\tests\CMakeLists.txt" (
    call :course_stage "%%D" || exit /b 1
    set /a STAGES+=1 >nul
)
popd
if not "%STAGES%"=="5" (
    echo Expected five stages, ran %STAGES%.
    exit /b 1
)
echo All five stages passed.
exit /b 0

:course_stage
pushd "%~1" || exit /b 1
echo Testing %~1
if not exist build-mingw-course mkdir build-mingw-course
mingw32-make -f ../script/course.mk stage
set "STAGE_RESULT=%ERRORLEVEL%"
popd
exit /b %STAGE_RESULT%
