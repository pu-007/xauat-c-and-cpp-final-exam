/* 15_strings 手写strlen/strcat/strcmp、回文 | ISO C++11 | 提高
 * 来源/关系：S1 p42 编程5–7、p120 编程2；S5 p7 My_strcat（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入两行英语字符串，每行<=100字节；输出拼接、长度、字典序比较符号、第一行是否回文
 * 思想：字符串内容之后必须放零字符；容量包含该零字符；双指针从两端比较。
 * 复杂度：O(n+m)
 * 练习：补写有容量参数的copy；不要把字符数组等同于字符串。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <string>
#include <algorithm>
int main() {
    std::string a, b;
    if (!std::getline(std::cin, a) || !std::getline(std::cin, b) || a.size() > 100 ||
        b.size() > 100)
        return 1;
    auto joined = a + b; // string负责容量和结束符，size是字节数而非中文字数。
    int order = (a > b) - (a < b);
    bool palindrome = std::equal(a.begin(), a.begin() + a.size() / 2, a.rbegin());
    std::cout << joined << '\n' << joined.size() << ' ' << order << ' ' << palindrome << '\n';
}
