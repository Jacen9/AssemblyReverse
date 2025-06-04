#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Library Extraction Script for Assembly Reverse Engineering
This script extracts .obj files from utils.lib and generates .asm files
Also supports converting debug libraries to release libraries
"""

import os
import sys
import subprocess
import argparse
import shutil
import glob
import tempfile
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

def find_editbin_tool():
    """查找editbin.exe工具"""
    editbin_paths = [
        "editbin",
        "editbin.exe"
    ]
    
    # 查找Visual Studio安装路径中的editbin.exe
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
                editbin_path = os.path.join(vs_path, edition, "VC", "Tools", "MSVC")
                if os.path.exists(editbin_path):
                    # 查找最新版本
                    versions = [d for d in os.listdir(editbin_path) if os.path.isdir(os.path.join(editbin_path, d))]
                    if versions:
                        latest_version = sorted(versions)[-1]
                        editbin_exe = os.path.join(editbin_path, latest_version, "bin", "Hostx64", "x64", "editbin.exe")
                        if os.path.exists(editbin_exe):
                            print(f"Found editbin.exe: {editbin_exe}")
                            return editbin_exe
    
    # 尝试从PATH中查找
    for editbin_path in editbin_paths:
        try:
            result = subprocess.run([editbin_path, "/?"], capture_output=True, text=True)
            if "Microsoft" in result.stdout or result.returncode == 0:
                print(f"Found editbin.exe in PATH: {editbin_path}")
                return editbin_path
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

def convert_debug_to_release_lib(debug_lib_file, release_lib_file, lib_tool, editbin_tool, output_base_dir=None):
    """将debug库转换为release库"""
    print(f"\n=== Converting debug library to release library ===")
    print(f"Source (Debug): {debug_lib_file}")
    print(f"Target (Release): {release_lib_file}")
    
    if not os.path.exists(debug_lib_file):
        print(f"Error: Debug library file not found: {debug_lib_file}")
        return False
    
    # 创建临时目录用于处理
    with tempfile.TemporaryDirectory() as temp_dir:
        temp_obj_dir = os.path.join(temp_dir, "obj")
        os.makedirs(temp_obj_dir, exist_ok=True)
        
        # 步骤1: 从debug库中提取所有.obj文件
        print("Step 1: Extracting .obj files from debug library...")
        if not extract_obj_files(debug_lib_file, temp_obj_dir, lib_tool):
            print("Failed to extract .obj files from debug library")
            return False
        
        # 可选：保存debug提取的文件到指定目录
        if output_base_dir:
            debug_output_dir = os.path.join(output_base_dir, "debug", "obj")
            print(f"Saving debug .obj files to: {debug_output_dir}")
            os.makedirs(debug_output_dir, exist_ok=True)
            obj_files = glob.glob(os.path.join(temp_obj_dir, "*.obj"))
            for obj_file in obj_files:
                target_path = os.path.join(debug_output_dir, os.path.basename(obj_file))
                shutil.copy2(obj_file, target_path)
        
        # 步骤2: 处理每个.obj文件，移除调试信息
        print("Step 2: Processing .obj files to remove debug information...")
        obj_files = glob.glob(os.path.join(temp_obj_dir, "*.obj"))
        processed_obj_files = []
        
        for obj_file in obj_files:
            processed_obj = process_obj_for_release(obj_file, editbin_tool)
            if processed_obj:
                processed_obj_files.append(processed_obj)
            else:
                print(f"Warning: Failed to process {os.path.basename(obj_file)}, using original")
                processed_obj_files.append(obj_file)
        
        # 可选：保存处理后的release .obj文件到指定目录
        if output_base_dir:
            release_obj_output_dir = os.path.join(output_base_dir, "release", "obj")
            print(f"Saving processed release .obj files to: {release_obj_output_dir}")
            os.makedirs(release_obj_output_dir, exist_ok=True)
            for obj_file in processed_obj_files:
                target_path = os.path.join(release_obj_output_dir, os.path.basename(obj_file).replace('.processed', ''))
                shutil.copy2(obj_file, target_path)
        
        # 步骤3: 创建新的release库
        print("Step 3: Creating release library...")
        if not create_release_library(processed_obj_files, release_lib_file, lib_tool):
            print("Failed to create release library")
            return False
    
    print(f"✓ Successfully converted debug library to release library: {release_lib_file}")
    return True

def process_obj_for_release(obj_file, editbin_tool):
    """处理单个.obj文件以移除调试信息"""
    try:
        # 创建处理后的文件副本
        processed_obj = obj_file + ".processed"
        shutil.copy2(obj_file, processed_obj)
        
        # 使用editbin移除调试信息
        # /NOLOGO: 不显示版权信息
        # /REMOVE:.debug$S: 移除调试符号段
        # /REMOVE:.debug$T: 移除调试类型段
        # /REMOVE:.debug$F: 移除调试文件段
        editbin_cmd = [
            editbin_tool,
            "/NOLOGO",
            "/REMOVE:.debug$S",
            "/REMOVE:.debug$T", 
            "/REMOVE:.debug$F",
            processed_obj
        ]
        
        result = run_command(editbin_cmd, capture_output=True)
        if result is not None:
            print(f"✓ Processed: {os.path.basename(obj_file)}")
            return processed_obj
        else:
            print(f"✗ Failed to process: {os.path.basename(obj_file)}")
            # 如果处理失败，删除处理后的文件
            if os.path.exists(processed_obj):
                os.remove(processed_obj)
            return None
            
    except Exception as e:
        print(f"Error processing {os.path.basename(obj_file)}: {e}")
        return None

def create_release_library(obj_files, output_lib, lib_tool):
    """从.obj文件创建release库"""
    if not obj_files:
        print("No .obj files to create library from")
        return False
    
    # 确保输出目录存在
    os.makedirs(os.path.dirname(output_lib), exist_ok=True)
    
    # 构建lib命令
    lib_cmd = [lib_tool, "/NOLOGO", "/OUT:" + output_lib]
    lib_cmd.extend(obj_files)
    
    print(f"Creating library with {len(obj_files)} object files...")
    result = run_command(lib_cmd, capture_output=True)
    
    if result is not None:
        print(f"✓ Created release library: {output_lib}")
        return True
    else:
        print(f"✗ Failed to create release library")
        return False

def analyze_library_differences(debug_lib, release_lib, dumpbin_tool):
    """分析debug和release库的差异"""
    print(f"\n=== Analyzing library differences ===")
    
    def get_lib_info(lib_file):
        """获取库文件信息"""
        if not os.path.exists(lib_file):
            return None
            
        info = {
            'size': os.path.getsize(lib_file),
            'symbols': [],
            'sections': []
        }
        
        # 获取符号信息
        symbols_cmd = [dumpbin_tool, "/SYMBOLS", lib_file]
        result = run_command(symbols_cmd, capture_output=True)
        if result:
            for line in result.stdout.split('\n'):
                line = line.strip()
                if 'External' in line or 'Static' in line:
                    info['symbols'].append(line)
        
        return info
    
    debug_info = get_lib_info(debug_lib)
    release_info = get_lib_info(release_lib)
    
    if not debug_info or not release_info:
        print("Failed to analyze one or both libraries")
        return
    
    print(f"Debug library size: {debug_info['size']:,} bytes")
    print(f"Release library size: {release_info['size']:,} bytes")
    size_reduction = debug_info['size'] - release_info['size']
    reduction_percent = (size_reduction / debug_info['size']) * 100 if debug_info['size'] > 0 else 0
    print(f"Size reduction: {size_reduction:,} bytes ({reduction_percent:.1f}%)")
    
    print(f"Debug symbols count: {len(debug_info['symbols'])}")
    print(f"Release symbols count: {len(release_info['symbols'])}")

def generate_conversion_report(debug_lib_file, release_lib_file, output_base_dir):
    """生成转换报告"""
    report_file = os.path.join(output_base_dir, "conversion_report.txt")
    
    with open(report_file, 'w', encoding='utf-8') as f:
        f.write("Library Conversion Report\n")
        f.write("=" * 50 + "\n\n")
        f.write(f"Source (Debug): {debug_lib_file}\n")
        f.write(f"Target (Release): {release_lib_file}\n")
        f.write(f"Conversion Time: {subprocess.run(['date', '/t'], capture_output=True, text=True, shell=True).stdout.strip()}\n\n")
        
        # 文件大小比较
        if os.path.exists(debug_lib_file) and os.path.exists(release_lib_file):
            debug_size = os.path.getsize(debug_lib_file)
            release_size = os.path.getsize(release_lib_file)
            reduction = debug_size - release_size
            reduction_percent = (reduction / debug_size) * 100 if debug_size > 0 else 0
            
            f.write(f"File Size Comparison:\n")
            f.write(f"  Debug library:   {debug_size:,} bytes\n")
            f.write(f"  Release library: {release_size:,} bytes\n")
            f.write(f"  Size reduction:  {reduction:,} bytes ({reduction_percent:.1f}%)\n\n")
        
        # 统计debug .obj文件
        debug_obj_dir = os.path.join(output_base_dir, "debug", "obj")
        if os.path.exists(debug_obj_dir):
            debug_obj_files = glob.glob(os.path.join(debug_obj_dir, "*.obj"))
            f.write(f"Debug .obj files ({len(debug_obj_files)}):\n")
            for obj_file in debug_obj_files:
                size = os.path.getsize(obj_file)
                f.write(f"  - {os.path.basename(obj_file)} ({size:,} bytes)\n")
            f.write("\n")
        
        # 统计release .obj文件
        release_obj_dir = os.path.join(output_base_dir, "release", "obj")
        if os.path.exists(release_obj_dir):
            release_obj_files = glob.glob(os.path.join(release_obj_dir, "*.obj"))
            f.write(f"Release .obj files ({len(release_obj_files)}):\n")
            for obj_file in release_obj_files:
                size = os.path.getsize(obj_file)
                f.write(f"  - {os.path.basename(obj_file)} ({size:,} bytes)\n")
            f.write("\n")
        
        f.write("Directory Structure:\n")
        f.write(f"  {output_base_dir}/\n")
        f.write(f"  ├── debug/\n")
        f.write(f"  │   └── obj/          # Original debug .obj files\n")
        f.write(f"  ├── release/\n")
        f.write(f"  │   └── obj/          # Processed release .obj files\n")
        f.write(f"  └── conversion_report.txt\n")
    
    print(f"✓ Generated conversion report: {report_file}")

def process_both_configurations(project_root, output_base_dir, lib_tool, dumpbin_tool, clean=False):
    """同时处理debug和release两个配置的库文件"""
    print(f"\n=== Processing both Debug and Release configurations ===")
    
    # 定义两个配置的库文件路径
    debug_lib_file = os.path.join(project_root, "build", "lib", "Debug", "utils.lib")
    release_lib_file = os.path.join(project_root, "build", "lib", "Release", "utils.lib")
    
    # 检查文件是否存在
    debug_exists = os.path.exists(debug_lib_file)
    release_exists = os.path.exists(release_lib_file)
    
    if not debug_exists and not release_exists:
        print("Error: Neither Debug nor Release library files found.")
        print("Please build the project first using:")
        print("  python bootstrap.py --config Debug")
        print("  python bootstrap.py --config Release")
        return False
    
    if not debug_exists:
        print(f"Warning: Debug library not found: {debug_lib_file}")
        print("Skipping Debug configuration.")
    
    if not release_exists:
        print(f"Warning: Release library not found: {release_lib_file}")
        print("Skipping Release configuration.")
    
    success_count = 0
    total_count = 0
    
    # 清理输出目录
    if clean and os.path.exists(output_base_dir):
        print("Cleaning output directory...")
        shutil.rmtree(output_base_dir)
    
    # 处理Debug配置
    if debug_exists:
        total_count += 1
        print(f"\n--- Processing Debug configuration ---")
        print(f"Library: {debug_lib_file}")
        
        debug_output_dir = os.path.join(output_base_dir, "debug")
        debug_obj_dir = os.path.join(debug_output_dir, "obj")
        debug_asm_dir = os.path.join(debug_output_dir, "asm")
        
        # 提取Debug .obj文件
        if extract_obj_files(debug_lib_file, debug_obj_dir, lib_tool):
            # 生成Debug .asm文件
            if generate_asm_files(debug_obj_dir, debug_asm_dir, dumpbin_tool):
                # 生成Debug报告
                generate_summary_report(debug_lib_file, debug_obj_dir, debug_asm_dir, debug_output_dir)
                success_count += 1
                print("✓ Debug configuration processed successfully")
            else:
                print("✗ Failed to generate .asm files for Debug configuration")
        else:
            print("✗ Failed to extract .obj files for Debug configuration")
    
    # 处理Release配置
    if release_exists:
        total_count += 1
        print(f"\n--- Processing Release configuration ---")
        print(f"Library: {release_lib_file}")
        
        release_output_dir = os.path.join(output_base_dir, "release")
        release_obj_dir = os.path.join(release_output_dir, "obj")
        release_asm_dir = os.path.join(release_output_dir, "asm")
        
        # 提取Release .obj文件
        if extract_obj_files(release_lib_file, release_obj_dir, lib_tool):
            # 生成Release .asm文件
            if generate_asm_files(release_obj_dir, release_asm_dir, dumpbin_tool):
                # 生成Release报告
                generate_summary_report(release_lib_file, release_obj_dir, release_asm_dir, release_output_dir)
                success_count += 1
                print("✓ Release configuration processed successfully")
            else:
                print("✗ Failed to generate .asm files for Release configuration")
        else:
            print("✗ Failed to extract .obj files for Release configuration")
    
    # 生成对比报告
    if debug_exists and release_exists and success_count == 2:
        generate_comparison_report(debug_lib_file, release_lib_file, output_base_dir, dumpbin_tool)
    
    print(f"\n=== Processing completed: {success_count}/{total_count} configurations successful ===")
    return success_count > 0

def generate_comparison_report(debug_lib_file, release_lib_file, output_base_dir, dumpbin_tool):
    """生成debug和release的对比报告"""
    report_file = os.path.join(output_base_dir, "comparison_report.txt")
    
    print(f"Generating comparison report...")
    
    with open(report_file, 'w', encoding='utf-8') as f:
        f.write("Debug vs Release Comparison Report\n")
        f.write("=" * 50 + "\n\n")
        f.write(f"Analysis Time: {subprocess.run(['date', '/t'], capture_output=True, text=True, shell=True).stdout.strip()}\n\n")
        
        # 库文件大小比较
        debug_size = os.path.getsize(debug_lib_file) if os.path.exists(debug_lib_file) else 0
        release_size = os.path.getsize(release_lib_file) if os.path.exists(release_lib_file) else 0
        
        f.write("Library File Size Comparison:\n")
        f.write(f"  Debug library:   {debug_size:,} bytes\n")
        f.write(f"  Release library: {release_size:,} bytes\n")
        
        if debug_size > 0 and release_size > 0:
            size_diff = debug_size - release_size
            size_diff_percent = (size_diff / debug_size) * 100 if debug_size > 0 else 0
            f.write(f"  Size difference: {size_diff:,} bytes ({size_diff_percent:.1f}%)\n")
            f.write(f"  Release is {'smaller' if size_diff > 0 else 'larger'} than Debug\n")
        f.write("\n")
        
        # .obj文件数量和大小比较
        debug_obj_dir = os.path.join(output_base_dir, "debug", "obj")
        release_obj_dir = os.path.join(output_base_dir, "release", "obj")
        
        debug_obj_files = glob.glob(os.path.join(debug_obj_dir, "*.obj")) if os.path.exists(debug_obj_dir) else []
        release_obj_files = glob.glob(os.path.join(release_obj_dir, "*.obj")) if os.path.exists(release_obj_dir) else []
        
        f.write("Extracted .obj Files Comparison:\n")
        f.write(f"  Debug .obj files:   {len(debug_obj_files)} files\n")
        f.write(f"  Release .obj files: {len(release_obj_files)} files\n")
        
        if debug_obj_files and release_obj_files:
            debug_obj_total_size = sum(os.path.getsize(f) for f in debug_obj_files)
            release_obj_total_size = sum(os.path.getsize(f) for f in release_obj_files)
            f.write(f"  Debug .obj total size:   {debug_obj_total_size:,} bytes\n")
            f.write(f"  Release .obj total size: {release_obj_total_size:,} bytes\n")
            
            obj_size_diff = debug_obj_total_size - release_obj_total_size
            obj_size_diff_percent = (obj_size_diff / debug_obj_total_size) * 100 if debug_obj_total_size > 0 else 0
            f.write(f"  .obj size difference: {obj_size_diff:,} bytes ({obj_size_diff_percent:.1f}%)\n")
        f.write("\n")
        
        # .asm文件数量比较
        debug_asm_dir = os.path.join(output_base_dir, "debug", "asm")
        release_asm_dir = os.path.join(output_base_dir, "release", "asm")
        
        debug_asm_files = glob.glob(os.path.join(debug_asm_dir, "*.asm")) if os.path.exists(debug_asm_dir) else []
        release_asm_files = glob.glob(os.path.join(release_asm_dir, "*.asm")) if os.path.exists(release_asm_dir) else []
        
        f.write("Generated .asm Files Comparison:\n")
        f.write(f"  Debug .asm files:   {len(debug_asm_files)} files\n")
        f.write(f"  Release .asm files: {len(release_asm_files)} files\n")
        
        if debug_asm_files and release_asm_files:
            debug_asm_total_size = sum(os.path.getsize(f) for f in debug_asm_files)
            release_asm_total_size = sum(os.path.getsize(f) for f in release_asm_files)
            f.write(f"  Debug .asm total size:   {debug_asm_total_size:,} bytes\n")
            f.write(f"  Release .asm total size: {release_asm_total_size:,} bytes\n")
        f.write("\n")
        
        # 符号信息比较（如果有dumpbin工具）
        if dumpbin_tool:
            f.write("Symbol Analysis:\n")
            
            # 分析Debug库符号
            debug_symbols = []
            symbols_cmd = [dumpbin_tool, "/SYMBOLS", debug_lib_file]
            result = run_command(symbols_cmd, capture_output=True)
            if result:
                for line in result.stdout.split('\n'):
                    line = line.strip()
                    if 'External' in line or 'Static' in line:
                        debug_symbols.append(line)
            
            # 分析Release库符号
            release_symbols = []
            symbols_cmd = [dumpbin_tool, "/SYMBOLS", release_lib_file]
            result = run_command(symbols_cmd, capture_output=True)
            if result:
                for line in result.stdout.split('\n'):
                    line = line.strip()
                    if 'External' in line or 'Static' in line:
                        release_symbols.append(line)
            
            f.write(f"  Debug symbols count:   {len(debug_symbols)}\n")
            f.write(f"  Release symbols count: {len(release_symbols)}\n")
            
            symbol_diff = len(debug_symbols) - len(release_symbols)
            f.write(f"  Symbol difference: {symbol_diff} symbols\n")
        
        f.write("\n")
        f.write("Directory Structure:\n")
        f.write(f"  {output_base_dir}/\n")
        f.write(f"  ├── debug/\n")
        f.write(f"  │   ├── obj/                    # Debug .obj files\n")
        f.write(f"  │   ├── asm/                    # Debug .asm files\n")
        f.write(f"  │   └── extraction_report.txt   # Debug extraction report\n")
        f.write(f"  ├── release/\n")
        f.write(f"  │   ├── obj/                    # Release .obj files\n")
        f.write(f"  │   ├── asm/                    # Release .asm files\n")
        f.write(f"  │   └── extraction_report.txt   # Release extraction report\n")
        f.write(f"  └── comparison_report.txt       # This comparison report\n")
    
    print(f"✓ Generated comparison report: {report_file}")

def main():
    parser = argparse.ArgumentParser(description="Extract .obj and generate .asm files from utils.lib, or convert debug lib to release lib")
    parser.add_argument("--lib-file", 
                       help="Path to the .lib file (default: auto-detect from build directory)")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"],
                       help="Build configuration (default: Debug)")
    parser.add_argument("--output-dir", default="extracted",
                       help="Output directory for extracted files (default: extracted)")
    parser.add_argument("--clean", action="store_true",
                       help="Clean output directory before extraction")
    parser.add_argument("--convert-to-release", action="store_true",
                       help="Convert debug library to release library")
    parser.add_argument("--release-lib-output",
                       help="Output path for converted release library (default: same directory as source with _release suffix)")
    parser.add_argument("--analyze-diff", action="store_true",
                       help="Analyze differences between debug and release libraries (requires --convert-to-release)")
    parser.add_argument("--process-both", action="store_true",
                       help="Process both Debug and Release configurations simultaneously")
    
    args = parser.parse_args()
    
    # 获取项目根目录
    project_root = os.path.dirname(os.path.abspath(__file__))
    
    # 设置基础输出目录
    output_base_dir = os.path.join(project_root, args.output_dir)
    
    print("=== Library Processing Tool ===")
    
    # 查找工具
    lib_tool = find_lib_tool()
    if not lib_tool:
        print("Error: lib.exe not found. Please ensure Visual Studio is installed.")
        return 1
    
    # 如果需要同时处理两个配置
    if args.process_both:
        print("Mode: Process both Debug and Release configurations")
        
        dumpbin_tool = find_dumpbin_tool()
        if not dumpbin_tool:
            print("Error: dumpbin.exe not found. Please ensure Visual Studio is installed.")
            return 1
        
        if process_both_configurations(project_root, output_base_dir, lib_tool, dumpbin_tool, args.clean):
            print(f"\n=== Both configurations processed successfully! ===")
            print(f"Output directory: {output_base_dir}")
            print(f"  - Debug files: {os.path.join(output_base_dir, 'debug')}")
            print(f"  - Release files: {os.path.join(output_base_dir, 'release')}")
            print(f"  - Comparison report: {os.path.join(output_base_dir, 'comparison_report.txt')}")
            return 0
        else:
            print("Failed to process configurations")
            return 1
    
    # 清理输出目录
    if args.clean and os.path.exists(output_base_dir):
        print("Cleaning output directory...")
        shutil.rmtree(output_base_dir)
    
    # 确定库文件路径（对于单个配置处理）
    if args.lib_file:
        lib_file = args.lib_file
    else:
        lib_file = os.path.join(project_root, "build", "lib", args.config, "utils.lib")
    
    if not os.path.exists(lib_file):
        print(f"Error: Library file not found: {lib_file}")
        print("Please build the project first or specify --lib-file")
        if not args.process_both:
            print("Or use --process-both to process existing configurations")
        return 1
    
    print(f"Library file: {lib_file}")
    print(f"Configuration: {args.config}")
    
    # 如果需要转换为release库，执行转换操作
    if args.convert_to_release:
        print("Mode: Convert debug library to release library")
        
        # 查找editbin工具
        editbin_tool = find_editbin_tool()
        if not editbin_tool:
            print("Error: editbin.exe not found. Please ensure Visual Studio is installed.")
            return 1
        
        # 确定release库输出路径
        if args.release_lib_output:
            release_lib_file = args.release_lib_output
        else:
            lib_dir = os.path.dirname(lib_file)
            lib_name = os.path.basename(lib_file)
            name_without_ext = os.path.splitext(lib_name)[0]
            release_lib_file = os.path.join(lib_dir, f"{name_without_ext}_release.lib")
        
        # 创建转换专用的输出目录结构
        conversion_output_dir = os.path.join(output_base_dir, "conversion")
        os.makedirs(conversion_output_dir, exist_ok=True)
        
        # 执行转换
        if not convert_debug_to_release_lib(lib_file, release_lib_file, lib_tool, editbin_tool, conversion_output_dir):
            print("Failed to convert debug library to release library")
            return 1
        
        # 生成转换报告
        generate_conversion_report(lib_file, release_lib_file, conversion_output_dir)
        
        # 如果需要分析差异
        if args.analyze_diff:
            dumpbin_tool = find_dumpbin_tool()
            if dumpbin_tool:
                analyze_library_differences(lib_file, release_lib_file, dumpbin_tool)
            else:
                print("Warning: dumpbin.exe not found, skipping difference analysis")
        
        print(f"\n=== Conversion completed successfully! ===")
        print(f"Original (Debug): {lib_file}")
        print(f"Converted (Release): {release_lib_file}")
        print(f"Conversion files: {conversion_output_dir}")
        print(f"  - Debug .obj files: {os.path.join(conversion_output_dir, 'debug', 'obj')}")
        print(f"  - Release .obj files: {os.path.join(conversion_output_dir, 'release', 'obj')}")
        print(f"  - Conversion report: {os.path.join(conversion_output_dir, 'conversion_report.txt')}")
        return 0
    
    # 原有的提取功能 - 根据配置创建相应的目录结构
    print("Mode: Extract and disassemble library")
    config_lower = args.config.lower()
    print(f"Target configuration: {args.config}")
    
    dumpbin_tool = find_dumpbin_tool()
    if not dumpbin_tool:
        print("Error: dumpbin.exe not found. Please ensure Visual Studio is installed.")
        return 1
    
    # 根据配置设置输出目录
    config_output_dir = os.path.join(output_base_dir, config_lower)
    obj_dir = os.path.join(config_output_dir, "obj")
    asm_dir = os.path.join(config_output_dir, "asm")
    
    print(f"Output directory: {config_output_dir}")
    
    # 提取.obj文件
    if not extract_obj_files(lib_file, obj_dir, lib_tool):
        print("Failed to extract .obj files")
        return 1
    
    # 生成.asm文件
    if not generate_asm_files(obj_dir, asm_dir, dumpbin_tool):
        print("Failed to generate .asm files")
        return 1
    
    # 生成报告
    generate_summary_report(lib_file, obj_dir, asm_dir, config_output_dir)
    
    print(f"\n=== Extraction completed successfully! ===")
    print(f"Configuration: {args.config}")
    print(f"Output directory: {config_output_dir}")
    print(f"  - .obj files: {obj_dir}")
    print(f"  - .asm files: {asm_dir}")
    print(f"  - Report: {os.path.join(config_output_dir, 'extraction_report.txt')}")
    
    return 0

if __name__ == "__main__":
    sys.exit(main()) 