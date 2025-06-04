# Assembly Reverse Engineering Test Project

这是一个专门为汇编逆向工程设计的C语言测试项目。该项目包含了丰富的C语言特性，能够生成多样化的汇编指令，用于测试C语言到汇编的转换以及汇编逆向到C语言的准确性。

## 项目结构

```
AssemblyReverse/
├── CMakeLists.txt          # CMake构建配置文件
├── bootstrap.py            # Python构建脚本
├── build.bat              # Windows批处理构建脚本
├── extract_lib.py          # 库文件提取脚本
├── extract_lib.bat         # 库文件提取批处理脚本
├── README.md              # 项目说明文档
├── USAGE.md               # 快速使用指南
├── .gitignore             # Git忽略文件
├── include/               # 头文件目录
│   └── utils.h           # 工具类头文件
├── src/                  # 源代码目录
│   ├── main.c            # 主程序文件
│   └── utils.c           # 工具类实现文件
└── build/                # 构建输出目录（自动生成）
    ├── AssemblyReverseProject.sln  # Visual Studio解决方案
    ├── bin/              # 可执行文件输出目录
    └── lib/              # 静态库输出目录
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

## 功能特性

该项目覆盖了以下C语言特性，确保生成的汇编代码具有最大的指令覆盖率：

### 1. 基础数据类型和运算
- 整数运算（int, short, long）
- 浮点运算（float, double）
- 字符和字符串操作
- 布尔类型操作

### 2. 位运算操作
- 按位与、或、异或、非
- 左移、右移操作
- 位域操作

### 3. 控制流结构
- if/else条件语句
- switch/case语句
- for循环
- while循环
- do-while循环
- goto语句

### 4. 函数和调用约定
- 普通函数调用
- 递归函数调用
- 函数指针和回调函数
- 变参函数（variadic functions）
- 内联函数
- **函数参数传递测试**：
  - 无参数函数
  - 单参数函数（不同类型：int, float, double, char, bool, pointer）
  - 双参数函数（相同类型和混合类型）
  - 三到八参数函数（混合类型组合）
  - 大量参数函数（超过寄存器数量，测试栈传递）
  - 结构体参数传递（按值和按指针）
  - 数组参数传递（不同声明方式）
  - 函数指针参数传递
  - 复杂混合参数（结构体+函数指针+数组+基础类型）
  - 递归函数参数传递
  - 参数传递性能基准测试

### 5. 数据结构
- 结构体（struct）
- 联合体（union）
- 枚举（enum）
- 数组操作
- 指针算术

### 6. 内存管理
- 动态内存分配（malloc/free）
- 内存复制和设置
- 指针操作和解引用

### 7. 高级特性
- 链表数据结构
- 文件I/O操作
- 类型转换
- 宏定义和预处理器指令
- 静态和全局变量
- 常量定义

## 测试模块目录

该项目包含18个测试模块，按执行顺序详细列出如下：

### 1. 函数参数传递测试 (Testing Function Parameter Passing)
**重点测试模块** - 专门测试各种函数调用约定和参数传递机制

#### 1.1 无参数函数
- `no_params_function()` - 无参数整数返回函数
- `void_no_params_function()` - 无参数void函数

#### 1.2 单参数函数（不同类型）
- `single_int_param(int)` - 单个整数参数
- `single_float_param(float)` - 单个浮点参数
- `single_double_param(double)` - 单个双精度参数
- `single_char_param(char)` - 单个字符参数
- `single_bool_param(bool)` - 单个布尔参数
- `single_pointer_param(void*)` - 单个指针参数

#### 1.3 双参数函数
**相同类型：**
- `two_int_params(int, int)` - 两个整数参数
- `two_float_params(float, float)` - 两个浮点参数
- `two_double_params(double, double)` - 两个双精度参数

**混合类型：**
- `int_float_params(int, float)` - 整数+浮点
- `float_double_params(float, double)` - 浮点+双精度
- `int_char_params(int, char)` - 整数+字符
- `int_double_params(int, double)` - 整数+双精度

#### 1.4 三参数函数（混合类型）
- `three_mixed_params_1(int, float, char)` - 整数+浮点+字符
- `three_mixed_params_2(double, int, bool)` - 双精度+整数+布尔
- `three_mixed_params_3(char, int, float)` - 字符+整数+浮点

#### 1.5 四参数函数（混合类型）
- `four_mixed_params_1(int, float, double, char)` - 四种基础类型
- `four_mixed_params_2(char, int, float, bool)` - 字符+整数+浮点+布尔
- `four_mixed_params_3(bool, double, int, char)` - 布尔+双精度+整数+字符

#### 1.6 五参数函数（混合类型）
- `five_mixed_params_1(int, float, double, char, bool)` - 五种基础类型
- `five_mixed_params_2(bool, char, int, double, float)` - 五种类型不同顺序

#### 1.7 六参数函数（混合类型）
- `six_mixed_params_1(int, float, double, char, bool, short)` - 六种类型组合1
- `six_mixed_params_2(short, bool, char, double, float, int)` - 六种类型组合2

#### 1.8 七参数函数（混合类型）
- `seven_mixed_params(int, float, double, char, bool, short, long)` - 七种类型

#### 1.9 八参数函数（混合类型）
- `eight_mixed_params(int, float, double, char, bool, short, long, unsigned int)` - 八种类型

#### 1.10 大量参数函数（栈传递测试）
- `many_int_params(int×10)` - 10个整数参数（测试栈传递）
- `many_float_params(float×8)` - 8个浮点参数
- `many_double_params(double×6)` - 6个双精度参数

#### 1.11 结构体参数传递
- `struct_by_value_param(Point)` - 小结构体按值传递
- `struct_by_pointer_param(Point*)` - 小结构体按指针传递
- `large_struct_by_value(Rectangle)` - 大结构体按值传递
- `large_struct_by_pointer(Rectangle*)` - 大结构体按指针传递

#### 1.12 数组参数传递
- `array_param_1(int[])` - 数组参数（方式1）
- `array_param_2(int[10])` - 固定大小数组参数
- `array_param_3(int*, size_t)` - 指针+大小参数
- `multidim_array_param(int[3][3])` - 多维数组参数

#### 1.13 函数指针参数
- `function_pointer_param_1(int(*)(int))` - 单参数函数指针
- `function_pointer_param_2(int(*)(int,int), int, int)` - 双参数函数指针
- `callback_with_multiple_params(void(*)(int,float,char), ...)` - 多参数回调

#### 1.14 复杂混合参数
- `complex_mixed_params_1(int, Point, float*, size_t, bool)` - 基础类型+结构体+数组
- `complex_mixed_params_2(Rectangle*, int(*)(int), double, char*)` - 结构体指针+函数指针+字符串
- `complex_mixed_params_3(Person, int*, CallbackFunc, VariantData*)` - 复杂结构体+回调+联合体

#### 1.15 递归函数参数传递
- `recursive_param_test_1(int, int)` - 递归累加测试
- `recursive_param_test_2(double, int, double)` - 递归幂运算测试
- `recursive_param_test_3(Node*, int, int*)` - 递归链表遍历测试

#### 1.16 参数传递性能基准测试
- `param_passing_benchmark_1(int×10)` - 大量整数参数性能测试
- `param_passing_benchmark_2(double×8)` - 大量浮点参数性能测试
- `param_passing_benchmark_3(Point×4, Rectangle×2)` - 大量结构体参数性能测试

### 2. 基础数学运算测试 (Testing Basic Math Operations)
- `add_integers(int, int)` - 整数加法
- `add_floats(float, float)` - 浮点加法
- `add_doubles(double, double)` - 双精度加法
- `subtract_integers(int, int)` - 整数减法
- `multiply_integers(int, int)` - 整数乘法
- `divide_floats(float, float)` - 浮点除法
- `modulo_operation(int, int)` - 取模运算
- `power_operation(double, int)` - 幂运算

### 3. 位运算测试 (Testing Bitwise Operations)
- `bitwise_and(unsigned int, unsigned int)` - 按位与
- `bitwise_or(unsigned int, unsigned int)` - 按位或
- `bitwise_xor(unsigned int, unsigned int)` - 按位异或
- `bitwise_not(unsigned int)` - 按位非
- `left_shift(unsigned int, int)` - 左移
- `right_shift(unsigned int, int)` - 右移

### 4. 条件和循环测试 (Testing Conditional and Loop Operations)
- `test_if_conditions(int)` - if/else条件测试
- `test_switch_statement(Color)` - switch/case测试
- `test_for_loop(int, int)` - for循环测试
- `test_while_loop(int, int)` - while循环测试
- `test_do_while_loop(int)` - do-while循环测试

### 5. 数组和指针操作测试 (Testing Array and Pointer Operations)
- `array_operations(int*, size_t)` - 数组操作（初始化、排序）
- `pointer_arithmetic(int*, size_t)` - 指针算术运算
- `string_operations(char*, const char*, size_t)` - 字符串操作

### 6. 结构体操作测试 (Testing Structure Operations)
- `create_point(int, int)` - 点结构体创建
- `create_rectangle(Point, Point, Color)` - 矩形结构体创建
- `create_person(const char*, int, float, double)` - 人员结构体创建
- `print_person(const Person*)` - 结构体打印
- `compare_persons(const Person*, const Person*)` - 结构体比较

### 7. 链表操作测试 (Testing Linked List Operations)
- `create_linked_list()` - 链表创建
- `add_node(LinkedList*, int)` - 节点添加
- `remove_node(LinkedList*, int)` - 节点删除
- `find_node(LinkedList*, int)` - 节点查找
- `print_list(const LinkedList*)` - 链表打印
- `destroy_linked_list(LinkedList*)` - 链表销毁

### 8. 内存管理测试 (Testing Memory Management)
- `safe_malloc(size_t)` - 安全内存分配
- `safe_realloc(void*, size_t)` - 安全内存重分配
- `safe_free(void**)` - 安全内存释放
- `memory_copy(void*, const void*, size_t)` - 内存复制
- `memory_set(void*, int, size_t)` - 内存设置

### 9. 递归函数测试 (Testing Recursive Functions)
- `factorial_recursive(int)` - 递归阶乘
- `fibonacci_recursive(int)` - 递归斐波那契
- `gcd_recursive(int, int)` - 递归最大公约数
- `binary_search_recursive(int*, int, int, int, int*)` - 递归二分查找

### 10. 函数指针和回调测试 (Testing Function Pointers and Callbacks)
- `sort_array(int*, size_t, CompareFunc)` - 使用函数指针排序
- `process_array(int*, size_t, CallbackFunc)` - 数组回调处理
- `generic_processor(void*, size_t, ProcessFunc)` - 通用处理器

### 11. 变参函数测试 (Testing Variadic Functions)
- `sum_integers(int, ...)` - 变参整数求和
- `print_formatted(const char*, ...)` - 变参格式化打印

### 12. 复杂控制流测试 (Testing Complex Control Flow)
- `complex_nested_loops(int[10][10], int, int)` - 复杂嵌套循环
- `goto_example(int*, size_t, int)` - goto语句示例
- `nested_switch_if(int, int, char)` - 嵌套switch-if结构

### 13. 类型转换和安全函数测试 (Testing Type Conversion and Safety)
- `safe_int_to_string(int, char*, size_t)` - 安全整数转字符串
- `safe_string_to_int(const char*, int*)` - 安全字符串转整数
- `variant_data_operations(VariantData*)` - 变体数据操作

### 14. 位域和联合体测试 (Testing Bitfields and Unions)
- `bitfield_operations(BitField*)` - 位域操作
- `union_operations(DataUnion*)` - 联合体操作

### 15. 静态和全局变量测试 (Testing Static and Global Variables)
- `increment_global_counter()` - 全局变量递增
- `get_static_value()` - 静态变量访问
- 全局变量：`global_counter`, `CONSTANT_VALUE`, `CONSTANT_STRING`, `ORIGIN_POINT`

### 16. 内联函数和宏测试 (Testing Inline Functions and Macros)
- `inline_max(int, int)` - 内联最大值函数
- `is_even(int)` - 内联偶数判断函数
- 宏测试：`SQUARE(x)`, `MAX(a,b)`, `MIN(a,b)`, `ARRAY_SIZE(arr)`

### 17. 常量测试 (Testing Constants)
- 常量值访问和使用
- 编译时常量和运行时常量
- 不同类型常量的内存布局

### 18. 平台信息测试 (Platform Information)
- 平台相关宏定义测试
- 条件编译指令测试
- 平台特定代码路径

## 汇编指令覆盖率

通过以上18个测试模块，项目能够生成以下汇编指令类型：

### 参数传递和调用约定指令
- **寄存器传递**：MOV RCX, MOV RDX, MOV R8, MOV R9（Windows x64前4个整数参数）
- **浮点寄存器**：MOVSS XMM0, MOVSD XMM1（浮点参数传递）
- **栈传递**：PUSH, SUB RSP（大量参数时的栈传递）
- **函数调用**：CALL, RET
- **栈帧管理**：PUSH RBP, MOV RBP RSP, POP RBP, ADD RSP

### 算术和逻辑指令
- **整数运算**：ADD, SUB, MUL, DIV, MOD, INC, DEC
- **浮点运算**：FADD, FSUB, FMUL, FDIV, ADDSS, SUBSS, MULSS, DIVSS
- **位运算**：AND, OR, XOR, NOT, SHL, SHR
- **比较指令**：CMP, TEST

### 控制流指令
- **条件跳转**：JE, JNE, JL, JLE, JG, JGE, JA, JB, JC, JNC
- **无条件跳转**：JMP
- **循环指令**：LOOP, LOOPE, LOOPNE

### 内存操作指令
- **数据移动**：MOV, MOVZX, MOVSX
- **地址计算**：LEA
- **内存访问**：各种寻址模式（直接、间接、基址+偏移、索引等）

## 构建要求

### 系统要求
- Windows 10 或更高版本
- Visual Studio 2017 或更高版本
- CMake 3.8 或更高版本
- Python 3.6 或更高版本

### 依赖项
- Microsoft Visual C++ 编译器
- CMake构建系统
- Python解释器

## 构建方法

### 方法1：使用Python构建脚本（推荐）

```bash
# 基本构建（Debug模式）
python bootstrap.py

