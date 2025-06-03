#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Bootstrap script for building the Assembly Reverse Project
This script will configure and build the project using CMake and Visual Studio 2017
"""

import os
import sys
import subprocess
import argparse
import shutil
import glob

def run_command(cmd, cwd=None):
    """运行命令并检查返回值"""
    print(f"Running: {' '.join(cmd)}")
    try:
        result = subprocess.run(cmd, cwd=cwd, check=True, capture_output=True, text=True)
        if result.stdout:
            print(result.stdout)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e}")
        if e.stdout:
            print(f"STDOUT: {e.stdout}")
        if e.stderr:
            print(f"STDERR: {e.stderr}")
        return False

def find_cmake():
    """查找CMake可执行文件"""
    cmake_paths = [
        "cmake",
        "C:\\Program Files\\CMake\\bin\\cmake.exe",
        "C:\\Program Files (x86)\\CMake\\bin\\cmake.exe"
    ]
    
    for cmake_path in cmake_paths:
        try:
            result = subprocess.run([cmake_path, "--version"], check=True, capture_output=True, text=True)
            print(f"Found CMake: {cmake_path}")
            print(f"CMake version: {result.stdout.strip().split()[2]}")
            return cmake_path
        except (subprocess.CalledProcessError, FileNotFoundError):
            continue
    
    return None

def find_visual_studio():
    """查找Visual Studio 2017安装"""
    vs_paths = [
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017",
        "C:\\Program Files\\Microsoft Visual Studio\\2017"
    ]
    
    for vs_path in vs_paths:
        if os.path.exists(vs_path):
            # 查找具体的版本（Community, Professional, Enterprise）
            for edition in ["Enterprise", "Professional", "Community"]:
                full_path = os.path.join(vs_path, edition)
                if os.path.exists(full_path):
                    print(f"Found Visual Studio 2017 {edition}: {full_path}")
                    return full_path
    
    print("Warning: Visual Studio 2017 not found in standard locations")
    return None

def verify_generated_files(build_dir, project_name="AssemblyReverseProject"):
    """验证生成的文件"""
    print("\n=== Verifying generated files ===")
    
    # 检查.sln文件
    sln_files = glob.glob(os.path.join(build_dir, "*.sln"))
    if sln_files:
        for sln_file in sln_files:
            print(f"✓ Solution file: {sln_file}")
    else:
        print("✗ No .sln files found!")
        return False
    
    # 检查.vcxproj文件
    vcxproj_files = glob.glob(os.path.join(build_dir, "**", "*.vcxproj"), recursive=True)
    if vcxproj_files:
        for vcxproj_file in vcxproj_files:
            print(f"✓ Project file: {vcxproj_file}")
    else:
        print("✗ No .vcxproj files found!")
        return False
    
    # 检查CMake缓存
    cmake_cache = os.path.join(build_dir, "CMakeCache.txt")
    if os.path.exists(cmake_cache):
        print(f"✓ CMake cache: {cmake_cache}")
    else:
        print("✗ CMakeCache.txt not found!")
        return False
    
    return True

def main():
    parser = argparse.ArgumentParser(description="Bootstrap script for Assembly Reverse Project")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"], 
                       help="Build configuration (default: Debug)")
    parser.add_argument("--clean", action="store_true", help="Clean build directory before building")
    parser.add_argument("--generator", default="Visual Studio 15 2017", 
                       help="CMake generator (default: Visual Studio 15 2017)")
    parser.add_argument("--arch", default="x64", choices=["Win32", "x64"], 
                       help="Target architecture (default: x64)")
    parser.add_argument("--generate-only", action="store_true", 
                       help="Only generate project files, don't build")
    parser.add_argument("--open-vs", action="store_true", 
                       help="Open Visual Studio after successful generation")
    
    args = parser.parse_args()
    
    # 获取项目根目录
    project_root = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(project_root, "build")
    
    print("=== Assembly Reverse Project Bootstrap ===")
    print(f"Project root: {project_root}")
    print(f"Build directory: {build_dir}")
    print(f"Configuration: {args.config}")
    print(f"Architecture: {args.arch}")
    print(f"Generator: {args.generator}")
    
    # 查找CMake
    cmake_exe = find_cmake()
    if not cmake_exe:
        print("Error: CMake not found. Please install CMake and add it to PATH.")
        print("Download CMake from: https://cmake.org/download/")
        return 1
    
    # 查找Visual Studio（可选，仅用于信息显示）
    find_visual_studio()
    
    # 清理构建目录
    if args.clean and os.path.exists(build_dir):
        print("Cleaning build directory...")
        shutil.rmtree(build_dir)
    
    # 创建构建目录
    os.makedirs(build_dir, exist_ok=True)
    
    # 配置项目
    print("\n=== Configuring project ===")
    generator = args.generator
    if args.arch == "x64":
        generator += " Win64"
    
    print(f"Using generator: {generator}")
    
    configure_cmd = [
        cmake_exe,
        "-G", generator,
        "-DCMAKE_BUILD_TYPE=" + args.config,
        project_root
    ]
    
    if not run_command(configure_cmd, cwd=build_dir):
        print("Configuration failed!")
        return 1
    
    # 验证生成的文件
    if not verify_generated_files(build_dir):
        print("Warning: Some expected files were not generated!")
    
    # 如果只是生成项目文件，则跳过构建
    if args.generate_only:
        print("\n=== Project generation completed! ===")
        sln_files = glob.glob(os.path.join(build_dir, "*.sln"))
        if sln_files:
            print(f"Visual Studio solution: {sln_files[0]}")
            if args.open_vs:
                try:
                    os.startfile(sln_files[0])
                    print("Opening Visual Studio...")
                except Exception as e:
                    print(f"Could not open Visual Studio: {e}")
        return 0
    
    # 构建项目
    print("\n=== Building project ===")
    build_cmd = [
        cmake_exe,
        "--build", ".",
        "--config", args.config
    ]
    
    if not run_command(build_cmd, cwd=build_dir):
        print("Build failed!")
        return 1
    
    print("\n=== Build completed successfully! ===")
    
    # 显示生成的文件位置
    exe_path = os.path.join(build_dir, 'bin', args.config, 'main.exe')
    lib_path = os.path.join(build_dir, 'lib', args.config, 'utils.lib')
    sln_files = glob.glob(os.path.join(build_dir, "*.sln"))
    
    print(f"Executable: {exe_path}")
    if os.path.exists(exe_path):
        print("  ✓ Executable built successfully")
    else:
        print("  ✗ Executable not found")
    
    print(f"Static library: {lib_path}")
    if os.path.exists(lib_path):
        print("  ✓ Static library built successfully")
    else:
        print("  ✗ Static library not found")
    
    if sln_files:
        print(f"Visual Studio solution: {sln_files[0]}")
        print("  ✓ Solution file available")
        
        if args.open_vs:
            try:
                os.startfile(sln_files[0])
                print("  ✓ Opening Visual Studio...")
            except Exception as e:
                print(f"  ✗ Could not open Visual Studio: {e}")
    
    print("\nYou can now:")
    print("1. Run the executable directly")
    print("2. Open the .sln file in Visual Studio 2017")
    print("3. Use the generated project files for debugging")
    
    return 0

if __name__ == "__main__":
    sys.exit(main()) 