#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// 宏定义
#define MAX_BUFFER_SIZE 1024
#define PI 3.14159265359
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// 条件编译宏
#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__linux__)
    #define PLATFORM_LINUX
#else
    #define PLATFORM_UNKNOWN
#endif

// 枚举类型
typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_ERROR = -1,
    STATUS_INVALID_PARAM = -2,
    STATUS_OUT_OF_MEMORY = -3,
    STATUS_FILE_NOT_FOUND = -4
} Status;

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_WHITE,
    COLOR_BLACK
} Color;

typedef enum {
    OPERATION_ADD = 1,
    OPERATION_SUBTRACT = 2,
    OPERATION_MULTIPLY = 4,
    OPERATION_DIVIDE = 8,
    OPERATION_MODULO = 16
} MathOperation;

// 结构体定义
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point top_left;
    Point bottom_right;
    Color color;
} Rectangle;

typedef struct {
    char name[64];
    int age;
    float height;
    double weight;
    bool is_active;
    Color favorite_color;
} Person;

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t count;
} LinkedList;

typedef union {
    int i;
    float f;
    double d;
    char c[8];
} DataUnion;

typedef struct {
    DataUnion value;
    enum { TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_STRING } type;
} VariantData;

// 函数指针类型定义
typedef int (*CompareFunc)(const void* a, const void* b);
typedef void (*CallbackFunc)(int value);
typedef Status (*ProcessFunc)(void* data, size_t size);

// ============================================================================
// 函数参数传递测试函数
// ============================================================================

// 无参数函数
int no_params_function(void);
void void_no_params_function(void);

// 单参数函数 - 不同类型
int single_int_param(int value);
float single_float_param(float value);
double single_double_param(double value);
char single_char_param(char value);
bool single_bool_param(bool value);
void* single_pointer_param(void* ptr);

// 双参数函数 - 相同类型
int two_int_params(int a, int b);
float two_float_params(float a, float b);
double two_double_params(double a, double b);

// 双参数函数 - 不同类型
int int_float_params(int a, float b);
float float_double_params(float a, double b);
int int_char_params(int a, char b);
double int_double_params(int a, double b);

// 三参数函数 - 混合类型
int three_mixed_params_1(int a, float b, char c);
float three_mixed_params_2(double a, int b, bool c);
char three_mixed_params_3(char a, int b, float c);

// 四参数函数 - 混合类型
int four_mixed_params_1(int a, float b, double c, char d);
double four_mixed_params_2(char a, int b, float c, bool d);
bool four_mixed_params_3(bool a, double b, int c, char d);

// 五参数函数 - 混合类型
int five_mixed_params_1(int a, float b, double c, char d, bool e);
float five_mixed_params_2(bool a, char b, int c, double d, float e);

// 六参数函数 - 混合类型
int six_mixed_params_1(int a, float b, double c, char d, bool e, short f);
double six_mixed_params_2(short a, bool b, char c, double d, float e, int f);

// 七参数函数 - 混合类型
int seven_mixed_params(int a, float b, double c, char d, bool e, short f, long g);

// 八参数函数 - 混合类型
double eight_mixed_params(int a, float b, double c, char d, bool e, short f, long g, unsigned int h);

// 大量参数函数（超过寄存器数量，测试栈传递）
int many_int_params(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10);
float many_float_params(float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8);
double many_double_params(double p1, double p2, double p3, double p4, double p5, double p6);

// 结构体参数传递
Point struct_by_value_param(Point p);
Point struct_by_pointer_param(Point* p);
Rectangle large_struct_by_value(Rectangle rect);
Rectangle large_struct_by_pointer(Rectangle* rect);

// 数组参数传递
int array_param_1(int arr[]);
int array_param_2(int arr[10]);
int array_param_3(int* arr, size_t size);
int multidim_array_param(int matrix[3][3]);

// 函数指针参数
int function_pointer_param_1(int (*func)(int));
int function_pointer_param_2(int (*func)(int, int), int a, int b);
void callback_with_multiple_params(void (*callback)(int, float, char), int a, float b, char c);

// 混合复杂参数
int complex_mixed_params_1(int a, Point p, float* arr, size_t size, bool flag);
double complex_mixed_params_2(Rectangle* rect, int (*func)(int), double d, char* str);
Status complex_mixed_params_3(Person person, int* results, CallbackFunc callback, VariantData* data);