# 指定构建配置
python bootstrap.py --config Release

# 指定目标架构
python bootstrap.py --arch x64

# 清理并重新构建
python bootstrap.py --clean

# 只生成VS2017项目文件，不构建
python bootstrap.py --generate-only

# 生成项目文件并自动打开Visual Studio
python bootstrap.py --generate-only --open-vs

# 查看所有选项
python bootstrap.py --help
```

### 方法2：使用Windows批处理脚本

```bash
# 基本构建
.\build.bat

# 构建Release版本
.\build.bat release

# 清理并重新构建
.\build.bat clean

# 只生成VS2017项目文件
.\build.bat generate

# 生成Release配置的项目文件
.\build.bat generate-release

# 生成项目文件并打开Visual Studio
.\build.bat open

# 生成Release项目文件并打开Visual Studio
.\build.bat open-release
```

### 方法3：手动使用CMake

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目（VS2017 x64）
cmake -G "Visual Studio 15 2017 Win64" ..

# 构建项目
cmake --build . --config Debug

# 或者构建Release版本
cmake --build . --config Release
```

## Visual Studio 2017 项目文件

bootstrap脚本会自动生成完整的Visual Studio 2017解决方案文件：

- **解决方案文件**：`build/AssemblyReverseProject.sln`
- **主程序项目**：`build/main.vcxproj`
- **静态库项目**：`build/utils.vcxproj`
- **项目依赖关系**：自动配置正确的依赖关系

