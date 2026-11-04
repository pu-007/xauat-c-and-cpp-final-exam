/* 35_union_enum 结构体、共用体与枚举 | ISO C99 | 提高
 * 来源/关系：S1 第八单元；C++类型安全拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出一个整数型记录及一个实数型记录
 * 思想：共用体共享存储；用标签记住最后写入的成员；C++11用enum class标签与构造函数管理访问。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
enum Kind { INTEGER, REAL };
struct Value {
    enum Kind kind;
    union {
        int integer;
        double real;
    } data;
};
static void print(struct Value v) {
    switch (v.kind) {
    case INTEGER:
        printf("%d\n", v.data.integer);
        break;
    case REAL:
        printf("%.1f\n", v.data.real);
        break;
    }
}
int main(void) {
    struct Value a = {INTEGER, {.integer = 7}}, b = {REAL, {.real = 2.5}};
    print(a);
    print(b);
    /* 不读取未激活成员来猜测数值；sizeof可能包含对齐填充，不输出固定大小。 */
    return 0;
}
