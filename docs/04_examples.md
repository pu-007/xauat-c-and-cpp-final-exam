# 53组配对代码：题型→实践

每个编号有C99与C++11两个独立入口。先读任务卡并独立写，再看参考实现。输出以所列程序契约为准；有些程序把多个相关原题合并演示。

建议先按题型学习，再用下表查找其他题目：

1. 顺序、分支、循环：[成绩等级](../practice/tasks/03_grade.md) → [正负零统计](../practice/tasks/50_sign_count.md) → [阶乘和](../practice/tasks/05_factorial_sum.md) → [水仙花数](../practice/tasks/46_narcissistic.md) → [区间素数](../practice/tasks/48_prime_interval.md)。
2. 数组与矩阵：[数组极值](../practice/tasks/10_array_stats.md) → [最小值交换](../practice/tasks/49_min_to_end.md) → [排序](../practice/tasks/12_sort.md) → [矩阵行和](../practice/tasks/47_matrix_row_sums.md) → [课程最高分](../practice/tasks/51_course_max.md)。
3. 字符串、函数与指针：[字符串](../practice/tasks/15_strings.md) → [指针](../practice/tasks/17_pointers.md) → [20数筛素数排序](../practice/tasks/52_prime_twenty.md)。
4. 结构体、链表与文件：[学生成绩](../practice/tasks/19_students.md) → [链表](../practice/tasks/20_linked_list.md) → [文件](../practice/tasks/21_files.md) → [订餐综合题](../practice/tasks/44_reservations.md)。
5. 学有余力再看 [栈与括号匹配](../practice/tasks/53_bracket_stack.md)和 22–31 的递推、分治、搜索、动态规划；其拓展部分不计入原资料考频。