### 在Visual Studio中使用

1. 运行 `python bootstrap.py --generate-only` 或 `.\build.bat generate`
2. 打开 `build/AssemblyReverseProject.sln`
3. 在Visual Studio中可以：
   - 设置断点调试
   - 查看汇编代码（调试 → 窗口 → 反汇编）
   - 分析内存布局
   - 使用性能分析工具

## 库文件提取和汇编分析

项目提供了专门的工具来提取静态库中的目标文件(.obj)并生成汇编文件(.asm)，同时支持将debug库转换为release库：

### 使用Python脚本提取和转换

#### 基本提取功能
```bash
# 从Debug构建提取
python extract_lib.py

# 从Release构建提取
python extract_lib.py --config Release

# 清理并重新提取
python extract_lib.py --clean

# 指定自定义库文件
python extract_lib.py --lib-file path/to/custom.lib

# **新功能：同时处理Debug和Release两个配置**
python extract_lib.py --process-both

# 查看所有选项
python extract_lib.py --help
```

#### **新功能：同时处理Debug和Release配置**

该脚本现在支持一次性处理Debug和Release两个配置的库文件，自动提取、反汇编并生成对比报告：

```bash
# 基本用法：同时处理两个配置
python extract_lib.py --process-both

# 同时处理并清理旧输出
python extract_lib.py --process-both --clean

# 指定自定义输出目录
python extract_lib.py --process-both --output-dir my_analysis
```

