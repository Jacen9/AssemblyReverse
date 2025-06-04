#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Example script demonstrating how to use the debug-to-release library conversion feature
"""

import os
import subprocess
import sys

def main():
    """演示如何使用debug到release库转换功能"""
    
    print("=== Debug to Release Library Conversion Example ===\n")
    
    # 示例1: 基本转换
    print("Example 1: Basic conversion")
    print("Command: python extract_lib.py --convert-to-release")
    print("Description: Convert the default debug library to release version")
    print("Output: utils_release.lib in the same directory as the source\n")
    
    # 示例2: 指定输入和输出文件
    print("Example 2: Specify input and output files")
    print("Command: python extract_lib.py --lib-file build/lib/Debug/utils.lib --convert-to-release --release-lib-output build/lib/Release/utils.lib")
    print("Description: Convert specific debug library to specific release library path")
    print("Output: build/lib/Release/utils.lib\n")
    
    # 示例3: 转换并分析差异
    print("Example 3: Convert and analyze differences")
    print("Command: python extract_lib.py --convert-to-release --analyze-diff")
    print("Description: Convert library and show size/symbol differences between debug and release versions")
    print("Output: Conversion + analysis report\n")
    
    # 示例4: 完整的工作流程
    print("Example 4: Complete workflow")
    print("Commands:")
    print("  1. python extract_lib.py --convert-to-release --analyze-diff")
    print("  2. python extract_lib.py --lib-file utils_release.lib --output-dir extracted_release")
    print("Description: Convert debug to release, then extract and disassemble the release library")
    print("Output: Release library + extracted files\n")
    
    # 实际执行示例（如果用户确认）
    response = input("Do you want to run Example 1 (basic conversion)? (y/N): ")
    if response.lower() == 'y':
        print("\nRunning basic conversion...")
        try:
            result = subprocess.run([
                sys.executable, "extract_lib.py", 
                "--convert-to-release", 
                "--analyze-diff"
            ], capture_output=True, text=True)
            
            print("STDOUT:")
            print(result.stdout)
            
            if result.stderr:
                print("STDERR:")
                print(result.stderr)
                
            if result.returncode == 0:
                print("✓ Conversion completed successfully!")
            else:
                print("✗ Conversion failed!")
                
        except Exception as e:
            print(f"Error running conversion: {e}")
    
    print("\n=== Additional Usage Tips ===")
    print("1. Make sure Visual Studio is installed (for lib.exe and editbin.exe)")
    print("2. The conversion process removes debug symbols and sections")
    print("3. Release libraries are typically smaller than debug libraries")
    print("4. Use --analyze-diff to see the size reduction achieved")
    print("5. You can chain operations: convert first, then extract/disassemble")

if __name__ == "__main__":
    main() 