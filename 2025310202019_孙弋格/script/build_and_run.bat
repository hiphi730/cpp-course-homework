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
rem GNU Make can fail even on relative names when its working directory contains Unicode.
rem Build a fresh ASCII-only source tree on a temporary drive, using Windows to copy the inputs.
set "STAGING=%TEMP%\cpp-course-%RANDOM%-%RANDOM%-%RANDOM%"
if exist "%STAGING%" exit /b 1
mkdir "%STAGING%" || exit /b 1
set "WORK_DRIVE="
for %%L in (Z Y X W V U T S R Q P O N M L K J I H G F E D) do if not defined WORK_DRIVE (
    subst %%L: "%STAGING%" >nul 2>&1 && set "WORK_DRIVE=%%L:"
)
if not defined WORK_DRIVE (
    echo Unable to reserve a temporary drive for the MinGW build.
    rd "%STAGING%"
    exit /b 1
)
pushd "%WORK_DRIVE%\" || exit /b 1
call :compile_course
set "COURSE_RESULT=%ERRORLEVEL%"
popd
subst %WORK_DRIVE% /d
if errorlevel 1 exit /b 1
rd /s /q "%STAGING%"
exit /b %COURSE_RESULT%

:compile_course
setlocal
mkdir script build-mingw-course || exit /b 1
copy /y "%COURSE_ROOT%\script\course.mk" script\course.mk >nul || exit /b 1
xcopy "%COURSE_ROOT%\third_party" third_party\ /e /i /q /y >nul || exit /b 1
mingw32-make -f script/course.mk framework || exit /b 1
set /a STAGES=0
for /d %%D in ("%COURSE_ROOT%\*") do if exist "%%D\tests\CMakeLists.txt" (
    set /a STAGES+=1 >nul
    call :compile_stage "%%D" || exit /b 1
)
if not "%STAGES%"=="5" exit /b 1
echo All five stages passed.
exit /b 0

:compile_stage
echo Testing %~nx1
for %%P in (src include tests) do (
    xcopy "%~1\%%P" "stage%STAGES%\%%P\" /e /i /q /y >nul || exit /b 1
)
pushd stage%STAGES% || exit /b 1
mkdir build-mingw-course || exit /b 1
mingw32-make -f ../script/course.mk stage
set "STAGE_RESULT=%ERRORLEVEL%"
popd
exit /b %STAGE_RESULT%