**同时处理功能特性：**
- **自动检测**：自动查找Debug和Release库文件
- **智能跳过**：如果某个配置不存在，会跳过并继续处理另一个
- **并行处理**：同时处取两个配置的.obj和.asm文件
- **对比分析**：自动生成两个配置的详细对比报告
- **完整报告**：每个配置都有独立的提取报告

**生成的目录结构：**
```
extracted/
├── debug/
│   ├── obj/                   # Debug .obj文件
│   ├── asm/                   # Debug .asm文件
│   └── extraction_report.txt  # Debug提取报告
├── release/
│   ├── obj/                   # Release .obj文件
│   ├── asm/                   # Release .asm文件
│   └── extraction_report.txt  # Release提取报告
└── comparison_report.txt       # 自动生成的对比报告
```

**对比报告内容：**
- 库文件大小对比和差异百分比
- .obj文件数量和总大小对比
- .asm文件数量和大小统计
- 符号分析和差异统计
- 完整的目录结构说明

#### **Debug库转换为Release库**

该脚本还支持将debug静态库转换为release版本，通过移除调试信息来减小文件大小：

```bash
# 基本转换：将debug库转换为release库
python extract_lib.py --convert-to-release

# 转换并分析差异
python extract_lib.py --convert-to-release --analyze-diff

# 指定输入和输出文件
python extract_lib.py \
    --lib-file build/lib/Debug/utils.lib \
    --convert-to-release \
    --release-lib-output build/lib/Release/utils.lib

# 完整工作流程：转换 -> 分析 -> 提取
python extract_lib.py --convert-to-release --analyze-diff
python extract_lib.py --lib-file utils_release.lib --output-dir extracted_release
```

