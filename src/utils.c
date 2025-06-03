#include "utils.h"
#include <stdarg.h>
#include <math.h>

// 全局变量定义
int global_counter = 0;
const int CONSTANT_VALUE = 42;
const char* const CONSTANT_STRING = "Hello, Assembly World!";
const Point ORIGIN_POINT = {0, 0};

// 静态变量
static int static_counter = 100;

// ============================================================================
// 函数参数传递测试函数实现
// ============================================================================

// 无参数函数
int no_params_function(void) {
    global_counter++;
    return global_counter * 2;
}

void void_no_params_function(void) {
    static_counter += 5;
}

// 单参数函数 - 不同类型
int single_int_param(int value) {
    return value * 2 + 1;
}

float single_float_param(float value) {
    return value * 1.5f + 0.5f;
}

double single_double_param(double value) {
    return value * 2.5 + 1.25;
}

char single_char_param(char value) {
    return (char)(value + 1);
}

bool single_bool_param(bool value) {
    return !value;
}

void* single_pointer_param(void* ptr) {
    // 简单的指针操作，返回偏移后的指针
    return (char*)ptr + sizeof(int);
}

// 双参数函数 - 相同类型
int two_int_params(int a, int b) {
    return (a * b) + (a + b);
}

float two_float_params(float a, float b) {
    return (a * b) - (a - b);
}

double two_double_params(double a, double b) {
    return (a / b) + (a * b);
}

// 双参数函数 - 不同类型
int int_float_params(int a, float b) {
    return a + (int)b;
}

float float_double_params(float a, double b) {
    return a + (float)b;
}

int int_char_params(int a, char b) {
    return a + (int)b;
}

double int_double_params(int a, double b) {
    return (double)a * b;
}

// 三参数函数 - 混合类型
int three_mixed_params_1(int a, float b, char c) {
    return a + (int)b + (int)c;
}

float three_mixed_params_2(double a, int b, bool c) {
    float result = (float)a + (float)b;
    return c ? result * 2.0f : result;
}

char three_mixed_params_3(char a, int b, float c) {
    int temp = (int)a + b + (int)c;
    return (char)(temp % 256);
}

// 四参数函数 - 混合类型
int four_mixed_params_1(int a, float b, double c, char d) {
    return a + (int)b + (int)c + (int)d;
}

double four_mixed_params_2(char a, int b, float c, bool d) {
    double result = (double)a + (double)b + (double)c;
    return d ? result * 1.5 : result;
}

bool four_mixed_params_3(bool a, double b, int c, char d) {
    int sum = (a ? 1 : 0) + (int)b + c + (int)d;
    return (sum % 2) == 0;
}

// 五参数函数 - 混合类型
int five_mixed_params_1(int a, float b, double c, char d, bool e) {
    int result = a + (int)b + (int)c + (int)d;
    return e ? result * 2 : result;
}

float five_mixed_params_2(bool a, char b, int c, double d, float e) {
    float result = (a ? 1.0f : 0.0f) + (float)b + (float)c + (float)d + e;
    return result / 5.0f;
}

// 六参数函数 - 混合类型
int six_mixed_params_1(int a, float b, double c, char d, bool e, short f) {
    int result = a + (int)b + (int)c + (int)d + (e ? 1 : 0) + (int)f;
    return result;
}

double six_mixed_params_2(short a, bool b, char c, double d, float e, int f) {
    double result = (double)a + (b ? 1.0 : 0.0) + (double)c + d + (double)e + (double)f;
    return result / 6.0;
}

// 七参数函数 - 混合类型
int seven_mixed_params(int a, float b, double c, char d, bool e, short f, long g) {
    long result = (long)a + (long)b + (long)c + (long)d + (e ? 1L : 0L) + (long)f + g;
    return (int)(result % INT_MAX);
}

// 八参数函数 - 混合类型
double eight_mixed_params(int a, float b, double c, char d, bool e, short f, long g, unsigned int h) {
    double result = (double)a + (double)b + c + (double)d + (e ? 1.0 : 0.0) + 
                   (double)f + (double)g + (double)h;
    return result / 8.0;
}

