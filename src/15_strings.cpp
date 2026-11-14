/* 15_strings 手写strlen/strcat/strcmp、回文 | ISO C++11 | 提高
 * 来源/关系：S1 p42 编程5–7、p120 编程2；S5 p7 My_strcat（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入两行英语字符串，每行<=100字节；输出拼接、长度、字典序比较符号、第一行是否回文
 * 思想：字符串内容之后必须放零字符；容量包含该零字符；双指针从两端比较。
 * 复杂度：O(n+m)
 * 对照 15_strings.c：C 手写长度、拼接与比较，C++ string 管理容量。
 * 练习：补写有容量参数的copy；不要把字符数组等同于字符串。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 标准输入输出。
#include <string> // string、getline 对应 C 字符数组和 fgets。
#include <algorithm> // equal 比较对称字节，对应 C 手写循环。
int main() {
    // getline 保留空格、去掉换行；每行最长 100 字节。
    std::string a, b; // 保存两行文本。
    if (!std::getline(std::cin, a) || !std::getline(std::cin, b) || a.size() > 100 ||
        b.size() > 100) // 两行都要存在且不超过长度限制。
        return 1; // 输入失败或越界。
    auto joined = a + b; // string负责容量和结束符，size是字节数而非中文字数。
    // 两个布尔比较相减得到 -1、0 或 1。
    int order = (a > b) - (a < b); // 字典序关系转为符号。
    // 正向前半段与反向开头比较；空串比较范围为空。
    bool palindrome = std::equal(a.begin(), a.begin() + a.size() / 2, a.rbegin()); // 比较左右对称字节。
    // bool 默认按 0 或 1 输出。
    std::cout << joined << '\n' << joined.size() << ' ' << order << ' ' << palindrome << '\n'; // 输出两行。
}