#### 转换功能特性

**转换过程：**
1. **提取**：从debug库中提取所有.obj文件
2. **处理**：使用`editbin.exe`移除调试段（.debug$S, .debug$T, .debug$F）
3. **重建**：使用`lib.exe`从处理后的.obj文件创建新库
4. **分析**：可选的差异分析

**预期效果：**
- **文件大小减少**：通常减少30-70%
- **移除调试信息**：不包含源码路径、行号等敏感信息
- **保持功能完整**：所有函数和符号保持可用
- **优化分发**：更适合发布和分发

**示例输出：**
```
=== Converting debug library to release library ===
Source (Debug): build/lib/Debug/utils.lib
Target (Release): build/lib/Debug/utils_release.lib

Step 1: Extracting .obj files from debug library...
Found 5 .obj files:
  - utils.obj
  - math_ops.obj
  - string_ops.obj
  - file_ops.obj
  - memory_ops.obj

Step 2: Processing .obj files to remove debug information...
✓ Processed: utils.obj
✓ Processed: math_ops.obj
✓ Processed: string_ops.obj
✓ Processed: file_ops.obj
✓ Processed: memory_ops.obj

Step 3: Creating release library...
Creating library with 5 object files...
✓ Created release library: utils_release.lib

=== Analyzing library differences ===
Debug library size: 2,458,624 bytes
Release library size: 892,416 bytes
Size reduction: 1,566,208 bytes (63.7%)
Debug symbols count: 1,247
Release symbols count: 856

✓ Successfully converted debug library to release library
```

