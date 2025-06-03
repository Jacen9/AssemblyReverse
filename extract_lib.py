#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Library Extraction Script for Assembly Reverse Engineering
This script extracts .obj files from utils.lib and generates .asm files
"""

import os
import sys
import subprocess
import argparse
import shutil
import glob
from pathlib import Path

def run_command(cmd, cwd=None, capture_output=True):
    """运行命令并返回结果"""
    print(f"Running: {' '.join(cmd)}")
    try:
        if capture_output:
            # 使用适当的编码处理Windows工具输出
            result = subprocess.run(cmd, cwd=cwd, check=True, capture_output=True, 
                                  text=True, encoding='utf-8', errors='ignore')
            if result.stdout:
                print(result.stdout)
            return result
        else:
            subprocess.run(cmd, cwd=cwd, check=True)
            return None
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e}")
        if hasattr(e, 'stdout') and e.stdout:
            print(f"STDOUT: {e.stdout}")
        if hasattr(e, 'stderr') and e.stderr:
            print(f"STDERR: {e.stderr}")
        return None
    except UnicodeDecodeError as e:
        print(f"Encoding error: {e}")
        # 尝试使用系统默认编码
        try:
            result = subprocess.run(cmd, cwd=cwd, check=True, capture_output=True, 
                                  text=True, encoding='cp1252', errors='ignore')
            if result.stdout:
                print(result.stdout)
            return result
        except Exception as e2:
            print(f"Failed with alternative encoding: {e2}")
            return None

def find_lib_tool():
    """查找lib.exe工具"""
    lib_paths = [
        "lib",
        "lib.exe"
    ]
    
    # 查找Visual Studio安装路径中的lib.exe
    vs_paths = [
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017",
        "C:\\Program Files\\Microsoft Visual Studio\\2017",
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019",
        "C:\\Program Files\\Microsoft Visual Studio\\2019",
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022",
        "C:\\Program Files\\Microsoft Visual Studio\\2022"
    ]
    
    for vs_path in vs_paths:
        if os.path.exists(vs_path):
            for edition in ["Enterprise", "Professional", "Community"]:
                lib_path = os.path.join(vs_path, edition, "VC", "Tools", "MSVC")
                if os.path.exists(lib_path):
                    # 查找最新版本
                    versions = [d for d in os.listdir(lib_path) if os.path.isdir(os.path.join(lib_path, d))]
                    if versions:
                        latest_version = sorted(versions)[-1]
                        lib_exe = os.path.join(lib_path, latest_version, "bin", "Hostx64", "x64", "lib.exe")
                        if os.path.exists(lib_exe):
                            print(f"Found lib.exe: {lib_exe}")
                            return lib_exe
    
    # 尝试从PATH中查找
    for lib_path in lib_paths:
        try:
            result = subprocess.run([lib_path, "/?"], capture_output=True, text=True)
            if "Microsoft" in result.stdout or result.returncode == 0:
                print(f"Found lib.exe in PATH: {lib_path}")
                return lib_path
        except FileNotFoundError:
            continue
    
    return None

def find_dumpbin_tool():
    """查找dumpbin.exe工具"""
    dumpbin_paths = [
        "dumpbin",
        "dumpbin.exe"
    ]
    
    # 查找Visual Studio安装路径中的dumpbin.exe
    vs_paths = [
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017",
        "C:\\Program Files\\Microsoft Visual Studio\\2017",
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019",
        "C:\\Program Files\\Microsoft Visual Studio\\2019",
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022",
        "C:\\Program Files\\Microsoft Visual Studio\\2022"
    ]
    
    for vs_path in vs_paths:
        if os.path.exists(vs_path):
            for edition in ["Enterprise", "Professional", "Community"]:
                dumpbin_path = os.path.join(vs_path, edition, "VC", "Tools", "MSVC")
                if os.path.exists(dumpbin_path):
                    # 查找最新版本
                    versions = [d for d in os.listdir(dumpbin_path) if os.path.isdir(os.path.join(dumpbin_path, d))]
                    if versions:
                        latest_version = sorted(versions)[-1]
                        dumpbin_exe = os.path.join(dumpbin_path, latest_version, "bin", "Hostx64", "x64", "dumpbin.exe")
                        if os.path.exists(dumpbin_exe):
                            print(f"Found dumpbin.exe: {dumpbin_exe}")
                            return dumpbin_exe
    
    # 尝试从PATH中查找
    for dumpbin_path in dumpbin_paths:
        try:
            result = subprocess.run([dumpbin_path, "/?"], capture_output=True, text=True)
            if "Microsoft" in result.stdout or result.returncode == 0:
                print(f"Found dumpbin.exe in PATH: {dumpbin_path}")
                return dumpbin_path
        except FileNotFoundError:
            continue
    
    return None

def extract_obj_files(lib_file, output_dir, lib_tool):
    """从静态库中提取.obj文件"""
    print(f"\n=== Extracting .obj files from {lib_file} ===")
    
    # 创建输出目录
    os.makedirs(output_dir, exist_ok=True)
    
    # 列出库中的文件
    list_cmd = [lib_tool, "/LIST", lib_file]
    result = run_command(list_cmd)
    
    if not result:
        print("Failed to list library contents")
        return False
    
    # 解析输出，获取.obj文件列表
    obj_files = []
    for line in result.stdout.split('\n'):
        line = line.strip()
        if line.endswith('.obj'):
            obj_files.append(line)
    
    if not obj_files:
        print("No .obj files found in library")
        return False
    
    print(f"Found {len(obj_files)} .obj files:")
    for obj_file in obj_files:
        print(f"  - {obj_file}")
    
    # 提取每个.obj文件
    for obj_file in obj_files:
        # 简化输出文件名，只保留基本文件名
        base_name = os.path.basename(obj_file)
        output_path = os.path.join(output_dir, base_name)
        
        # 确保输出目录存在
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        
        extract_cmd = [lib_tool, "/EXTRACT:" + obj_file, "/OUT:" + output_path, lib_file]
        if not run_command(extract_cmd):
            print(f"Failed to extract {obj_file}")
            return False
        else:
            print(f"✓ Extracted: {base_name}")
    
    return True

def generate_asm_files(obj_dir, asm_dir, dumpbin_tool):
    """从.obj文件生成.asm文件"""
    print(f"\n=== Generating .asm files from .obj files ===")
    
    # 创建输出目录
    os.makedirs(asm_dir, exist_ok=True)
    
    # 查找所有.obj文件
    obj_files = glob.glob(os.path.join(obj_dir, "*.obj"))
    
    if not obj_files:
        print("No .obj files found")
        return False
    
    success_count = 0
    for obj_file in obj_files:
        obj_name = os.path.basename(obj_file)
        asm_name = obj_name.replace('.obj', '.asm')
        asm_file = os.path.join(asm_dir, asm_name)
        
        print(f"Generating {asm_name}...")
        
        # 使用dumpbin生成反汇编
        dumpbin_cmd = [dumpbin_tool, "/DISASM", obj_file]
        result = run_command(dumpbin_cmd)
        
        if result:
            # 将输出写入.asm文件
            with open(asm_file, 'w', encoding='utf-8') as f:
                f.write(f"; Disassembly of {obj_name}\n")
                f.write(f"; Generated by extract_lib.py\n\n")
                f.write(result.stdout)
            
            print(f"✓ Generated: {asm_name}")
            success_count += 1
        else:
            print(f"✗ Failed to generate: {asm_name}")
    
    print(f"\nSuccessfully generated {success_count}/{len(obj_files)} .asm files")
    return success_count > 0

def generate_summary_report(lib_file, obj_dir, asm_dir, output_dir):
    """生成提取报告"""
    report_file = os.path.join(output_dir, "extraction_report.txt")
    
    with open(report_file, 'w', encoding='utf-8') as f:
        f.write("Library Extraction Report\n")
        f.write("=" * 50 + "\n\n")
        f.write(f"Source Library: {lib_file}\n")
        f.write(f"Extraction Time: {subprocess.run(['date', '/t'], capture_output=True, text=True, shell=True).stdout.strip()}\n\n")
        
        # 统计.obj文件
        obj_files = glob.glob(os.path.join(obj_dir, "*.obj"))
        f.write(f"Extracted .obj files ({len(obj_files)}):\n")
        for obj_file in obj_files:
            size = os.path.getsize(obj_file)
            f.write(f"  - {os.path.basename(obj_file)} ({size:,} bytes)\n")
        
        f.write("\n")
        
        # 统计.asm文件
        asm_files = glob.glob(os.path.join(asm_dir, "*.asm"))
        f.write(f"Generated .asm files ({len(asm_files)}):\n")
        for asm_file in asm_files:
            size = os.path.getsize(asm_file)
            f.write(f"  - {os.path.basename(asm_file)} ({size:,} bytes)\n")
        
        f.write("\n")
        f.write("Directory Structure:\n")
        f.write(f"  {output_dir}/\n")
        f.write(f"  ├── obj/          # Extracted .obj files\n")
        f.write(f"  ├── asm/          # Generated .asm files\n")
        f.write(f"  └── extraction_report.txt\n")
    
    print(f"✓ Generated extraction report: {report_file}")

def main():
    parser = argparse.ArgumentParser(description="Extract .obj and generate .asm files from utils.lib")
    parser.add_argument("--lib-file", 
                       help="Path to the .lib file (default: auto-detect from build directory)")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"],
                       help="Build configuration (default: Debug)")
    parser.add_argument("--output-dir", default="extracted",
                       help="Output directory for extracted files (default: extracted)")
    parser.add_argument("--clean", action="store_true",
                       help="Clean output directory before extraction")
    
    args = parser.parse_args()
    
    # 获取项目根目录
    project_root = os.path.dirname(os.path.abspath(__file__))
    
    # 确定库文件路径
    if args.lib_file:
        lib_file = args.lib_file
    else:
        lib_file = os.path.join(project_root, "build", "lib", args.config, "utils.lib")
    
    if not os.path.exists(lib_file):
        print(f"Error: Library file not found: {lib_file}")
        print("Please build the project first or specify --lib-file")
        return 1
    
    print("=== Library Extraction Tool ===")
    print(f"Library file: {lib_file}")
    print(f"Configuration: {args.config}")
    print(f"Output directory: {args.output_dir}")
    
    # 查找工具
    lib_tool = find_lib_tool()
    if not lib_tool:
        print("Error: lib.exe not found. Please ensure Visual Studio is installed.")
        return 1
    
    dumpbin_tool = find_dumpbin_tool()
    if not dumpbin_tool:
        print("Error: dumpbin.exe not found. Please ensure Visual Studio is installed.")
        return 1
    
    # 设置输出目录
    output_dir = os.path.join(project_root, args.output_dir)
    obj_dir = os.path.join(output_dir, "obj")
    asm_dir = os.path.join(output_dir, "asm")
    
    # 清理输出目录
    if args.clean and os.path.exists(output_dir):
        print("Cleaning output directory...")
        shutil.rmtree(output_dir)
    
    # 提取.obj文件
    if not extract_obj_files(lib_file, obj_dir, lib_tool):
        print("Failed to extract .obj files")
        return 1
    
    # 生成.asm文件
    if not generate_asm_files(obj_dir, asm_dir, dumpbin_tool):
        print("Failed to generate .asm files")
        return 1
    
    # 生成报告
    generate_summary_report(lib_file, obj_dir, asm_dir, output_dir)
    
    print("\n=== Extraction completed successfully! ===")
    print(f"Output directory: {output_dir}")
    print(f"  - .obj files: {obj_dir}")
    print(f"  - .asm files: {asm_dir}")
    print(f"  - Report: {os.path.join(output_dir, 'extraction_report.txt')}")
    
    return 0

if __name__ == "__main__":
    sys.exit(main()) 