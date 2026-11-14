/* 31_kmp 字符串匹配：朴素法到KMP | ISO C99 | 拓展
 * 来源/关系：S1 p61 编程8、p84 附加13的优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入文本和模式各一行<=1000字节；输出第一次匹配下标，未找到-1，空模式0
 * 思想：前缀函数记录最长相等真前后缀；失配时复用已经匹配的信息。
 * 复杂度：O(n+m)，空间O(m)
 * 对照 31_kmp.cpp：C 使用字符数组和 fgets，C++ 使用 string 和 getline。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 声明 fgets、puts、printf 和 stdin；C++ 使用 getline、cout。 */
#include <string.h> /* 声明 strcspn 和 strlen；C++ string 提供 size。 */
static int read_line(char s[1002]) { /* 读取最多 1000 字节的一行。 */
    if (!fgets(s, 1002, stdin)) /* 缺少输入行。 */
        return 0; /* 向调用者报告读取失败。 */
    size_t n = strcspn(s, "\n"); /* 找换行位置；没有换行时得到字符串长度。 */
    if (n > 1000) /* 读到第 1001 个字节则超长。 */
        return 0; /* 向调用者报告行超长。 */
    s[n] = '\0'; /* 去掉换行或保留末尾终止符。 */
    return 1; /* 成功读取。 */
}
int main(void) {
    char text[1002], pattern[1002]; /* 文本及模式缓冲区。 */
    int pi[1001] = {0}; /* 前缀函数，首项为零。 */
    if (!read_line(text) || !read_line(pattern)) /* 两行都必须成功读取。 */
        return 1; /* 输入非法时以非零状态结束。 */
    int n = (int)strlen(text), m = (int)strlen(pattern); /* 字节长度不超过 1000。 */
    if (m == 0) { /* 空模式约定在下标零匹配。 */
        puts("0"); /* 输出约定的匹配位置。 */
        return 0; /* 空模式已处理完毕。 */
    }
    for (int i = 1, j = 0; i < m; ++i) { /* 为模式的每个前缀构建 pi。 */
        while (j > 0 && pattern[i] != pattern[j]) /* 失配时缩短候选前缀。 */
            j = pi[j - 1]; /* 回退到上一个相等真前后缀。 */
        if (pattern[i] == pattern[j]) /* 当前字节可延长匹配。 */
            ++j; /* 匹配长度增加一。 */
        pi[i] = j; /* 保存最长长度。 */
    }
    int answer = -1; /* 默认未找到。 */
    for (int i = 0, j = 0; i < n; ++i) { /* 扫描文本，j 为已匹配模式长度。 */
        while (j > 0 && text[i] != pattern[j]) /* 失配时利用前缀表回退。 */
            j = pi[j - 1]; /* 复用最长相等前后缀。 */
        if (text[i] == pattern[j]) /* 当前字节匹配则扩展。 */
            ++j; /* 已匹配长度增加一。 */
        if (j == m) { /* 完整模式首次匹配。 */
            answer = i - m + 1; /* 根据末尾下标计算起点。 */
            break; /* 首次匹配即最小下标。 */
        }
    }
    printf("%d\n", answer); /* 输出起点或 -1。 */
    return 0; /* 正常结束。 */
}