#### 命令行选项

| 选项 | 描述 |
|------|------|
| `--convert-to-release` | 启用debug到release转换模式 |
| `--release-lib-output PATH` | 指定release库的输出路径 |
| `--analyze-diff` | 分析debug和release库的差异 |
| `--lib-file PATH` | 指定输入库文件路径 |
| `--config {Debug,Release}` | 构建配置（默认：Debug） |
| `--output-dir DIR` | 提取文件的输出目录 |
| `--clean` | 清理输出目录 |
| `--process-both` | **新功能**：同时处理Debug和Release两个配置 |

#### 工具要求

转换功能需要以下Microsoft Visual Studio工具：
- `lib.exe` - Microsoft库管理器
- `editbin.exe` - Microsoft二进制编辑器  
- `dumpbin.exe` - Microsoft二进制分析器（用于差异分析）

这些工具随Visual Studio自动安装。

### 使用批处理脚本提取

```bash
# 从Debug构建提取
.\extract_lib.bat

# 从Release构建提取
.\extract_lib.bat release

# 清理并重新提取
.\extract_lib.bat clean

# 清理并从Release构建提取
.\extract_lib.bat clean-release
```

### 提取结果

提取完成后，会根据不同的操作模式在`extracted/`目录下生成相应的子目录结构：

#### 转换模式（Debug到Release转换）

```
extracted/
└── conversion/
    ├── debug/
    │   └── obj/                # 原始debug .obj文件
    │       ├── utils.obj
    │       └── ...
    ├── release/
    │   └── obj/                # 处理后的release .obj文件
    │       ├── utils.obj
    │       └── ...
    └── conversion_report.txt   # 转换报告
```

#### 提取模式（根据配置区分）

```
extracted/
├── debug/                      # Debug配置的提取结果
│   ├── obj/                   # 提取的.obj文件
│   │   ├── utils.obj
│   │   └── ...
│   ├── asm/                   # 生成的.asm文件
│   │   ├── utils.asm
│   │   └── ...
│   └── extraction_report.txt  # 提取报告
└── release/                    # Release配置的提取结果
    ├── obj/                   # 提取的.obj文件
    │   ├── utils.obj
    │   └── ...
    ├── asm/                   # 生成的.asm文件
    │   ├── utils.asm
    │   └── ...
    └── extraction_report.txt  # 提取报告
```

这种目录结构的优势：
- **清晰分离**：Debug和Release文件分别存储，避免混淆
- **便于比较**：可以直接对比debug和release版本的差异
- **模块化组织**：转换操作和提取操作分别组织
- **可追溯性**：每个操作都有相应的报告文件

### 转换用例

#### 1. 同时分析两个配置（推荐）
```bash
# 一次性处理Debug和Release配置
python extract_lib.py --process-both

# 结果：
# extracted/debug/        - Debug版本的完整分析
# extracted/release/      - Release版本的完整分析  
# extracted/comparison_report.txt - 自动生成的对比报告
```

#### 2. 开发到发布工作流
```bash
# 开发阶段：使用debug库进行开发和调试
python bootstrap.py --config Debug

# 发布阶段：转换为release库
python extract_lib.py --convert-to-release --analyze-diff

# 结果：extracted/conversion/目录包含debug和release的.obj文件对比
# 分发：使用更小的release库
```

