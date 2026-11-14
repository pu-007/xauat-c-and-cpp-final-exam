/* 16_words_vowels 单词状态机、元音筛选、字符排序 | ISO C99 | 提高
 * 来源/关系：S5 p3 单词数、p7–8 元音/字符排序；S1 p32 编程14（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行<=100字节；单词按空白分隔；输出单词数、原顺序元音、升序字符（含空格）
 * 思想：状态从单词外进入单词内时才计数；筛选维护写位置，排序不包含结束符。
 * 复杂度：C字符排序O(n²)，C++排序O(n log n)
 * 对照 16_words_vowels.cpp：C 手写状态机和冒泡排序，C++ 使用流和 sort。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* fgets 和 printf，对应 C++ getline 和 cout。 */
#include <string.h> /* strcspn 查换行、strchr 查元音；C++ 使用 string。 */
#include <ctype.h> /* isspace 判断空白；C++ 用字符串流分词。 */
int main(void) {
    /* 输入缓冲区容纳 100 字节、换行和结束符。 */
    char s[102], vowels[102]; /* 分别保存输入和筛出的元音。 */
    if (!fgets(s, sizeof s, stdin)) /* 读取包括空格的一行。 */
        return 1; /* 无输入则退出。 */
    /* 找到换行或末尾，超过 100 字节则拒绝。 */
    size_t n = strcspn(s, "\n"); /* 换行位置，也是正文长度。 */
    if (n > 100) /* 未在允许长度内结束。 */
        return 1;
    s[n] = '\0'; /* 去除换行或保持原结束符。 */
    /* inside 记录当前位置之前是否处于单词中。 */
    int inside = 0, count = 0; /* 最初位于单词外，计数为零。 */
    size_t used = 0; /* 已保存的元音数量。 */
    for (size_t i = 0; i < n; ++i) { /* 扫描每个正文字符。 */
        /* 转成 unsigned char 才可安全传给字符分类函数。 */
        unsigned char c = (unsigned char)s[i]; /* 字符分类要求非负字节值。 */
        /* 遇空白离开单词；只有从外进入时增加计数。 */
        if (isspace(c)) /* 空白分隔单词。 */
            inside = 0; /* 进入单词外状态。 */
        else if (!inside) { /* 从外部进入一个单词。 */
            ++count; /* 每个单词只计数一次。 */
            inside = 1; /* 后续连续字符仍属于这个单词。 */
        }
        /* 将元音按出现顺序写入结果，不改变原数组。 */
        if (strchr("aeiouAEIOU", c)) /* 检查是否为指定元音。 */
            vowels[used++] = s[i]; /* 追加并移动写位置。 */
    }
    /* 为结果补结束符，再用冒泡排序原字符（不包含结束符）。 */
    vowels[used] = '\0'; /* 手动终止结果字符串。 */
    for (size_t i = 1; i < n; ++i) /* 每轮固定一个后缀位置。 */
        for (size_t j = 0; j < n - i; ++j) /* 比较未排序部分的相邻字符。 */
            /* 按无符号字节比较，避免 char 有符号性改变排序。 */
            if ((unsigned char)s[j] > (unsigned char)s[j + 1]) { /* 逆序时交换。 */
                char t = s[j]; /* 暂存左侧字符。 */
                s[j] = s[j + 1]; /* 较小字符移到左侧。 */
                s[j + 1] = t; /* 暂存字符移到右侧。 */
            }
    /* 三项结果各占一行，包括空结果。 */
    printf("%d\n%s\n%s\n", count, vowels, s); /* 输出三行。 */
    return 0; /* 正常结束。 */
}
