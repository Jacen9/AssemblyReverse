#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// 回调函数示例
void print_callback(int value) {
    printf("Callback received: %d\n", value);
}

// 用于参数传递测试的回调函数
void multi_param_callback(int a, float b, char c) {
    printf("Multi-param callback: int=%d, float=%.2f, char='%c'\n", a, b, c);
}

// 比较函数示例
int reverse_compare(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ib > ia) - (ib < ia); // 反向比较
}

// 处理函数示例
Status data_processor(void* data, size_t size) {
    if (!data || size == 0) {
        return STATUS_INVALID_PARAM;
    }
    
    int* int_data = (int*)data;
    size_t count = size / sizeof(int);
    
    printf("Processing %zu integers: ", count);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", int_data[i]);
    }
    printf("\n");
    
    return STATUS_SUCCESS;
}

int main(void) {
    printf("=== Assembly Reverse Engineering Test Program ===\n\n");
    
    // ========================================================================
    // 测试函数参数传递
    // ========================================================================
    printf("1. Testing Function Parameter Passing:\n");
    
    // 无参数函数测试
    printf("   No Parameters:\n");
    printf("     no_params_function() = %d\n", no_params_function());
    void_no_params_function();
    printf("     void_no_params_function() executed\n");
    
    // 单参数函数测试
    printf("   Single Parameters:\n");
    printf("     single_int_param(10) = %d\n", single_int_param(10));
    printf("     single_float_param(3.14f) = %.2f\n", single_float_param(3.14f));
    printf("     single_double_param(2.718) = %.3f\n", single_double_param(2.718));
    printf("     single_char_param('A') = '%c'\n", single_char_param('A'));
    printf("     single_bool_param(true) = %s\n", single_bool_param(true) ? "true" : "false");
    
    // 双参数函数测试
    printf("   Two Parameters (Same Type):\n");
    printf("     two_int_params(5, 7) = %d\n", two_int_params(5, 7));
    printf("     two_float_params(2.5f, 1.5f) = %.2f\n", two_float_params(2.5f, 1.5f));
    printf("     two_double_params(10.0, 3.0) = %.2f\n", two_double_params(10.0, 3.0));
    
    printf("   Two Parameters (Mixed Types):\n");
    printf("     int_float_params(10, 3.14f) = %d\n", int_float_params(10, 3.14f));
    printf("     float_double_params(2.5f, 1.25) = %.2f\n", float_double_params(2.5f, 1.25));
    printf("     int_char_params(100, 'Z') = %d\n", int_char_params(100, 'Z'));
    printf("     int_double_params(5, 2.5) = %.2f\n", int_double_params(5, 2.5));
    
    // 三参数函数测试
    printf("   Three Parameters (Mixed Types):\n");
    printf("     three_mixed_params_1(10, 2.5f, 'A') = %d\n", three_mixed_params_1(10, 2.5f, 'A'));
    printf("     three_mixed_params_2(3.14, 5, true) = %.2f\n", three_mixed_params_2(3.14, 5, true));
    printf("     three_mixed_params_3('B', 20, 1.5f) = '%c'\n", three_mixed_params_3('B', 20, 1.5f));
    
    // 四参数函数测试
    printf("   Four Parameters (Mixed Types):\n");
    printf("     four_mixed_params_1(10, 2.5f, 1.25, 'C') = %d\n", 
           four_mixed_params_1(10, 2.5f, 1.25, 'C'));
    printf("     four_mixed_params_2('D', 15, 3.5f, false) = %.2f\n", 
           four_mixed_params_2('D', 15, 3.5f, false));
    printf("     four_mixed_params_3(true, 2.718, 42, 'E') = %s\n", 
           four_mixed_params_3(true, 2.718, 42, 'E') ? "true" : "false");
    
    // 五参数函数测试
    printf("   Five Parameters (Mixed Types):\n");
    printf("     five_mixed_params_1(8, 1.5f, 2.25, 'F', true) = %d\n", 
           five_mixed_params_1(8, 1.5f, 2.25, 'F', true));
    printf("     five_mixed_params_2(false, 'G', 12, 3.14, 2.5f) = %.2f\n", 
           five_mixed_params_2(false, 'G', 12, 3.14, 2.5f));
    
    // 六参数函数测试
    printf("   Six Parameters (Mixed Types):\n");
    printf("     six_mixed_params_1(6, 1.2f, 3.4, 'H', true, 100) = %d\n", 
           six_mixed_params_1(6, 1.2f, 3.4, 'H', true, 100));
    printf("     six_mixed_params_2(200, false, 'I', 5.67, 8.9f, 25) = %.2f\n", 
           six_mixed_params_2(200, false, 'I', 5.67, 8.9f, 25));
    
    // 七参数函数测试
    printf("   Seven Parameters (Mixed Types):\n");
    printf("     seven_mixed_params(7, 2.1f, 4.2, 'J', true, 300, 1000L) = %d\n", 
           seven_mixed_params(7, 2.1f, 4.2, 'J', true, 300, 1000L));
    
    // 八参数函数测试
    printf("   Eight Parameters (Mixed Types):\n");
    printf("     eight_mixed_params(8, 3.2f, 6.4, 'K', false, 400, 2000L, 500U) = %.2f\n", 
           eight_mixed_params(8, 3.2f, 6.4, 'K', false, 400, 2000L, 500U));
    
    // 大量参数函数测试（测试栈传递）
    printf("   Many Parameters (Stack Passing):\n");
    printf("     many_int_params(1,2,3,4,5,6,7,8,9,10) = %d\n", 
           many_int_params(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    printf("     many_float_params(1.1f,2.2f,3.3f,4.4f,5.5f,6.6f,7.7f,8.8f) = %.2f\n", 
           many_float_params(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    printf("     many_double_params(1.1,2.2,3.3,4.4,5.5,6.6) = %.2f\n", 
           many_double_params(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    
    // 结构体参数传递测试
    printf("   Structure Parameters:\n");
    Point test_point = {10, 20};
    Point result_point = struct_by_value_param(test_point);
    printf("     struct_by_value_param({10,20}) = {%d,%d}\n", result_point.x, result_point.y);
    
    result_point = struct_by_pointer_param(&test_point);
    printf("     struct_by_pointer_param(&{10,20}) = {%d,%d}\n", result_point.x, result_point.y);
    
    Rectangle test_rect = {{5, 5}, {15, 15}, COLOR_RED};
    Rectangle result_rect = large_struct_by_value(test_rect);
    printf("     large_struct_by_value(rect) = {{%d,%d},{%d,%d},%d}\n", 
           result_rect.top_left.x, result_rect.top_left.y,
           result_rect.bottom_right.x, result_rect.bottom_right.y, result_rect.color);
    
    result_rect = large_struct_by_pointer(&test_rect);
    printf("     large_struct_by_pointer(&rect) = {{%d,%d},{%d,%d},%d}\n", 
           result_rect.top_left.x, result_rect.top_left.y,
           result_rect.bottom_right.x, result_rect.bottom_right.y, result_rect.color);
    
    // 数组参数传递测试
    printf("   Array Parameters:\n");
    int test_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("     array_param_1(arr) = %d\n", array_param_1(test_arr));
    printf("     array_param_2(arr) = %d\n", array_param_2(test_arr));
    printf("     array_param_3(arr, 10) = %d\n", array_param_3(test_arr, 10));
    
    int test_matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printf("     multidim_array_param(matrix) = %d\n", multidim_array_param(test_matrix));
    
    // 函数指针参数测试
    printf("   Function Pointer Parameters:\n");
    printf("     function_pointer_param_1(square_func) = %d\n", function_pointer_param_1(single_int_param));
    printf("     function_pointer_param_2(add_func, 10, 20) = %d\n", 
           function_pointer_param_2(two_int_params, 10, 20));
    
    // 测试带多参数的回调函数
    printf("     callback_with_multiple_params test:\n");
    callback_with_multiple_params(multi_param_callback, 42, 3.14f, 'X');
    
    // 复杂混合参数测试
    printf("   Complex Mixed Parameters:\n");
    Point complex_point = {25, 35};
    float complex_arr[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    printf("     complex_mixed_params_1(15, {25,35}, arr, 5, true) = %d\n", 
           complex_mixed_params_1(15, complex_point, complex_arr, 5, true));
    
    Rectangle complex_rect = {{0, 0}, {50, 50}, COLOR_CYAN};
    char complex_str[] = "TestString";
    printf("     complex_mixed_params_2(&rect, func, 7.89, \"TestString\") = %.2f\n", 
           complex_mixed_params_2(&complex_rect, single_int_param, 7.89, complex_str));
    
    Person complex_person = create_person("TestPerson", 28, 170.0f, 65.5);
    int complex_results[3];
    VariantData complex_variant = {.type = TYPE_INT, .value.i = 100};
    Status complex_status = complex_mixed_params_3(complex_person, complex_results, print_callback, &complex_variant);
    printf("     complex_mixed_params_3(person, results, callback, variant) = %d\n", complex_status);
    printf("     Results: [%d, %d, %d], Variant value: %d\n", 
           complex_results[0], complex_results[1], complex_results[2], complex_variant.value.i);
    
    // 递归函数参数传递测试
    printf("   Recursive Parameter Passing:\n");
    printf("     recursive_param_test_1(5, 0) = %d\n", recursive_param_test_1(5, 0));
    printf("     recursive_param_test_2(2.0, 3, 1.0) = %.2f\n", recursive_param_test_2(2.0, 3, 1.0));
    
    // 创建一个简单的链表用于递归测试
    LinkedList* param_test_list = create_linked_list();
    if (param_test_list) {
        add_node(param_test_list, 1);
        add_node(param_test_list, 2);
        add_node(param_test_list, 3);
        int max_depth = 0;
        Status recursive_result = recursive_param_test_3(param_test_list->head, 0, &max_depth);
        printf("     recursive_param_test_3(list, 0, &max_depth) = %d, max_depth = %d\n", 
               recursive_result, max_depth);
        destroy_linked_list(param_test_list);
    }
    
    // 参数传递性能测试
    printf("   Parameter Passing Benchmarks:\n");
    printf("     param_passing_benchmark_1(1,2,3,4,5,6,7,8,9,10) = %d\n", 
           param_passing_benchmark_1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    printf("     param_passing_benchmark_2(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8) = %.2f\n", 
           param_passing_benchmark_2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    
    Point bp1 = {1, 2}, bp2 = {3, 4}, bp3 = {5, 6}, bp4 = {7, 8};
    Rectangle br1 = {{10, 10}, {20, 20}, COLOR_BLUE};
    Rectangle br2 = {{30, 30}, {40, 40}, COLOR_GREEN};
    Status benchmark_result = param_passing_benchmark_3(bp1, bp2, bp3, bp4, br1, br2);
    printf("     param_passing_benchmark_3(multiple_structs) = %d\n", benchmark_result);
    
    printf("\n");
    
    // ========================================================================
    // 测试基础数学运算
    // ========================================================================
    printf("2. Testing Basic Math Operations:\n");
    printf("   add_integers(10, 20) = %d\n", add_integers(10, 20));
    printf("   add_floats(3.14f, 2.86f) = %.2f\n", add_floats(3.14f, 2.86f));
    printf("   add_doubles(1.234, 5.678) = %.3f\n", add_doubles(1.234, 5.678));
    printf("   subtract_integers(100, 30) = %d\n", subtract_integers(100, 30));
    printf("   multiply_integers(7, 8) = %d\n", multiply_integers(7, 8));
    printf("   divide_floats(15.0f, 3.0f) = %.2f\n", divide_floats(15.0f, 3.0f));
    printf("   modulo_operation(17, 5) = %d\n", modulo_operation(17, 5));
    printf("   power_operation(2.0, 8) = %.0f\n", power_operation(2.0, 8));
    printf("\n");
    
    // ========================================================================
    // 测试位运算
    // ========================================================================
    printf("3. Testing Bitwise Operations:\n");
    unsigned int a = 0xF0F0, b = 0x0F0F;
    printf("   a = 0x%04X, b = 0x%04X\n", a, b);
    printf("   bitwise_and(a, b) = 0x%04X\n", bitwise_and(a, b));
    printf("   bitwise_or(a, b) = 0x%04X\n", bitwise_or(a, b));
    printf("   bitwise_xor(a, b) = 0x%04X\n", bitwise_xor(a, b));
    printf("   bitwise_not(a) = 0x%08X\n", bitwise_not(a));
    printf("   left_shift(a, 2) = 0x%08X\n", left_shift(a, 2));
    printf("   right_shift(a, 2) = 0x%04X\n", right_shift(a, 2));
    printf("\n");
    
    // ========================================================================
    // 测试条件和循环
    // ========================================================================
    printf("4. Testing Conditional and Loop Operations:\n");
    printf("   test_if_conditions(150) = %d\n", test_if_conditions(150));
    printf("   test_if_conditions(75) = %d\n", test_if_conditions(75));
    printf("   test_if_conditions(25) = %d\n", test_if_conditions(25));
    printf("   test_if_conditions(-10) = %d\n", test_if_conditions(-10));
    
    printf("   test_switch_statement(COLOR_RED) = %d\n", test_switch_statement(COLOR_RED));
    printf("   test_switch_statement(COLOR_GREEN) = %d\n", test_switch_statement(COLOR_GREEN));
    printf("   test_switch_statement(COLOR_YELLOW) = %d\n", test_switch_statement(COLOR_YELLOW));
    printf("   test_switch_statement(COLOR_BLACK) = %d\n", test_switch_statement(COLOR_BLACK));
    
    printf("   test_for_loop(1, 10) = %d\n", test_for_loop(1, 10));
    printf("   test_while_loop(0, 100) = %d\n", test_while_loop(0, 100));
    printf("   test_do_while_loop(5) = %d\n", test_do_while_loop(5));
    printf("\n");
    
    // ========================================================================
    // 测试数组和指针操作
    // ========================================================================
    printf("5. Testing Array and Pointer Operations:\n");
    int test_array[10];
    Status result = array_operations(test_array, 10);
    printf("   array_operations result: %d\n", result);
    printf("   Array contents: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    
    result = pointer_arithmetic(test_array, 5);
    printf("   pointer_arithmetic result: %d\n", result);
    
    char dest_str[100];
    const char* src_str = "Hello, Assembly World!";
    result = string_operations(dest_str, src_str, sizeof(dest_str));
    printf("   string_operations result: %d, string: \"%s\"\n", result, dest_str);
    printf("\n");
    
    // ========================================================================
    // 测试结构体操作
    // ========================================================================
    printf("6. Testing Structure Operations:\n");
    Point p1 = create_point(10, 20);
    Point p2 = create_point(30, 40);
    printf("   Point p1: (%d, %d)\n", p1.x, p1.y);
    printf("   Point p2: (%d, %d)\n", p2.x, p2.y);
    
    Rectangle rect = create_rectangle(p1, p2, COLOR_RED);
    printf("   Rectangle: top_left(%d, %d), bottom_right(%d, %d), color=%d\n",
           rect.top_left.x, rect.top_left.y, rect.bottom_right.x, rect.bottom_right.y, rect.color);
    
    Person person1 = create_person("Alice", 25, 165.5f, 55.2);
    Person person2 = create_person("Bob", 30, 175.0f, 70.5);
    print_person(&person1);
    print_person(&person2);
    
    result = compare_persons(&person1, &person2);
    printf("   compare_persons result: %d\n", result);
    printf("\n");
    
    // ========================================================================
    // 测试链表操作
    // ========================================================================
    printf("7. Testing Linked List Operations:\n");
    LinkedList* list = create_linked_list();
    if (list) {
        add_node(list, 10);
        add_node(list, 20);
        add_node(list, 30);
        add_node(list, 40);
        print_list(list);
        
        Node* found = find_node(list, 20);
        printf("   find_node(20): %s\n", found ? "Found" : "Not found");
        
        remove_node(list, 20);
        print_list(list);
        
        destroy_linked_list(list);
    }
    printf("\n");
    
    // ========================================================================
    // 测试内存管理
    // ========================================================================
    printf("8. Testing Memory Management:\n");
    void* ptr = safe_malloc(100);
    if (ptr) {
        printf("   safe_malloc(100): Success\n");
        
        result = memory_set(ptr, 0xAA, 50);
        printf("   memory_set result: %d\n", result);
        
        void* new_ptr = safe_realloc(ptr, 200);
        if (new_ptr) {
            printf("   safe_realloc(200): Success\n");
            ptr = new_ptr;
        }
        
        safe_free(&ptr);
        printf("   safe_free: %s\n", ptr ? "Failed" : "Success");
    }
    printf("\n");
    
    // ========================================================================
    // 测试递归函数
    // ========================================================================
    printf("9. Testing Recursive Functions:\n");
    printf("   factorial_recursive(5) = %d\n", factorial_recursive(5));
    printf("   fibonacci_recursive(8) = %d\n", fibonacci_recursive(8));
    printf("   gcd_recursive(48, 18) = %d\n", gcd_recursive(48, 18));
    
    int sorted_array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int index;
    result = binary_search_recursive(sorted_array, 7, 0, 9, &index);
    printf("   binary_search_recursive(7) result: %d, index: %d\n", result, index);
    printf("\n");
    
    // ========================================================================
    // 测试函数指针和回调
    // ========================================================================
    printf("10. Testing Function Pointers and Callbacks:\n");
    int callback_array[] = {5, 2, 8, 1, 9, 3};
    size_t array_size = sizeof(callback_array) / sizeof(callback_array[0]);
    
    printf("   Original array: ");
    for (size_t i = 0; i < array_size; i++) {
        printf("%d ", callback_array[i]);
    }
    printf("\n");
    
    result = sort_array(callback_array, array_size, reverse_compare);
    printf("   sort_array (reverse) result: %d\n", result);
    printf("   Sorted array: ");
    for (size_t i = 0; i < array_size; i++) {
        printf("%d ", callback_array[i]);
    }
    printf("\n");
    
    result = process_array(callback_array, array_size, print_callback);
    printf("   process_array result: %d\n", result);
    
    result = generic_processor(callback_array, sizeof(callback_array), data_processor);
    printf("   generic_processor result: %d\n", result);
    printf("\n");
    
    // ========================================================================
    // 测试变参函数
    // ========================================================================
    printf("11. Testing Variadic Functions:\n");
    int sum = sum_integers(5, 10, 20, 30, 40, 50);
    printf("    sum_integers(5, 10, 20, 30, 40, 50) = %d\n", sum);
    
    result = print_formatted("    Formatted output: %s = %d, %.2f\n", "PI", 3, 3.14159);
    printf("    print_formatted result: %d\n", result);
    printf("\n");
    
    // ========================================================================
    // 测试复杂控制流
    // ========================================================================
    printf("12. Testing Complex Control Flow:\n");
    int matrix[10][10];
    result = complex_nested_loops(matrix, 3, 3);
    printf("    complex_nested_loops result: %d\n", result);
    printf("    Matrix (3x3):\n");
    for (int i = 0; i < 3; i++) {
        printf("    ");
        for (int j = 0; j < 3; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    int goto_array[] = {1, 2, 3, 4, 5};
    result = goto_example(goto_array, 5, 3);
    printf("    goto_example(target=3) result: %d\n", result);
    
    result = nested_switch_if(10, 5, '+');
    printf("    nested_switch_if(10, 5, '+') result: %d\n", result);
    printf("\n");
    
    // ========================================================================
    // 测试类型转换和安全函数
    // ========================================================================
    printf("13. Testing Type Conversion and Safety:\n");
    char buffer[32];
    result = safe_int_to_string(12345, buffer, sizeof(buffer));
    printf("    safe_int_to_string(12345) result: %d, string: \"%s\"\n", result, buffer);
    
    int converted_value;
    result = safe_string_to_int("67890", &converted_value);
    printf("    safe_string_to_int(\"67890\") result: %d, value: %d\n", result, converted_value);
    
    VariantData variant;
    variant.type = TYPE_INT;
    variant.value.i = 42;
    result = variant_data_operations(&variant);
    printf("    variant_data_operations(INT, 42) result: %d, new value: %d\n", result, variant.value.i);
    printf("\n");
    
    // ========================================================================
    // 测试位域和联合体
    // ========================================================================
    printf("14. Testing Bitfields and Unions:\n");
    BitField bf;
    result = bitfield_operations(&bf);
    printf("    bitfield_operations result: %d\n", result);
    printf("    BitField: flag1=%u, flag2=%u, flag3=%u, value=0x%06X\n",
           bf.flag1, bf.flag2, bf.flag3, bf.value);
    
    DataUnion data_union;
    result = union_operations(&data_union);
    printf("    union_operations result: %d\n", result);
    printf("\n");
    
    // ========================================================================
    // 测试静态和全局变量
    // ========================================================================
    printf("15. Testing Static and Global Variables:\n");
    printf("    Initial global_counter: %d\n", global_counter);
    
    increment_global_counter();
    increment_global_counter();
    increment_global_counter();
    
    printf("    After 3 increments:\n");
    get_static_value();
    get_static_value();
    printf("\n");
    
    // ========================================================================
    // 测试内联函数和宏
    // ========================================================================
    printf("16. Testing Inline Functions and Macros:\n");
    printf("    inline_max(15, 25) = %d\n", inline_max(15, 25));
    printf("    is_even(42) = %s\n", is_even(42) ? "true" : "false");
    printf("    is_even(43) = %s\n", is_even(43) ? "true" : "false");
    
    printf("    SQUARE(7) = %d\n", SQUARE(7));
    printf("    MAX(10, 20) = %d\n", MAX(10, 20));
    printf("    MIN(10, 20) = %d\n", MIN(10, 20));
    
    int macro_array[] = {1, 2, 3, 4, 5};
    printf("    ARRAY_SIZE(macro_array) = %zu\n", ARRAY_SIZE(macro_array));
    printf("\n");
    
    // ========================================================================
    // 测试常量
    // ========================================================================
    printf("17. Testing Constants:\n");
    printf("    CONSTANT_VALUE = %d\n", CONSTANT_VALUE);
    printf("    CONSTANT_STRING = \"%s\"\n", CONSTANT_STRING);
    printf("    ORIGIN_POINT = (%d, %d)\n", ORIGIN_POINT.x, ORIGIN_POINT.y);
    printf("    PI = %.5f\n", PI);
    printf("\n");
    
    // ========================================================================
    // 平台相关测试
    // ========================================================================
    printf("18. Platform Information:\n");
#ifdef PLATFORM_WINDOWS
    printf("    Platform: Windows\n");
#elif defined(PLATFORM_LINUX)
    printf("    Platform: Linux\n");
#else
    printf("    Platform: Unknown\n");
#endif
    printf("\n");
    
    printf("=== All Tests Completed Successfully! ===\n");
    printf("This program exercises a comprehensive set of C language features\n");
    printf("that will generate diverse assembly instructions for reverse engineering.\n\n");
    
    printf("Features covered:\n");
    printf("- Function parameter passing (various types and quantities)\n");
    printf("- Arithmetic operations (int, float, double)\n");
    printf("- Bitwise operations\n");
    printf("- Control flow (if/else, switch, loops)\n");
    printf("- Function calls and returns\n");
    printf("- Pointer arithmetic and dereferencing\n");
    printf("- Structure and union operations\n");
    printf("- Array operations\n");
    printf("- Memory allocation and management\n");
    printf("- Recursive function calls\n");
    printf("- Function pointers and callbacks\n");
    printf("- Variadic functions\n");
    printf("- Complex nested control structures\n");
    printf("- Type conversions\n");
    printf("- Static and global variable access\n");
    printf("- Inline functions and macros\n");
    printf("- Bitfield manipulations\n");
    printf("- String operations\n");
    printf("- File I/O operations\n");
    
    return 0;
} 