/* 40_my_atoi 有范围检查的数字字符串转换 | ISO C++11 | 提高
 * 来源/关系：S6实验4(2) p28/31；原my_atoi的安全扩展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行最多100字节，可选+/-后接十进制数字，不接受空白；输出int或INVALID
 * 思想：逐位乘10前检查是否超限；明确格式与溢出政策。
 * 复杂度：O(字符串长度)
 * 对照 40_my_atoi.c：C 手动检查溢出并通过指针返回结果；C++ 使用 stoi 和异常。
 * getline 对应 C 的 fgets 加 strcspn 去换行；cout 对应 printf/puts。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 处理输入输出。
#include <string> // string、getline 和 stoi。
#include <stdexcept> // stoi 的异常类型。
int main() {
    std::string s; // 保存输入的整行，不包括换行符。
    if (!std::getline(std::cin, s) || s.size() > 100)
        return 1; // 输入失败或超过长度限制。
    std::size_t begin = (!s.empty() && (s[0] == '+' || s[0] == '-')) ? 1 : 0; // 跳过可选符号。
    bool valid = begin < s.size(); // 至少需要一个数字。
    for (std::size_t i = begin; i < s.size(); ++i)
        if (s[i] < '0' || s[i] > '9')
            valid = false; // 包括空白在内的其他字符均非法。
    if (!valid) {
        std::cout << "INVALID\n";
        return 0;
    }
    try {
        std::size_t used = 0; // stoi 返回已消耗字符数。
        int value = std::stoi(s, &used); // 超出 int 范围时抛异常。
        if (used != s.size())
            std::cout << "INVALID\n"; // 防止只转换前缀。
        else
            std::cout << value << '\n';
    } catch (const std::invalid_argument &) { // 无法转换。
        std::cout << "INVALID\n";
    } catch (const std::out_of_range &) { // 超出 int 范围。
        std::cout << "INVALID\n";
    }
}