|编号|主题|层级|C99 / C++11 / 任务|
|---|---|---|---|
|01_expressions|表达式、短路与确定的求值顺序|基础|[C](../src/01_expressions.c) · [C++](../src/01_expressions.cpp) · [练习](../practice/tasks/01_expressions.md)|
|02_io|格式化输入输出与类型|基础|[C](../src/02_io.c) · [C++](../src/02_io.cpp) · [练习](../practice/tasks/02_io.md)|
|03_grade|switch百分制成绩|基础|[C](../src/03_grade.c) · [C++](../src/03_grade.cpp) · [练习](../practice/tasks/03_grade.md)|
|04_characters|字母、数字、空格和其他字符统计|基础|[C](../src/04_characters.c) · [C++](../src/04_characters.cpp) · [练习](../practice/tasks/04_characters.md)|
|05_factorial_sum|阶乘递推与累加|基础|[C](../src/05_factorial_sum.c) · [C++](../src/05_factorial_sum.cpp) · [练习](../practice/tasks/05_factorial_sum.md)|
|06_digits|数位拆分、水仙花数|基础|[C](../src/06_digits.c) · [C++](../src/06_digits.cpp) · [练习](../practice/tasks/06_digits.md)|
|07_gcd|欧几里得算法与最小公倍数|基础|[C](../src/07_gcd.c) · [C++](../src/07_gcd.cpp) · [练习](../practice/tasks/07_gcd.md)|
|08_prime|单个整数的素数判定|基础|[C](../src/08_prime.c) · [C++](../src/08_prime.cpp) · [练习](../practice/tasks/08_prime.md)|
|09_recurrence|斐波那契与分数序列|基础|[C](../src/09_recurrence.c) · [C++](../src/09_recurrence.cpp) · [练习](../practice/tasks/09_recurrence.md)|
|10_array_stats|数组、平均数、极值与下标|基础|[C](../src/10_array_stats.c) · [C++](../src/10_array_stats.cpp) · [练习](../practice/tasks/10_array_stats.md)|
|11_reverse_rotate|逆序、循环右移、最小最大交换|提高|[C](../src/11_reverse_rotate.c) · [C++](../src/11_reverse_rotate.cpp) · [练习](../practice/tasks/11_reverse_rotate.md)|
|12_sort|冒泡、选择、插入三种排序|提高|[C](../src/12_sort.c) · [C++](../src/12_sort.cpp) · [练习](../practice/tasks/12_sort.md)|
|13_binary_search|二分查找第一个匹配|拓展|[C](../src/13_binary_search.c) · [C++](../src/13_binary_search.cpp) · [练习](../practice/tasks/13_binary_search.md)|
|14_matrix|二维数组、转置、对角线、行列极值|提高|[C](../src/14_matrix.c) · [C++](../src/14_matrix.cpp) · [练习](../practice/tasks/14_matrix.md)|
|15_strings|手写strlen/strcat/strcmp、回文|提高|[C](../src/15_strings.c) · [C++](../src/15_strings.cpp) · [练习](../practice/tasks/15_strings.md)|
|16_words_vowels|单词状态机、元音筛选、字符排序|提高|[C](../src/16_words_vowels.c) · [C++](../src/16_words_vowels.cpp) · [练习](../practice/tasks/16_words_vowels.md)|
|17_pointers|值传递、指针、数组指针|提高|[C](../src/17_pointers.c) · [C++](../src/17_pointers.cpp) · [练习](../practice/tasks/17_pointers.md)|
|18_storage_callback|static、作用域、函数指针、宏|提高|[C](../src/18_storage_callback.c) · [C++](../src/18_storage_callback.cpp) · [练习](../practice/tasks/18_storage_callback.md)|
|19_students|结构体数组与成绩统计|提高|[C](../src/19_students.c) · [C++](../src/19_students.cpp) · [练习](../practice/tasks/19_students.md)|
|20_linked_list|动态内存、头插、删除、反转|提高|[C](../src/20_linked_list.c) · [C++](../src/20_linked_list.cpp) · [练习](../practice/tasks/20_linked_list.md)|
|21_files|文件写入、读回与返回值|提高|[C](../src/21_files.c) · [C++](../src/21_files.cpp) · [练习](../practice/tasks/21_files.md)|
|22_josephus|约瑟夫环：模拟到递推|提高|[C](../src/22_josephus.c) · [C++](../src/22_josephus.cpp) · [练习](../practice/tasks/22_josephus.md)|
|23_sieve|埃氏筛：批量判断素数|提高|[C](../src/23_sieve.c) · [C++](../src/23_sieve.cpp) · [练习](../practice/tasks/23_sieve.md)|
|24_recursion|递归与快速幂（取模）|拓展|[C](../src/24_recursion.c) · [C++](../src/24_recursion.cpp) · [练习](../practice/tasks/24_recursion.md)|
|25_merge_sort|归并排序与分治|拓展|[C](../src/25_merge_sort.c) · [C++](../src/25_merge_sort.cpp) · [练习](../practice/tasks/25_merge_sort.md)|
|26_prefix_window|前缀和与固定窗口|拓展|[C](../src/26_prefix_window.c) · [C++](../src/26_prefix_window.cpp) · [练习](../practice/tasks/26_prefix_window.md)|
|27_knapsack|0/1背包动态规划|拓展|[C](../src/27_knapsack.c) · [C++](../src/27_knapsack.cpp) · [练习](../practice/tasks/27_knapsack.md)|
|28_queens|N皇后回溯|拓展|[C](../src/28_queens.c) · [C++](../src/28_queens.cpp) · [练习](../practice/tasks/28_queens.md)|
|29_bfs_maze|迷宫广度优先搜索|拓展|[C](../src/29_bfs_maze.c) · [C++](../src/29_bfs_maze.cpp) · [练习](../practice/tasks/29_bfs_maze.md)|
|30_big_integer|十进制高精度阶乘|拓展|[C](../src/30_big_integer.c) · [C++](../src/30_big_integer.cpp) · [练习](../practice/tasks/30_big_integer.md)|
|31_kmp|字符串匹配：朴素法到KMP|拓展|[C](../src/31_kmp.c) · [C++](../src/31_kmp.cpp) · [练习](../practice/tasks/31_kmp.md)|
|32_numerical|数值迭代：莱布尼茨级数与牛顿法|提高|[C](../src/32_numerical.c) · [C++](../src/32_numerical.cpp) · [练习](../practice/tasks/32_numerical.md)|
|33_calendar|闰年、日期结构体与年内序号|基础|[C](../src/33_calendar.c) · [C++](../src/33_calendar.cpp) · [练习](../practice/tasks/33_calendar.md)|
|34_magic_square|奇数阶魔方阵|提高|[C](../src/34_magic_square.c) · [C++](../src/34_magic_square.cpp) · [练习](../practice/tasks/34_magic_square.md)|
|35_union_enum|结构体、共用体与枚举|提高|[C](../src/35_union_enum.c) · [C++](../src/35_union_enum.cpp) · [练习](../practice/tasks/35_union_enum.md)|
|36_prime_pipeline|综合压轴：素数筛选、函数、排序|提高|[C](../src/36_prime_pipeline.c) · [C++](../src/36_prime_pipeline.cpp) · [练习](../practice/tasks/36_prime_pipeline.md)|
|37_quadratic|二次方程及退化情况|基础|[C](../src/37_quadratic.c) · [C++](../src/37_quadratic.cpp) · [练习](../practice/tasks/37_quadratic.md)|
|38_newton_polynomial|报告指定方程的牛顿迭代|提高|[C](../src/38_newton_polynomial.c) · [C++](../src/38_newton_polynomial.cpp) · [练习](../practice/tasks/38_newton_polynomial.md)|
|39_saddle|矩阵所有鞍点|提高|[C](../src/39_saddle.c) · [C++](../src/39_saddle.cpp) · [练习](../practice/tasks/39_saddle.md)|
|40_my_atoi|有范围检查的数字字符串转换|提高|[C](../src/40_my_atoi.c) · [C++](../src/40_my_atoi.cpp) · [练习](../practice/tasks/40_my_atoi.md)|
|41_global_scores|全局数组与输出参数|提高|[C](../src/41_global_scores.c) · [C++](../src/41_global_scores.cpp) · [练习](../practice/tasks/41_global_scores.md)|
|42_grade_files|文本→二进制→排序→文本/二进制|提高|[C](../src/42_grade_files.c) · [C++](../src/42_grade_files.cpp) · [练习](../practice/tasks/42_grade_files.md)|
|43_five_courses|10名学生5门课：行列统计|基础|[C](../src/43_five_courses.c) · [C++](../src/43_five_courses.cpp) · [练习](../practice/tasks/43_five_courses.md)|
|44_reservations|订餐信息管理：插入查询修改删除显示|综合|[C](../src/44_reservations.c) · [C++](../src/44_reservations.cpp) · [练习](../practice/tasks/44_reservations.md)|
|45_string_max|三个字符串中字典序最大者|基础|[C](../src/45_string_max.c) · [C++](../src/45_string_max.cpp) · [练习](../practice/tasks/45_string_max.md)|
|46_narcissistic|三位水仙花数：模拟卷改编|基础|[C](../src/46_narcissistic.c) · [C++](../src/46_narcissistic.cpp) · [练习](../practice/tasks/46_narcissistic.md)|
|47_matrix_row_sums|5×6矩阵及各行和：模拟卷改编|基础|[C](../src/47_matrix_row_sums.c) · [C++](../src/47_matrix_row_sums.cpp) · [练习](../practice/tasks/47_matrix_row_sums.md)|
|48_prime_interval|200至300的素数：模拟卷改编|基础|[C](../src/48_prime_interval.c) · [C++](../src/48_prime_interval.cpp) · [练习](../practice/tasks/48_prime_interval.md)|
|49_min_to_end|最小元素与末项交换：模拟卷改编|基础|[C](../src/49_min_to_end.c) · [C++](../src/49_min_to_end.cpp) · [练习](../practice/tasks/49_min_to_end.md)|
|50_sign_count|统计正数、负数和零：期末练习|基础|[C](../src/50_sign_count.c) · [C++](../src/50_sign_count.cpp) · [练习](../practice/tasks/50_sign_count.md)|
|51_course_max|20名学生三门课最高分：模拟卷改编|基础|[C](../src/51_course_max.c) · [C++](../src/51_course_max.cpp) · [练习](../practice/tasks/51_course_max.md)|
|52_prime_twenty|20数筛素数排序：模拟卷改编|提高|[C](../src/52_prime_twenty.c) · [C++](../src/52_prime_twenty.cpp) · [练习](../practice/tasks/52_prime_twenty.md)|
|53_bracket_stack|栈与括号匹配|拓展|[C](../src/53_bracket_stack.c) · [C++](../src/53_bracket_stack.cpp) · [练习](../practice/tasks/53_bracket_stack.md)|

## 如何组合原题

- S1模拟三素数筛选排序：直接练36，再分别重写08与12。
- S5二维最大值/转置/对角和：14里是3×3，原题3×4时按题目改行列上限和函数类型。
- S6实验1/2新增任务：37–39、43、45；函数/指针/文件与综合项目：40–44。
- C++版本不使用C++14/17特性；容器、lambda、范围for、enum class均属于C++11。
- 二进制文件题、结构体单科题和指定函数签名的适配详见[实验手册](15_labs.md)。
