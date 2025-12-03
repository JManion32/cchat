@echo off
setlocal

REM ============================================
REM CONFIGURATION
REM ============================================
set BINDIR=bin
set SRCDIR=src
set COMMONDIR=common

REM Windows compiler (MSVC)
if not defined VSINSTALLDIR (
    echo You must run this script from a "Developer Command Prompt for VS".
    echo Or run: vcvarsall.bat x64
    exit /b 1
)

REM Ensure output directory exists
if not exist "%BINDIR%" mkdir "%BINDIR%"

REM Compiler flags
set CFLAGS=/EHsc /std:c++17
set LIBS=ws2_32.lib

REM Common source files
set COMMON=%COMMONDIR%\socket_handler.cpp %COMMONDIR%\thread_handler.cpp


REM ============================================
REM BUILD SERVER
REM ============================================
:build_server
cl %CFLAGS% ^
    %SRCDIR%\server\server.cpp ^
    %COMMON% ^
    /Fe%BINDIR%\server.exe ^
    %LIBS%

if errorlevel 1 exit /b 1
echo Server built successfully.
goto done_server


REM ============================================
REM BUILD CLIENT (Qt GUI)
REM ============================================
:build_client

REM NOTE: Qt DLLs & paths must be in environment:
REM   set QT_DIR=C:\Qt\6.7.0\msvc2019_64
REM   set PATH=%QT_DIR%\bin;%PATH%

cl %CFLAGS% ^
    /I "%QT_DIR%\include" ^
    /I "%QT_DIR%\include\QtWidgets" ^
    /I "%QT_DIR%\include\QtCore" ^
    /I "%QT_DIR%\include\QtGui" ^
    %SRCDIR%\client\client.cpp ^
    %COMMON% ^
    /Fe%BINDIR%\client.exe ^
    %LIBS% ^
    "%QT_DIR%\lib\Qt6Core.lib" ^
    "%QT_DIR%\lib\Qt6Gui.lib" ^
    "%QT_DIR%\lib\Qt6Widgets.lib"

if errorlevel 1 exit /b 1
echo Client built successfully.
goto done_client


REM ============================================
REM BUILD ALL
REM ============================================
:build_all
call :build_server
call :build_client
echo All binaries built!
goto end


REM ============================================
REM MENU / ARGUMENT HANDLING
REM ============================================
:menu
echo.
echo Windows Build Script
echo -----------------------------------------
echo 1. Build ALL
echo 2. Build SERVER only
echo 3. Build CLIENT only
echo.

set /p choice="Choose option: "

if "%choice%"=="1" goto build_all
if "%choice%"=="2" goto build_server
if "%choice%"=="3" goto build_client

echo Invalid option.
goto menu


REM ============================================
REM DONE LABELS
REM ============================================
:done_server
goto end

:done_client
goto end

REM ============================================
REM END
REM ============================================
:end
echo.
echo Build complete.
exit /b 0
