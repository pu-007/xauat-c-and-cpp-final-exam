/* 45_string_max 三个字符串中字典序最大者 | ISO C++11 | 基础
 * 来源/关系：S6实验2(4) p13–14（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入3个无空格字符串，每个1..9字节；输出字典序最大者
 * 思想：strcmp比较内容；最大不是最长，比较规则基于字符编码。
 * 复杂度：O(字符串总长度)
 * 对照 45_string_max.c：C 数组使用 strcmp/strcpy，string 可直接比较并自动管理空间。
 * string 字典序比较对应 C 的 strcmp；string 赋值对应 strcpy 到足够大的字符数组。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 标准输入输出流。
#include <string> // 保存并比较字符串。
#include <algorithm> // max 选择字典序较大者。
int main() {
    std::string a, b, c; // 三个可变长度字符串。
    if (!(std::cin >> a >> b >> c) || a.size() > 9 || b.size() > 9 || c.size() > 9) // 检查输入和长度。
        return 1;
    std::cout << std::max(a, std::max(b, c)) << '\n'; // 两次字典序比较得到最大者。
}
