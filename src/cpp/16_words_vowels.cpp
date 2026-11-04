/* 16_words_vowels 单词状态机、元音筛选、字符排序 | ISO C++11 | 提高
 * 来源/关系：S5 p3 单词数、p7–8 元音/字符排序；S1 p32 编程14（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行<=100字节；单词按空白分隔；输出单词数、原顺序元音、升序字符（含空格）
 * 思想：状态从单词外进入单词内时才计数；筛选维护写位置，排序不包含结束符。
 * 复杂度：C字符排序O(n²)，C++排序O(n log n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
int main() {
    std::string s, word, vowels;
    if (!std::getline(std::cin, s) || s.size() > 100)
        return 1;
    std::istringstream input(s);
    int count = 0;
    while (input >> word)
        ++count;
    for (char c : s)
        if (std::string("aeiouAEIOU").find(c) != std::string::npos)
            vowels += c;
    std::sort(s.begin(), s.end(), [](unsigned char a, unsigned char b) { return a < b; });
    std::cout << count << '\n' << vowels << '\n' << s << '\n';
}
