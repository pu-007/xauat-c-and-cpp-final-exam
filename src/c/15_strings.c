/* 15_strings 手写strlen/strcat/strcmp、回文 | ISO C99 | 提高
 * 来源/关系：S1 p42 编程5–7、p120 编程2；S5 p7 My_strcat（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入两行英语字符串，每行<=100字节；输出拼接、长度、字典序比较符号、第一行是否回文
 * 思想：字符串内容之后必须放零字符；容量包含该零字符；双指针从两端比较。
 * 复杂度：O(n+m)
 * 练习：补写有容量参数的copy；不要把字符数组等同于字符串。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <stddef.h>
static size_t length(const char *s) {
    size_t n = 0;
    while (s[n] != '\0')
        ++n;
    return n;
}
static int read_line(char s[102]) {
    if (!fgets(s, 102, stdin))
        return 0;
    size_t n = length(s);
    if (n && s[n - 1] == '\n')
        s[--n] = '\0';
    return n <= 100;
}
static int append(char *dest, size_t capacity, const char *src) {
    size_t a = length(dest), b = length(src);
    if (a >= capacity || b >= capacity - a)
        return 0; /* 留一个位置写\0。 */
    for (size_t i = 0; i <= b; ++i)
        dest[a + i] = src[i];
    return 1;
}
static int compare(const char *a, const char *b) {
    while (*a && *a == *b) {
        ++a;
        ++b;
    }
    return ((unsigned char)*a > (unsigned char)*b) - ((unsigned char)*a < (unsigned char)*b);
}
int main(void) {
    char a[102], b[102], joined[201] = "";
    if (!read_line(a) || !read_line(b) || !append(joined, sizeof joined, a) ||
        !append(joined, sizeof joined, b))
        return 1;
    size_t n = length(a);
    int palindrome = 1;
    for (size_t i = 0; i < n / 2; ++i)
        if (a[i] != a[n - 1 - i])
            palindrome = 0;
    printf("%s\n%zu %d %d\n", joined, length(joined), compare(a, b), palindrome);
    return 0;
}