// 参数传递性能测试函数
int param_passing_benchmark_1(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
double param_passing_benchmark_2(double a, double b, double c, double d, double e, double f, double g, double h);
Status param_passing_benchmark_3(Point p1, Point p2, Point p3, Point p4, Rectangle r1, Rectangle r2);

// 递归函数参数传递测试
int recursive_param_test_1(int n, int accumulator);
double recursive_param_test_2(double base, int exponent, double result);
Status recursive_param_test_3(Node* node, int depth, int* max_depth);

// ============================================================================
// 基础数学运算函数
// ============================================================================
int add_integers(int a, int b);
float add_floats(float a, float b);
double add_doubles(double a, double b);
int subtract_integers(int a, int b);
int multiply_integers(int a, int b);
float divide_floats(float a, float b);
int modulo_operation(int a, int b);
double power_operation(double base, int exponent);

// 位运算函数
unsigned int bitwise_and(unsigned int a, unsigned int b);
unsigned int bitwise_or(unsigned int a, unsigned int b);
unsigned int bitwise_xor(unsigned int a, unsigned int b);
unsigned int bitwise_not(unsigned int a);
unsigned int left_shift(unsigned int value, int positions);
unsigned int right_shift(unsigned int value, int positions);

// 条件和循环测试函数
Status test_if_conditions(int value);
Status test_switch_statement(Color color);
int test_for_loop(int start, int end);
int test_while_loop(int initial_value, int target);
int test_do_while_loop(int value);

// 数组和指针操作
Status array_operations(int* array, size_t size);
Status pointer_arithmetic(int* ptr, size_t offset);
Status string_operations(char* dest, const char* src, size_t max_len);

// 结构体操作函数
Point create_point(int x, int y);
Rectangle create_rectangle(Point top_left, Point bottom_right, Color color);
Person create_person(const char* name, int age, float height, double weight);
Status print_person(const Person* person);
Status compare_persons(const Person* p1, const Person* p2);

// 链表操作函数
LinkedList* create_linked_list(void);
Status add_node(LinkedList* list, int data);
Status remove_node(LinkedList* list, int data);
Node* find_node(LinkedList* list, int data);
Status print_list(const LinkedList* list);
void destroy_linked_list(LinkedList* list);

// 内存管理函数
void* safe_malloc(size_t size);
void* safe_realloc(void* ptr, size_t new_size);
void safe_free(void** ptr);
Status memory_copy(void* dest, const void* src, size_t size);
Status memory_set(void* ptr, int value, size_t size);

// 文件操作函数
Status read_file_content(const char* filename, char** content, size_t* size);
Status write_file_content(const char* filename, const char* content, size_t size);
Status append_to_file(const char* filename, const char* content);

// 递归函数
int factorial_recursive(int n);
int fibonacci_recursive(int n);
int gcd_recursive(int a, int b);
Status binary_search_recursive(int* array, int target, int left, int right, int* index);

// 函数指针和回调函数
Status sort_array(int* array, size_t size, CompareFunc compare);
Status process_array(int* array, size_t size, CallbackFunc callback);
Status generic_processor(void* data, size_t size, ProcessFunc processor);

// 变参函数
int sum_integers(int count, ...);
Status print_formatted(const char* format, ...);

// 复杂控制流函数
Status complex_nested_loops(int matrix[10][10], int rows, int cols);
Status goto_example(int* array, size_t size, int target);
Status nested_switch_if(int a, int b, char op);

// 类型转换和类型安全函数
Status safe_int_to_string(int value, char* buffer, size_t buffer_size);
Status safe_string_to_int(const char* str, int* value);
Status variant_data_operations(VariantData* data);

// 位域和联合体操作
typedef struct {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int flag3 : 1;
    unsigned int reserved : 5;
    unsigned int value : 24;
} BitField;

Status bitfield_operations(BitField* bf);
Status union_operations(DataUnion* data);

// 静态和全局变量测试
extern int global_counter;
Status increment_global_counter(void);
Status get_static_value(void);

// 内联函数
static inline int inline_max(int a, int b) {
    return (a > b) ? a : b;
}

static inline bool is_even(int n) {
    return (n % 2) == 0;
}

// 常量和只读数据
extern const int CONSTANT_VALUE;
extern const char* const CONSTANT_STRING;
extern const Point ORIGIN_POINT;

#endif // UTILS_H 