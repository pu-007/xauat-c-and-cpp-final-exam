/* 04_characters 字符分类与大小写 | ISO C++11 | 基础
 * 来源/关系：S1 p22 编程3；S2 填空1/5；S5 p1 例3.10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：读到换行或EOF；输出字母、数字、空格、其他的个数；只针对单字节英语文本
 * 思想：getchar用int接收EOF；字符分类函数接收unsigned char值。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <string>
#include <cctype>
int main() {
    std::string line;
    std::getline(std::cin, line);
    int letters = 0, digits = 0, spaces = 0, other = 0;
    for (unsigned char c : line) { // 范围for不处理字符串末尾的隐式零字符。
        if (std::isalpha(c))
            ++letters;
        else if (std::isdigit(c))
            ++digits;
        else if (c == ' ')
            ++spaces;
        else
            ++other;
    }
    std::cout << letters << ' ' << digits << ' ' << spaces << ' ' << other << '\n';
}
