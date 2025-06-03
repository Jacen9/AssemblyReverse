@echo off
echo ========================================
echo Assembly Reverse Engineering Project
echo Build Script for Windows
echo ========================================
echo.

REM 检查Python是否可用
python --version >nul 2>&1
if errorlevel 1 (
    echo Error: Python is not installed or not in PATH
    echo Please install Python 3.6 or higher
    pause
    exit /b 1
)

REM 检查CMake是否可用
cmake --version >nul 2>&1
if errorlevel 1 (
    echo Error: CMake is not installed or not in PATH
    echo Please install CMake 3.8 or higher
    pause
    exit /b 1
)

echo Python and CMake found, starting build...
echo.

REM 运行Python构建脚本
if "%1"=="clean" (
    echo Running clean build...
    python bootstrap.py --clean --config Debug
) else if "%1"=="release" (
    echo Running release build...
    python bootstrap.py --config Release
) else if "%1"=="debug" (
    echo Running debug build...
    python bootstrap.py --config Debug
) else if "%1"=="generate" (
    echo Generating Visual Studio 2017 project files only...
    python bootstrap.py --generate-only --config Debug
) else if "%1"=="generate-release" (
    echo Generating Visual Studio 2017 project files (Release)...
    python bootstrap.py --generate-only --config Release
) else if "%1"=="open" (
    echo Generating and opening Visual Studio 2017...
    python bootstrap.py --generate-only --config Debug --open-vs
) else if "%1"=="open-release" (
    echo Generating and opening Visual Studio 2017 (Release)...
    python bootstrap.py --generate-only --config Release --open-vs
) else (
    echo Running default build (Debug)...
    python bootstrap.py --config Debug
)

if errorlevel 1 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.

REM 显示文件位置
if "%1"=="generate" (
    echo Visual Studio solution generated:
    echo   build\AssemblyReverseProject.sln
    echo.
    echo You can now open the solution in Visual Studio 2017
) else if "%1"=="generate-release" (
    echo Visual Studio solution generated (Release):
    echo   build\AssemblyReverseProject.sln
    echo.
    echo You can now open the solution in Visual Studio 2017
) else if "%1"=="open" (
    echo Visual Studio should be opening automatically...
) else if "%1"=="open-release" (
    echo Visual Studio should be opening automatically...
) else (
    echo Executable location:
    if "%1"=="release" (
        echo   build\bin\Release\main.exe
    ) else (
        echo   build\bin\Debug\main.exe
    )
    echo.
    echo Static library location:
    if "%1"=="release" (
        echo   build\lib\Release\utils.lib
    ) else (
        echo   build\lib\Debug\utils.lib
    )
    echo.
    echo Visual Studio solution:
    echo   build\AssemblyReverseProject.sln
)

echo.
echo Usage:
echo   build.bat                - Build Debug version
echo   build.bat debug          - Build Debug version
echo   build.bat release        - Build Release version
echo   build.bat clean          - Clean and build Debug version
echo   build.bat generate       - Generate VS2017 project files only (Debug)
echo   build.bat generate-release - Generate VS2017 project files only (Release)
echo   build.bat open           - Generate and open VS2017 (Debug)
echo   build.bat open-release   - Generate and open VS2017 (Release)
echo.
pause 