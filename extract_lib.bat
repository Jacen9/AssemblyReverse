@echo off
echo ========================================
echo Library Extraction Tool
echo Extract .obj and .asm files from utils.lib
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

echo Python found, starting extraction...
echo.

REM 运行Python提取脚本
if "%1"=="debug" (
    echo Extracting from Debug build...
    python extract_lib.py --config Debug
) else if "%1"=="release" (
    echo Extracting from Release build...
    python extract_lib.py --config Release
) else if "%1"=="clean" (
    echo Cleaning and extracting from Debug build...
    python extract_lib.py --config Debug --clean
) else if "%1"=="clean-release" (
    echo Cleaning and extracting from Release build...
    python extract_lib.py --config Release --clean
) else if "%1"=="help" (
    python extract_lib.py --help
    goto end
) else (
    echo Extracting from Debug build (default)...
    python extract_lib.py --config Debug
)

if errorlevel 1 (
    echo.
    echo Extraction failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo Extraction completed successfully!
echo ========================================
echo.
echo Output directory: extracted\
echo   - .obj files: extracted\obj\
echo   - .asm files: extracted\asm\
echo   - Report: extracted\extraction_report.txt
echo.
echo You can now:
echo 1. Examine the .obj files for binary analysis
echo 2. Study the .asm files for assembly code analysis
echo 3. Use the files with reverse engineering tools
echo.

:end
echo Usage:
echo   extract_lib.bat           - Extract from Debug build
echo   extract_lib.bat debug     - Extract from Debug build
echo   extract_lib.bat release   - Extract from Release build
echo   extract_lib.bat clean     - Clean and extract from Debug build
echo   extract_lib.bat clean-release - Clean and extract from Release build
echo   extract_lib.bat help      - Show detailed help
echo.
pause 