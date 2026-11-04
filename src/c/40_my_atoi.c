/* 40_my_atoi 有范围检查的数字字符串转换 | ISO C99 | 提高
 * 来源/关系：S6实验4(2) p28/31；原my_atoi的安全扩展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行最多100字节，可选+/-后接十进制数字，不接受空白；输出int或INVALID
 * 思想：逐位乘10前检查是否超限；明确格式与溢出政策。
 * 复杂度：O(字符串长度)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
static int my_atoi(const char *s, int *out) {
    int negative = 0;
    if (*s == '+' || *s == '-') {
        negative = *s == '-';
        ++s;
    }
    if (*s == '\0')
        return 0;
    unsigned limit = negative ? (unsigned)(-(INT_MIN + 1)) + 1u : (unsigned)INT_MAX, value = 0;
    for (; *s; ++s) {
        if (*s < '0' || *s > '9')
            return 0;
        unsigned digit = (unsigned)(*s - '0');
        if (value > (limit - digit) / 10u)
            return 0;
        value = value * 10u + digit;
    }
    if (negative)
        *out = value == limit ? INT_MIN : -(int)value;
    else
        *out = (int)value;
    return 1;
}
int main(void) {
    char s[102];
    if (!fgets(s, sizeof s, stdin))
        return 1;
    size_t n = strcspn(s, "\n");
    if (n > 100)
        return 1;
    s[n] = '\0';
    int value;
    if (my_atoi(s, &value))
        printf("%d\n", value);
    else
        puts("INVALID");
    return 0;
}
