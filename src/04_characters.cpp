/* 04_characters 字母、数字、空格和其他字符统计 | ISO C++11 | 基础
 * 来源/关系：S1 p22 编程3；S2 填空1/5；S5 p1 例3.10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：读到换行或EOF；输出字母、数字、空格、其他的个数；只针对单字节英语文本
 * 思想：getline读取整行，字符分类函数接收unsigned char值。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 04_characters.c 用 getchar 逐字节读取，空间为 O(1)。
 * 本版本保存整行，空间为 O(n)。
 */
#include <iostream> // 声明cin和cout；C版使用getchar/printf。
#include <string> // 声明string和getline以保存整行。
#include <cctype> // 声明isalpha和isdigit字符分类函数。
int main() { // C++程序入口。
    std::string line; // 保存读取的行，不包含换行符。
    std::getline(std::cin, line); // 读取整行；直接遇到EOF时保持空字符串。
    int letters = 0, digits = 0, spaces = 0, other = 0; // 四类计数器从0开始。
    for (unsigned char c : line) { // 遍历行内字节，转换后可安全传给分类函数。
        if (std::isalpha(c)) // 字母包括大写和小写。
            ++letters; // 字母数增加1。
        else if (std::isdigit(c)) // 否则检查是否为数字。
            ++digits; // 数字数增加1。
        else if (c == ' ') // 只把普通空格归入空格类。
            ++spaces; // 空格数增加1；制表符不属于此类。
        else
            ++other; // 其余字符归入其他类。
    }
    std::cout << letters << ' ' << digits << ' ' << spaces << ' ' << other << '\n'; // 按题目顺序输出四个计数。
} // main自然结束时返回0。