#### 3. 库文件优化比较
```bash
# 方法1：使用新的同时处理功能（推荐）
python extract_lib.py --process-both

# 方法2：分别提取两个版本
python extract_lib.py --config Debug --output-dir extracted
python extract_lib.py --config Release --output-dir extracted

# 现在可以比较extracted/debug/和extracted/release/目录中的差异
```

#### 4. Debug到Release转换分析
```bash
# 转换debug库到release并保存中间文件
python extract_lib.py --convert-to-release --analyze-diff

# 查看转换结果：
# - extracted/conversion/debug/obj/     - 原始debug .obj文件
# - extracted/conversion/release/obj/   - 处理后的release .obj文件  
# - extracted/conversion/conversion_report.txt - 详细转换报告
```

#### 5. 逆向工程准备
```bash
# 方法1：准备两个配置进行对比分析
python extract_lib.py --process-both --output-dir reverse_analysis

# 方法2：准备清洁的release版本
python extract_lib.py --convert-to-release --release-lib-output clean_version.lib
python extract_lib.py --lib-file clean_version.lib --config Release --output-dir clean_extracted

# 结果：clean_extracted/release/目录包含清洁的分析文件
```

#### 6. 高级分析工作流
```bash
# 完整的分析流程
# 1. 构建两个配置
python bootstrap.py --config Debug
python bootstrap.py --config Release

# 2. 同时处理两个配置
python extract_lib.py --process-both --clean

# 3. 执行debug到release转换
python extract_lib.py --convert-to-release --analyze-diff

# 4. 现在拥有三种不同的分析结果：
# extracted/debug/        - Debug版本直接提取结果
# extracted/release/      - Release版本直接提取结果  
# extracted/conversion/   - Debug转Release的处理过程
# extracted/comparison_report.txt - Debug vs Release对比报告
```

## 运行程序

构建完成后，可执行文件位于：
- Debug版本：`build/bin/Debug/main.exe`
- Release版本：`build/bin/Release/main.exe`

直接运行可执行文件：
```bash
# 进入构建目录
cd build/bin/Debug

# 运行程序
./main.exe
```

## 输出文件

构建过程会生成以下文件：

1. **静态库**：`build/lib/Debug/utils.lib` 或 `build/lib/Release/utils.lib`
2. **可执行文件**：`build/bin/Debug/main.exe` 或 `build/bin/Release/main.exe`
3. **Visual Studio解决方案**：`build/AssemblyReverseProject.sln`
4. **项目文件**：`build/main.vcxproj`, `build/utils.vcxproj`
5. **提取的文件**：`extracted/obj/` 和 `extracted/asm/`

## 汇编分析

为了进行汇编分析，可以：

1. **在Visual Studio中查看汇编**：
   - 打开解决方案文件
   - 设置断点并开始调试
   - 右键选择"转到反汇编"

2. **使用提取的汇编文件**：
   - 运行 `.\extract_lib.bat` 提取汇编代码
   - 查看 `extracted/asm/` 目录中的.asm文件
   - 使用文本编辑器或专门的汇编查看器

3. **生成汇编代码文件**：
   ```bash
   # 使用MSVC编译器生成汇编
   cl /c /Fa src/utils.c
   cl /c /Fa src/main.c
   ```

4. **使用反汇编工具**：
   - IDA Pro
   - Ghidra
   - x64dbg
   - Visual Studio反汇编器

5. **编译器优化级别**：
   - Debug模式：`/Od`（无优化）
   - Release模式：`/O2`（最大优化）

## 测试覆盖的汇编指令类型

该项目设计用于生成以下类型的汇编指令：

### 算术指令
- ADD, SUB, MUL, DIV, MOD
- FADD, FSUB, FMUL, FDIV（浮点运算）
- INC, DEC（递增递减）

### 逻辑和位运算指令
- AND, OR, XOR, NOT
- SHL, SHR（移位操作）
- TEST, CMP（比较操作）

