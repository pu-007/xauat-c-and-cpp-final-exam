/* 15_strings 手写strlen/strcat/strcmp、回文 | ISO C99 | 提高
 * 来源/关系：S1 p42 编程5–7、p120 编程2；S5 p7 My_strcat（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入两行英语字符串，每行<=100字节；输出拼接、长度、字典序比较符号、第一行是否回文
 * 思想：字符串内容之后必须放零字符；容量包含该零字符；双指针从两端比较。
 * 复杂度：O(n+m)
 * 对照 15_strings.cpp：C 手动维护结束符和容量，C++ string 管理存储。
 * 练习：补写有容量参数的copy；不要把字符数组等同于字符串。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* fgets、printf；C++ 对应 getline、cout。 */
#include <stddef.h> /* size_t 保存长度；C++ string 的 size 返回无符号长度。 */
static size_t length(const char *s) {
    /* 从首字节计数，遇到结束符停止；不计结束符本身。 */
    size_t n = 0; /* 初始长度为零。 */
    while (s[n] != '\0') /* 扫描到结束符为止。 */
        ++n; /* 当前字节属于内容。 */
    return n; /* 返回内容字节数。 */
}
static int read_line(char s[102]) {
    /* fgets 最多读取 101 字节并保留结束符，再去掉末尾换行。 */
    if (!fgets(s, 102, stdin)) /* 最多读取 101 个输入字节。 */
        return 0; /* 没有读到一行。 */
    size_t n = length(s); /* 当前内容长度。 */
    if (n && s[n - 1] == '\n') /* 空串不能检查 n-1。 */
        s[--n] = '\0'; /* 覆盖换行并同步缩短长度。 */
    return n <= 100; /* 超出允许长度则失败。 */
}
static int append(char *dest, size_t capacity, const char *src) {
    /* 两个长度之和必须小于容量，为结束符保留一格。 */
    size_t a = length(dest), b = length(src); /* 两个内容长度。 */
    if (a >= capacity || b >= capacity - a) /* 避免加法溢出并为结束符留位。 */
        return 0;
    /* 包含 src 的结束符一起复制，因此 i 可以等于 b。 */
    for (size_t i = 0; i <= b; ++i) /* 连结束符一起复制。 */
        dest[a + i] = src[i]; /* 从目标末尾开始写。 */
    return 1; /* 拼接成功。 */
}
static int compare(const char *a, const char *b) {
    /* 跳过相同前缀；遇到不同字节或第一个字符串结束时比较。 */
    while (*a && *a == *b) { /* 沿共同前缀前进。 */
        ++a; /* 前进第一个指针。 */
        ++b; /* 同步前进第二个指针。 */
    }
    return ((unsigned char)*a > (unsigned char)*b) - ((unsigned char)*a < (unsigned char)*b); /* 无符号字节比较得到符号。 */
}
/* 两个输入最多各 100 字节，拼接缓冲区还需一字节结束符。 */
int main(void) {
    char a[102], b[102], joined[201] = ""; /* 初始化为空字符串。 */
    if (!read_line(a) || !read_line(b) || !append(joined, sizeof joined, a) ||
        !append(joined, sizeof joined, b)) /* 两次拼接都要成功。 */
        return 1; /* 输入或容量不合法。 */
    /* 从两头比较一半；空串和单字符自然保持回文。 */
    size_t n = length(a); /* 第一行的字节长度。 */
    int palindrome = 1; /* 默认回文。 */
    for (size_t i = 0; i < n / 2; ++i) /* 只比较前半部分。 */
        if (a[i] != a[n - 1 - i]) /* 比较对称位置。 */
            palindrome = 0; /* 任一不相等即不是回文。 */
    /* 输出拼接、字节长度、比较符号与回文标记。 */
    printf("%s\n%zu %d %d\n", joined, length(joined), compare(a, b), palindrome); /* 两行输出。 */
    return 0; /* 正常结束。 */
}