// 大量参数函数（超过寄存器数量，测试栈传递）
int many_int_params(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10) {
    // 这个函数会强制使用栈传递参数（在x64上，前4个整数参数通过寄存器传递）
    return p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10;
}

float many_float_params(float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8) {
    // 测试大量浮点参数传递
    return (p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8) / 8.0f;
}

double many_double_params(double p1, double p2, double p3, double p4, double p5, double p6) {
    // 测试多个double参数传递
    return (p1 + p2 + p3 + p4 + p5 + p6) / 6.0;
}

// 结构体参数传递
Point struct_by_value_param(Point p) {
    Point result = {p.x * 2, p.y * 2};
    return result;
}

Point struct_by_pointer_param(Point* p) {
    if (!p) {
        Point zero = {0, 0};
        return zero;
    }
    Point result = {p->x + 10, p->y + 10};
    return result;
}

Rectangle large_struct_by_value(Rectangle rect) {
    // 测试大结构体按值传递
    Rectangle result = rect;
    result.top_left.x += 5;
    result.top_left.y += 5;
    result.bottom_right.x += 5;
    result.bottom_right.y += 5;
    return result;
}

Rectangle large_struct_by_pointer(Rectangle* rect) {
    if (!rect) {
        Rectangle empty = {{0, 0}, {0, 0}, COLOR_BLACK};
        return empty;
    }
    
    Rectangle result = *rect;
    result.top_left.x -= 5;
    result.top_left.y -= 5;
    result.bottom_right.x -= 5;
    result.bottom_right.y -= 5;
    return result;
}

// 数组参数传递
int array_param_1(int arr[]) {
    // 数组作为参数实际上是指针
    if (!arr) return 0;
    return arr[0] + arr[1];  // 假设至少有2个元素
}

int array_param_2(int arr[10]) {
    // 指定大小的数组参数，实际上仍然是指针
    if (!arr) return 0;
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    return sum;
}

