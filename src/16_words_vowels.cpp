/* 16_words_vowels 单词状态机、元音筛选、字符排序 | ISO C++11 | 提高
 * 来源/关系：S5 p3 单词数、p7–8 元音/字符排序；S1 p32 编程14（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行<=100字节；单词按空白分隔；输出单词数、原顺序元音、升序字符（含空格）
 * 思想：用字符串流按空白提取单词，按原序收集元音，再排序全部字节。
 * 复杂度：C字符排序O(n²)，C++排序O(n log n)
 * 对照 16_words_vowels.c：C 用状态机计数及冒泡，C++ 使用流和 sort。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 标准输入输出。
#include <sstream> // istringstream 按空白分词，对应 C 状态机。
#include <string> // string、getline 和 find 对应 C 字符数组操作。
#include <algorithm> // sort 对应 C 的冒泡排序。
int main() {
    // 读取整行；空行允许，长度按字节检查。
    std::string s, word, vowels; // 输入、临时单词和元音结果。
    if (!std::getline(std::cin, s) || s.size() > 100) // 保留空格并检查长度。
        return 1; // 输入失败或过长。
    // 字符串流按空白分词，每成功提取一次计一个单词。
    std::istringstream input(s); // 从输入行构造分词流。
    int count = 0; // 已提取的单词数。
    while (input >> word) // 运算符按空白跳过分隔符并读取一个单词。
        ++count; // 每次成功提取加一。
    // 只筛选大小写英文元音，保留原顺序。
    for (char c : s) // 遍历原始字符。
        if (std::string("aeiouAEIOU").find(c) != std::string::npos) // 判断元音集合。
            vowels += c; // 按出现顺序追加。
    // 转为无符号字节比较，空格同样参与排序。
    std::sort(s.begin(), s.end(), [](unsigned char a, unsigned char b) { return a < b; }); // 升序排列所有字节。
    // 即使元音或原行为空，也保留对应输出行。
    std::cout << count << '\n' << vowels << '\n' << s << '\n'; // 依次输出三行。
}