### 控制流指令
- JMP（无条件跳转）
- JE, JNE, JL, JG等（条件跳转）
- CALL, RET（函数调用和返回）
- LOOP（循环指令）

### 内存操作指令
- MOV（数据移动）
- LEA（地址加载）
- PUSH, POP（栈操作）
- 各种寻址模式

### 函数调用和参数传递指令
- **参数传递指令**：
  - MOV（寄存器参数传递）
  - PUSH/POP（栈参数传递）
  - LEA（地址参数传递）
- **调用约定指令**：
  - CALL（函数调用）
  - RET（函数返回）
  - 栈帧建立和清理（PUSH RBP, MOV RBP RSP, POP RBP）
  - 栈指针调整（SUB RSP, ADD RSP）
- **寄存器使用模式**：
  - RCX, RDX, R8, R9（Windows x64前4个整数参数）
  - XMM0-XMM3（浮点参数传递）
  - RAX（返回值）
  - 调用者保存和被调用者保存寄存器

### 浮点指令
- FLD, FST（浮点加载和存储）
- 浮点运算指令
- SSE指令集（现代编译器）

## 逆向工程验证

使用该项目进行逆向工程验证的步骤：

1. **编译生成目标程序**
2. **提取静态库文件**：使用 `extract_lib.py` 或 `extract_lib.bat`
3. **分析汇编代码**：查看生成的.asm文件
4. **使用反汇编工具分析**：IDA Pro, Ghidra等
5. **将汇编代码逆向还原为C代码**
6. **对比原始C代码和逆向结果**
7. **验证逆向的准确性**

## 注意事项

1. **编译器优化**：不同的优化级别会产生不同的汇编代码
2. **调用约定**：注意函数调用的参数传递方式
3. **内存布局**：结构体的内存对齐和填充
4. **平台差异**：x86和x64架构的差异

## 扩展建议

可以通过以下方式扩展项目：

1. **添加更多数据结构**：树、图、哈希表等
2. **增加并发特性**：线程、锁、原子操作
3. **添加系统调用**：文件操作、网络操作
4. **增加异常处理**：setjmp/longjmp
5. **添加内联汇编**：直接嵌入汇编代码

## 许可证

本项目仅用于教育和研究目的。

## 联系信息

如有问题或建议，请通过项目仓库提交Issue。 

#### 7. 错误排查

**常见问题及解决方案：**

1. **"lib.exe not found"** / **"editbin.exe not found"**
   - 确保已安装Visual Studio with C++ tools
   - 检查工具是否在PATH中

2. **"Neither Debug nor Release library files found"**
   - 先构建项目：`python bootstrap.py --config Debug` 和 `python bootstrap.py --config Release`
   - 检查`build/lib/Debug/utils.lib`和`build/lib/Release/utils.lib`是否存在

3. **转换失败**
   - 检查输入库文件是否存在
   - 确认有足够的磁盘空间
   - 验证文件权限

4. **大小减少不明显**
   - 原库可能已经是release版本
   - 检查原库是否在debug模式下编译
   - 查看conversion_report.txt了解详细信息

5. **目录结构混乱**
   - 使用--clean选项清理输出目录
   - 确保使用正确的--config参数
   - 检查--output-dir参数设置

### 集成和扩展

新的同时处理功能与现有功能完全兼容：
- **自动检测**：智能检测可用的配置文件
- **分层组织**：不同操作模式创建相应的目录结构
- **链式操作**：可以对转换后的release库执行提取操作
- **并行分析**：同时提取debug和release版本进行对比
- **向后兼容**：保持所有现有命令行参数的兼容性

**功能组合示例：**
```bash
# 同时处理 + 清理
python extract_lib.py --process-both --clean

# 单独转换 + 同时分析
python extract_lib.py --convert-to-release
python extract_lib.py --process-both --output-dir full_analysis

# 自定义输出 + 对比分析
python extract_lib.py --process-both --output-dir custom_output --clean
``` 