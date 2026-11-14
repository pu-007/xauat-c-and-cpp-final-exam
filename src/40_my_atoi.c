/* 40_my_atoi 有范围检查的数字字符串转换 | ISO C99 | 提高
 * 来源/关系：S6实验4(2) p28/31；原my_atoi的安全扩展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行最多100字节，可选+/-后接十进制数字，不接受空白；输出int或INVALID
 * 思想：逐位乘10前检查是否超限；明确格式与溢出政策。
 * 复杂度：O(字符串长度)
 * 对照 40_my_atoi.cpp：C 手动检查溢出并通过指针返回结果；C++ 使用 stoi 和异常。
 * fgets/strcspn 读行并去换行，对应 C++ getline；printf/puts 对应 cout。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* fgets、printf 和 puts。 */
#include <string.h> /* strcspn 定位换行。 */
#include <limits.h> /* INT_MIN 和 INT_MAX 指定整数范围。 */
static int my_atoi(const char *s, int *out) {
    int negative = 0; /* 默认正数。 */
    if (*s == '+' || *s == '-') {
        negative = *s == '-'; /* 记录符号并跳过它。 */
        ++s;
    }
    if (*s == '\0') /* 空串或只有符号不合法。 */
        return 0;
    unsigned limit = negative ? (unsigned)(-(INT_MIN + 1)) + 1u : (unsigned)INT_MAX, value = 0; /* 避免直接对 INT_MIN 取负。 */
    for (; *s; ++s) { /* 逐位读取至终止零。 */
        if (*s < '0' || *s > '9')
            return 0; /* 不接受空白或非数字。 */
        unsigned digit = (unsigned)(*s - '0'); /* 字符转为数位。 */
        if (value > (limit - digit) / 10u)
            return 0; /* 乘十加数位前检查是否超出所选上限。 */
        value = value * 10u + digit; /* 扩展当前绝对值。 */
    }
    if (negative)
        *out = value == limit ? INT_MIN : -(int)value; /* 最小负数单独处理。 */
    else
        *out = (int)value; /* 正值已确认不超过 INT_MAX。 */
    return 1; /* 输出参数有效。 */
}
int main(void) {
    char s[102]; /* 容纳 100 字节、换行和终止零。 */
    if (!fgets(s, sizeof s, stdin))
        return 1; /* 无法读取行。 */
    size_t n = strcspn(s, "\n"); /* 找到换行或终止零。 */
    if (n > 100)
        return 1; /* 超长行不进行转换。 */
    s[n] = '\0'; /* 去掉换行。 */
    int value;
    if (my_atoi(s, &value)) /* 成功时 value 已写入。 */
        printf("%d\n", value);
    else
        puts("INVALID"); /* 格式错误或超出 int 范围。 */
    return 0;
}
