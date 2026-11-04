/* 40_my_atoi 有范围检查的数字字符串转换 | ISO C++11 | 提高
 * 来源/关系：S6实验4(2) p28/31；原my_atoi的安全扩展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行最多100字节，可选+/-后接十进制数字，不接受空白；输出int或INVALID
 * 思想：逐位乘10前检查是否超限；明确格式与溢出政策。
 * 复杂度：O(字符串长度)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <string>
#include <stdexcept>
int main() {
    std::string s;
    if (!std::getline(std::cin, s) || s.size() > 100)
        return 1;
    std::size_t begin = (!s.empty() && (s[0] == '+' || s[0] == '-')) ? 1 : 0;
    bool valid = begin < s.size();
    for (std::size_t i = begin; i < s.size(); ++i)
        if (s[i] < '0' || s[i] > '9')
            valid = false;
    if (!valid) {
        std::cout << "INVALID\n";
        return 0;
    }
    try {
        std::size_t used = 0;
        int value = std::stoi(s, &used);
        if (used != s.size())
            std::cout << "INVALID\n";
        else
            std::cout << value << '\n';
    } catch (const std::invalid_argument &) {
        std::cout << "INVALID\n";
    } catch (const std::out_of_range &) {
        std::cout << "INVALID\n";
    }
}
