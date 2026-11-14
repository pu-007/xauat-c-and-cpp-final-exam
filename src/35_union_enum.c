/* 35_union_enum 结构体、共用体与枚举 | ISO C99 | 提高
 * 来源/关系：S1 第八单元；C++类型安全拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出一个整数型记录及一个实数型记录
 * 思想：共用体共享存储；用标签记住最后写入的成员；C++11用enum class标签与构造函数管理访问。
 * 复杂度：O(1)
 * 对照 35_union_enum.cpp：C 用普通枚举和指定初始化，C++ 用强类型枚举和构造函数。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 提供 printf；C++ 版本通过 cout 输出。 */
enum Kind { INTEGER, REAL }; /* 标签说明当前值的类型。 */
struct Value {
    enum Kind kind; /* 记录当前使用的共用体成员。 */
    union { /* 两个成员共享存储。 */
        int integer; /* 整数类型的值。 */
        double real; /* 实数类型的值。 */
    } data;
};
static void print(struct Value v) { /* 根据标签打印实际写入的成员。 */
    switch (v.kind) {
    case INTEGER: /* 整数记录。 */
        printf("%d\n", v.data.integer); /* 按整数格式输出有效成员。 */
        break; /* 不继续执行实数分支。 */
    case REAL: /* 实数记录，保留一位小数。 */
        printf("%.1f\n", v.data.real); /* 按一位小数输出有效成员。 */
        break; /* 结束本分支。 */
    }
}
int main(void) {
    struct Value a = {INTEGER, {.integer = 7}}, b = {REAL, {.real = 2.5}}; /* 指定初始化成员与标签一致。 */
    print(a); /* 输出整数记录。 */
    print(b); /* 输出实数记录。 */
    /* 不读取未激活成员来猜测数值；sizeof可能包含对齐填充，不输出固定大小。 */
    return 0; /* 正常结束。 */
}
