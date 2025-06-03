# 快速使用指南

本指南适用于位于`AssemblyReverse`目录下的汇编逆向工程测试项目。

## 快速开始

### 1. 生成Visual Studio 2017项目文件

```bash
# 方法1：使用Python脚本
python bootstrap.py --generate-only

# 方法2：使用批处理脚本
.\build.bat generate

# 方法3：生成并自动打开Visual Studio
.\build.bat open
```

### 2. 构建项目

```bash
# 构建Debug版本
python bootstrap.py
# 或
.\build.bat

# 构建Release版本
python bootstrap.py --config Release
# 或
.\build.bat release
```

### 3. 提取库文件为.obj和.asm

```bash
# 从Debug构建提取
python extract_lib.py
# 或
.\extract_lib.bat

# 从Release构建提取
python extract_lib.py --config Release
# 或
.\extract_lib.bat release
```

### 4. 运行程序

```bash
# 运行Debug版本
build\bin\Debug\main.exe

# 运行Release版本
build\bin\Release\main.exe
```

## 常用命令

### 构建命令

| 命令 | 功能 |
|------|------|
| `python bootstrap.py` | 构建Debug版本 |
| `python bootstrap.py --config Release` | 构建Release版本 |
| `python bootstrap.py --generate-only` | 只生成项目文件 |
| `python bootstrap.py --generate-only --open-vs` | 生成项目文件并打开VS |
| `python bootstrap.py --clean` | 清理并重新构建 |
| `.\build.bat generate` | 生成VS2017项目文件 |
| `.\build.bat open` | 生成项目文件并打开VS |

### 提取命令

| 命令 | 功能 |
|------|------|
| `python extract_lib.py` | 从Debug构建提取.obj和.asm |
| `python extract_lib.py --config Release` | 从Release构建提取 |
| `python extract_lib.py --clean` | 清理并重新提取 |
| `.\extract_lib.bat` | 从Debug构建提取（批处理） |
| `.\extract_lib.bat release` | 从Release构建提取（批处理） |
| `.\extract_lib.bat clean` | 清理并重新提取（批处理） |

## 生成的文件

### 构建文件

构建完成后，您将得到：

```
build/
├── AssemblyReverseProject.sln    # Visual Studio 2017解决方案
├── main.vcxproj                  # 主程序项目文件
├── utils.vcxproj                 # 静态库项目文件
├── bin/
│   ├── Debug/main.exe           # Debug可执行文件
│   └── Release/main.exe         # Release可执行文件
└── lib/
    ├── Debug/utils.lib          # Debug静态库
    └── Release/utils.lib        # Release静态库
```

### 提取文件

提取完成后，您将得到：

```
extracted/
├── obj/                         # 提取的目标文件
│   ├── utils.obj               # 主要的目标文件
│   └── ...                     # 其他目标文件
├── asm/                         # 生成的汇编文件
│   ├── utils.asm               # 反汇编代码
│   └── ...                     # 其他汇编文件
└── extraction_report.txt        # 提取报告
```

## 在Visual Studio中使用

1. 运行 `.\build.bat generate` 生成项目文件
2. 双击打开 `build\AssemblyReverseProject.sln`
3. 在Visual Studio中：
   - 按F5开始调试
   - 设置断点查看变量
   - 使用"调试 → 窗口 → 反汇编"查看汇编代码
   - 使用"调试 → 窗口 → 内存"查看内存布局

## 汇编分析

### 查看汇编代码的方法：

1. **使用提取的汇编文件**（推荐）
   - 运行 `.\extract_lib.bat` 提取汇编代码
   - 打开 `extracted\asm\utils.asm` 查看反汇编代码
   - 使用文本编辑器或专门的汇编查看器

2. **Visual Studio反汇编窗口**
   - 在调试时右键选择"转到反汇编"
   - 或使用菜单：调试 → 窗口 → 反汇编

3. **生成汇编文件**
   ```bash
   # 进入源代码目录
   cd src
   
   # 生成汇编文件
   cl /c /Fa main.c
   cl /c /Fa utils.c
   
   # 查看生成的.asm文件
   ```

4. **使用外部工具**
   - IDA Pro
   - Ghidra
   - x64dbg

## 完整工作流程

### 典型的汇编逆向工程工作流程：

1. **构建项目**
   ```bash
   .\build.bat
   ```

2. **提取汇编代码**
   ```bash
   .\extract_lib.bat
   ```

3. **分析汇编代码**
   - 查看 `extracted\asm\utils.asm`
   - 分析函数结构和指令序列
   - 识别编译器优化模式

4. **对比不同优化级别**
   ```bash
   # 构建Release版本
   .\build.bat release
   
   # 提取Release版本的汇编代码
   .\extract_lib.bat release
   
   # 对比Debug和Release的汇编差异
   ```

5. **逆向工程验证**
   - 根据汇编代码重构C代码
   - 对比原始源代码
   - 验证逆向的准确性

## 故障排除

### 常见问题：

1. **CMake未找到**
   - 下载并安装CMake：https://cmake.org/download/
   - 确保CMake在PATH环境变量中

2. **Visual Studio 2017未找到**
   - 安装Visual Studio 2017或更高版本
   - 确保安装了C++开发工具

3. **Python未找到**
   - 安装Python 3.6或更高版本
   - 确保Python在PATH环境变量中

4. **构建失败**
   - 运行 `python bootstrap.py --clean` 清理重建
   - 检查错误信息并确保所有依赖项已安装

5. **提取失败**
   - 确保已经构建了项目（存在utils.lib文件）
   - 检查Visual Studio工具链是否正确安装
   - 运行 `python extract_lib.py --help` 查看详细选项

### 获取帮助：

```bash
# 查看构建选项
python bootstrap.py --help

# 查看提取选项
python extract_lib.py --help
```

## 项目特点

这个项目专门设计用于汇编逆向工程研究，包含：

- ✅ 18个测试模块，覆盖所有主要C语言特性
- ✅ 1200+行工具类代码，400+行主程序代码
- ✅ 完整的Visual Studio 2017项目支持
- ✅ Debug和Release两种构建配置
- ✅ 静态库和可执行文件分离
- ✅ 自动化的.obj和.asm文件提取
- ✅ 丰富的汇编指令覆盖率
- ✅ 详细的提取报告和文档
- ✅ **专门的函数参数传递测试模块**
- ✅ **多种调用约定和参数传递模式测试**

适用于：
- C语言到汇编的转换研究
- 汇编逆向工程的准确性验证
- 编译器优化效果分析
- 汇编指令覆盖率测试
- 静态库文件分析
- 目标文件格式研究
- **函数调用约定分析**
- **参数传递机制研究** 