/* 31_kmp 字符串匹配：朴素法到KMP | ISO C99 | 拓展
 * 来源/关系：S1 p61 编程8、p84 附加13的优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入文本和模式各一行<=1000字节；输出第一次匹配下标，未找到-1，空模式0
 * 思想：前缀函数记录最长相等真前后缀；失配时复用已经匹配的信息。
 * 复杂度：O(n+m)，空间O(m)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <string.h>
static int read_line(char s[1002]) {
    if (!fgets(s, 1002, stdin))
        return 0;
    size_t n = strcspn(s, "\n");
    if (n > 1000)
        return 0;
    s[n] = '\0';
    return 1;
}
int main(void) {
    char text[1002], pattern[1002];
    int pi[1001] = {0};
    if (!read_line(text) || !read_line(pattern))
        return 1;
    int n = (int)strlen(text), m = (int)strlen(pattern);
    if (m == 0) {
        puts("0");
        return 0;
    }
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            ++j;
        pi[i] = j;
    }
    int answer = -1;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j])
            ++j;
        if (j == m) {
            answer = i - m + 1;
            break;
        }
    }
    printf("%d\n", answer);
    return 0;
}