int array_param_3(int* arr, size_t size) {
    // 显式指针和大小参数
    if (!arr || size == 0) return 0;
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int multidim_array_param(int matrix[3][3]) {
    // 多维数组参数
    if (!matrix) return 0;
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// 辅助函数用于函数指针测试
static int square_function(int x) {
    return x * x;
}

static int add_function(int a, int b) {
    return a + b;
}

// 函数指针参数
int function_pointer_param_1(int (*func)(int)) {
    if (!func) return 0;
    return func(5);
}

int function_pointer_param_2(int (*func)(int, int), int a, int b) {
    if (!func) return 0;
    return func(a, b);
}

void callback_with_multiple_params(void (*callback)(int, float, char), int a, float b, char c) {
    if (callback) {
        callback(a, b, c);
    }
}

// 混合复杂参数
int complex_mixed_params_1(int a, Point p, float* arr, size_t size, bool flag) {
    if (!arr || size == 0) return a;
    
    int result = a + p.x + p.y;
    if (flag) {
        for (size_t i = 0; i < size && i < 5; i++) {
            result += (int)arr[i];
        }
    }
    return result;
}

double complex_mixed_params_2(Rectangle* rect, int (*func)(int), double d, char* str) {
    if (!rect || !func) return d;
    
    double result = d;
    result += (double)(rect->top_left.x + rect->top_left.y);
    result += (double)func(10);
    
    if (str) {
        result += (double)strlen(str);
    }
    
    return result;
}

Status complex_mixed_params_3(Person person, int* results, CallbackFunc callback, VariantData* data) {
    if (!results || !data) return STATUS_INVALID_PARAM;
    
    results[0] = person.age;
    results[1] = (int)person.height;
    results[2] = (int)person.weight;
    
    if (callback) {
        callback(person.age);
    }
    
    // 操作VariantData
    if (data->type == TYPE_INT) {
        data->value.i += person.age;
    }
    
    return STATUS_SUCCESS;
}

// 参数传递性能测试函数
int param_passing_benchmark_1(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    // 测试大量整数参数的传递性能
    volatile int result = 0;  // volatile防止编译器优化
    result += a + b + c + d + e;
    result += f + g + h + i + j;
    result *= (a % 2 == 0) ? 2 : 1;
    result += (b * c) % 100;
    return result;
}

double param_passing_benchmark_2(double a, double b, double c, double d, double e, double f, double g, double h) {
    // 测试大量浮点参数的传递性能
    volatile double result = 0.0;  // volatile防止编译器优化
    result += a * b + c * d;
    result += e * f + g * h;
    result /= (a + b + c + d + e + f + g + h);
    return result;
}

Status param_passing_benchmark_3(Point p1, Point p2, Point p3, Point p4, Rectangle r1, Rectangle r2) {
    // 测试大量结构体参数的传递性能
    volatile int sum = 0;  // volatile防止编译器优化
    sum += p1.x + p1.y + p2.x + p2.y;
    sum += p3.x + p3.y + p4.x + p4.y;
    sum += r1.top_left.x + r1.top_left.y;
    sum += r1.bottom_right.x + r1.bottom_right.y;
    sum += r2.top_left.x + r2.top_left.y;
    sum += r2.bottom_right.x + r2.bottom_right.y;
    
    return (sum > 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

// 递归函数参数传递测试
int recursive_param_test_1(int n, int accumulator) {
    if (n <= 0) {
        return accumulator;
    }
    return recursive_param_test_1(n - 1, accumulator + n);
}

double recursive_param_test_2(double base, int exponent, double result) {
    if (exponent <= 0) {
        return result;
    }
    return recursive_param_test_2(base, exponent - 1, result * base);
}

Status recursive_param_test_3(Node* node, int depth, int* max_depth) {
    if (!node || !max_depth) {
        return STATUS_INVALID_PARAM;
    }
    
    if (depth > *max_depth) {
        *max_depth = depth;
    }
    
    if (node->next) {
        return recursive_param_test_3(node->next, depth + 1, max_depth);
    }
    
    return STATUS_SUCCESS;
}

// ============================================================================
// 基础数学运算函数
// ============================================================================

int add_integers(int a, int b) {
    return a + b;
}

float add_floats(float a, float b) {
    return a + b;
}

double add_doubles(double a, double b) {
    return a + b;
}

int subtract_integers(int a, int b) {
    return a - b;
}

int multiply_integers(int a, int b) {
    return a * b;
}

float divide_floats(float a, float b) {
    if (b == 0.0f) {
        return 0.0f; // 避免除零错误
    }
    return a / b;
}

int modulo_operation(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a % b;
}

double power_operation(double base, int exponent) {
    double result = 1.0;
    int abs_exp = (exponent < 0) ? -exponent : exponent;
    
    for (int i = 0; i < abs_exp; i++) {
        result *= base;
    }
    
    return (exponent < 0) ? (1.0 / result) : result;
}

// ============================================================================
// 位运算函数
// ============================================================================

unsigned int bitwise_and(unsigned int a, unsigned int b) {
    return a & b;
}

unsigned int bitwise_or(unsigned int a, unsigned int b) {
    return a | b;
}

unsigned int bitwise_xor(unsigned int a, unsigned int b) {
    return a ^ b;
}

unsigned int bitwise_not(unsigned int a) {
    return ~a;
}

unsigned int left_shift(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) {
        return value;
    }
    return value << positions;
}

unsigned int right_shift(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) {
        return value;
    }
    return value >> positions;
}

// ============================================================================
// 条件和循环测试函数
// ============================================================================

Status test_if_conditions(int value) {
    if (value > 100) {
        return STATUS_SUCCESS;
    } else if (value > 50) {
        return STATUS_ERROR;
    } else if (value > 0) {
        return STATUS_INVALID_PARAM;
    } else {
        return STATUS_OUT_OF_MEMORY;
    }
}

Status test_switch_statement(Color color) {
    switch (color) {
        case COLOR_RED:
            return STATUS_SUCCESS;
        case COLOR_GREEN:
        case COLOR_BLUE:
            return STATUS_ERROR;
        case COLOR_YELLOW:
            return STATUS_INVALID_PARAM;
        default:
            return STATUS_OUT_OF_MEMORY;
    }
}

int test_for_loop(int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
        if (sum > 10000) {
            break;
        }
    }
    return sum;
}

int test_while_loop(int initial_value, int target) {
    int current = initial_value;
    int iterations = 0;
    
    while (current < target && iterations < 1000) {
        current += 2;
        iterations++;
        if (current % 10 == 0) {
            continue;
        }
    }
    
    return iterations;
}

int test_do_while_loop(int value) {
    int result = 0;
    do {
        result += value;
        value--;
    } while (value > 0);
    
    return result;
}

// ============================================================================
// 数组和指针操作
// ============================================================================

Status array_operations(int* array, size_t size) {
    if (!array || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    // 数组初始化
    for (size_t i = 0; i < size; i++) {
        array[i] = (int)(i * 2);
    }
    
    // 数组排序（简单冒泡排序）
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    
    return STATUS_SUCCESS;
}

Status pointer_arithmetic(int* ptr, size_t offset) {
    if (!ptr) {
        return STATUS_INVALID_PARAM;
    }
    
    // 指针算术运算
    int* new_ptr = ptr + offset;
    *new_ptr = *ptr + 10;
    
    // 指针比较
    if (new_ptr > ptr) {
        return STATUS_SUCCESS;
    }
    
    return STATUS_ERROR;
}

Status string_operations(char* dest, const char* src, size_t max_len) {
    if (!dest || !src || max_len == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    // 字符串复制
    size_t i = 0;
    while (i < max_len - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    // 字符串长度计算
    size_t len = 0;
    while (dest[len] != '\0') {
        len++;
    }
    
    return (len > 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

// ============================================================================
// 结构体操作函数
// ============================================================================

Point create_point(int x, int y) {
    Point p = {x, y};
    return p;
}

Rectangle create_rectangle(Point top_left, Point bottom_right, Color color) {
    Rectangle rect;
    rect.top_left = top_left;
    rect.bottom_right = bottom_right;
    rect.color = color;
    return rect;
}

Person create_person(const char* name, int age, float height, double weight) {
    Person person;
    
    // 字符串复制
    size_t name_len = 0;
    while (name[name_len] != '\0' && name_len < 63) {
        person.name[name_len] = name[name_len];
        name_len++;
    }
    person.name[name_len] = '\0';
    
    person.age = age;
    person.height = height;
    person.weight = weight;
    person.is_active = (age >= 18 && age <= 65);
    person.favorite_color = COLOR_BLUE;
    
    return person;
}

Status print_person(const Person* person) {
    if (!person) {
        return STATUS_INVALID_PARAM;
    }
    
    printf("Person: %s, Age: %d, Height: %.2f, Weight: %.2f, Active: %s\n",
           person->name, person->age, person->height, person->weight,
           person->is_active ? "Yes" : "No");
    
    return STATUS_SUCCESS;
}

Status compare_persons(const Person* p1, const Person* p2) {
    if (!p1 || !p2) {
        return STATUS_INVALID_PARAM;
    }
    
    if (p1->age != p2->age) {
        return (p1->age > p2->age) ? STATUS_SUCCESS : STATUS_ERROR;
    }
    
    return STATUS_SUCCESS;
}

// ============================================================================
// 链表操作函数
// ============================================================================

LinkedList* create_linked_list(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    
    return list;
}

Status add_node(LinkedList* list, int data) {
    if (!list) {
        return STATUS_INVALID_PARAM;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return STATUS_OUT_OF_MEMORY;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->count++;
    
    return STATUS_SUCCESS;
}

Status remove_node(LinkedList* list, int data) {
    if (!list) {
        return STATUS_INVALID_PARAM;
    }
    
    Node* current = list->head;
    while (current) {
        if (current->data == data) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->head = current->next;
            }
            
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev;
            }
            
            free(current);
            list->count--;
            return STATUS_SUCCESS;
        }
        current = current->next;
    }
    
    return STATUS_ERROR;
}

Node* find_node(LinkedList* list, int data) {
    if (!list) {
        return NULL;
    }
    
    Node* current = list->head;
    while (current) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

Status print_list(const LinkedList* list) {
    if (!list) {
        return STATUS_INVALID_PARAM;
    }
    
    printf("List (count: %zu): ", list->count);
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    return STATUS_SUCCESS;
}

void destroy_linked_list(LinkedList* list) {
    if (!list) {
        return;
    }
    
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

// ============================================================================
// 内存管理函数
// ============================================================================

void* safe_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    void* ptr = malloc(size);
    if (ptr) {
        memset(ptr, 0, size);
    }
    
    return ptr;
}

void* safe_realloc(void* ptr, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    
    return realloc(ptr, new_size);
}

void safe_free(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

Status memory_copy(void* dest, const void* src, size_t size) {
    if (!dest || !src || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    memcpy(dest, src, size);
    return STATUS_SUCCESS;
}

Status memory_set(void* ptr, int value, size_t size) {
    if (!ptr || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    memset(ptr, value, size);
    return STATUS_SUCCESS;
}

// ============================================================================
// 文件操作函数
// ============================================================================

Status read_file_content(const char* filename, char** content, size_t* size) {
    if (!filename || !content || !size) {
        return STATUS_INVALID_PARAM;
    }
    
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return STATUS_FILE_NOT_FOUND;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        return STATUS_ERROR;
    }
    
    *content = (char*)malloc(file_size + 1);
    if (!*content) {
        fclose(file);
        return STATUS_OUT_OF_MEMORY;
    }
    
    size_t read_size = fread(*content, 1, file_size, file);
    (*content)[read_size] = '\0';
    *size = read_size;
    
    fclose(file);
    return STATUS_SUCCESS;
}

Status write_file_content(const char* filename, const char* content, size_t size) {
    if (!filename || !content) {
        return STATUS_INVALID_PARAM;
    }
    
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return STATUS_FILE_NOT_FOUND;
    }
    
    size_t written = fwrite(content, 1, size, file);
    fclose(file);
    
    return (written == size) ? STATUS_SUCCESS : STATUS_ERROR;
}

Status append_to_file(const char* filename, const char* content) {
    if (!filename || !content) {
        return STATUS_INVALID_PARAM;
    }
    
    FILE* file = fopen(filename, "a");
    if (!file) {
        return STATUS_FILE_NOT_FOUND;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    
    return STATUS_SUCCESS;
}

// ============================================================================
// 递归函数
// ============================================================================

int factorial_recursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}

int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int gcd_recursive(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_recursive(b, a % b);
}

Status binary_search_recursive(int* array, int target, int left, int right, int* index) {
    if (!array || !index || left > right) {
        return STATUS_INVALID_PARAM;
    }
    
    int mid = left + (right - left) / 2;
    
    if (array[mid] == target) {
        *index = mid;
        return STATUS_SUCCESS;
    }
    
    if (array[mid] > target) {
        return binary_search_recursive(array, target, left, mid - 1, index);
    } else {
        return binary_search_recursive(array, target, mid + 1, right, index);
    }
}

// ============================================================================
// 函数指针和回调函数
// ============================================================================

static int int_compare(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

Status sort_array(int* array, size_t size, CompareFunc compare) {
    if (!array || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    if (!compare) {
        compare = int_compare;
    }
    
    // 简单选择排序
    for (size_t i = 0; i < size - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < size; j++) {
            if (compare(&array[j], &array[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = array[i];
            array[i] = array[min_idx];
            array[min_idx] = temp;
        }
    }
    
    return STATUS_SUCCESS;
}

Status process_array(int* array, size_t size, CallbackFunc callback) {
    if (!array || !callback || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    for (size_t i = 0; i < size; i++) {
        callback(array[i]);
    }
    
    return STATUS_SUCCESS;
}

Status generic_processor(void* data, size_t size, ProcessFunc processor) {
    if (!data || !processor || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    return processor(data, size);
}

// ============================================================================
// 变参函数
// ============================================================================

int sum_integers(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }
    
    va_end(args);
    return sum;
}

Status print_formatted(const char* format, ...) {
    if (!format) {
        return STATUS_INVALID_PARAM;
    }
    
    va_list args;
    va_start(args, format);
    
    vprintf(format, args);
    
    va_end(args);
    return STATUS_SUCCESS;
}

// ============================================================================
// 复杂控制流函数
// ============================================================================

Status complex_nested_loops(int matrix[10][10], int rows, int cols) {
    if (!matrix || rows <= 0 || cols <= 0 || rows > 10 || cols > 10) {
        return STATUS_INVALID_PARAM;
    }
    
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
            sum += matrix[i][j];
            
            if (matrix[i][j] % 2 == 0) {
                for (int k = 0; k < 3; k++) {
                    sum += k;
                }
            }
        }
    }
    
    return (sum > 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

Status goto_example(int* array, size_t size, int target) {
    if (!array || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (array[i] < 0) {
            goto error_handling;
        }
        
        if (array[i] == target) {
            goto found;
        }
    }
    
    return STATUS_ERROR;

found:
    return STATUS_SUCCESS;

error_handling:
    return STATUS_INVALID_PARAM;
}

Status nested_switch_if(int a, int b, char op) {
    switch (op) {
        case '+':
            if (a > 0 && b > 0) {
                return STATUS_SUCCESS;
            } else if (a < 0 || b < 0) {
                return STATUS_ERROR;
            }
            break;
            
        case '-':
            if (a > b) {
                return STATUS_SUCCESS;
            }
            break;
            
        case '*':
            if ((a % 2 == 0) && (b % 2 == 0)) {
                return STATUS_SUCCESS;
            }
            break;
            
        default:
            return STATUS_INVALID_PARAM;
    }
    
    return STATUS_ERROR;
}

// ============================================================================
// 类型转换和类型安全函数
// ============================================================================

Status safe_int_to_string(int value, char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    int result = snprintf(buffer, buffer_size, "%d", value);
    return (result > 0 && (size_t)result < buffer_size) ? STATUS_SUCCESS : STATUS_ERROR;
}

Status safe_string_to_int(const char* str, int* value) {
    if (!str || !value) {
        return STATUS_INVALID_PARAM;
    }
    
    char* endptr;
    long result = strtol(str, &endptr, 10);
    
    if (endptr == str || *endptr != '\0') {
        return STATUS_ERROR;
    }
    
    if (result > INT_MAX || result < INT_MIN) {
        return STATUS_ERROR;
    }
    
    *value = (int)result;
    return STATUS_SUCCESS;
}

Status variant_data_operations(VariantData* data) {
    if (!data) {
        return STATUS_INVALID_PARAM;
    }
    
    switch (data->type) {
        case TYPE_INT:
            data->value.i *= 2;
            break;
        case TYPE_FLOAT:
            data->value.f *= 2.0f;
            break;
        case TYPE_DOUBLE:
            data->value.d *= 2.0;
            break;
        case TYPE_STRING:
            // 字符串操作
            for (int i = 0; i < 8 && data->value.c[i] != '\0'; i++) {
                if (data->value.c[i] >= 'a' && data->value.c[i] <= 'z') {
                    data->value.c[i] = data->value.c[i] - 'a' + 'A';
                }
            }
            break;
        default:
            return STATUS_ERROR;
    }
    
    return STATUS_SUCCESS;
}

// ============================================================================
// 位域和联合体操作
// ============================================================================

Status bitfield_operations(BitField* bf) {
    if (!bf) {
        return STATUS_INVALID_PARAM;
    }
    
    bf->flag1 = 1;
    bf->flag2 = 0;
    bf->flag3 = 1;
    bf->reserved = 0;
    bf->value = 0xABCDEF;
    
    // 位域操作
    if (bf->flag1 && bf->flag3) {
        bf->value |= 0x1;
    }
    
    return STATUS_SUCCESS;
}

Status union_operations(DataUnion* data) {
    if (!data) {
        return STATUS_INVALID_PARAM;
    }
    
    // 联合体操作
    data->i = 0x12345678;
    
    // 通过不同成员访问同一内存
    printf("Union as int: 0x%08X\n", data->i);
    printf("Union as float: %f\n", data->f);
    printf("Union as bytes: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", (unsigned char)data->c[i]);
    }
    printf("\n");
    
    return STATUS_SUCCESS;
}

// ============================================================================
// 静态和全局变量测试
// ============================================================================

Status increment_global_counter(void) {
    global_counter++;
    static_counter += 2;
    return STATUS_SUCCESS;
}

Status get_static_value(void) {
    static_counter++;
    return static_counter;
} 