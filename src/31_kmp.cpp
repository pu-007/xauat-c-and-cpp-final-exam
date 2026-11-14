/* 31_kmp 字符串匹配：朴素法到KMP | ISO C++11 | 拓展
 * 来源/关系：S1 p61 编程8、p84 附加13的优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入文本和模式各一行<=1000字节；输出第一次匹配下标，未找到-1，空模式0
 * 思想：前缀函数记录最长相等真前后缀；失配时复用已经匹配的信息。
 * 复杂度：O(n+m)，空间O(m)
 * 对照 31_kmp.c：C 使用字符数组和 fgets，C++ 使用 string 和 getline。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 用 stdin 和 printf。
#include <string> // 提供 string 和 getline；C 用字符数组和 fgets。
#include <vector> // 保存动态前缀表；C 使用定长整型数组。
int main() {
    std::string text, pattern; // 分别保存文本行和模式行。
    if (!std::getline(std::cin, text) || !std::getline(std::cin, pattern) || text.size() > 1000 ||
        pattern.size() > 1000) // 拒绝缺行或超过字节上限。
        return 1; // 输入非法时以非零状态结束。
    int n = static_cast<int>(text.size()), m = static_cast<int>(pattern.size()); // 已检查长度，可安全转 int。
    if (m == 0) { // 空模式在下标零匹配。
        std::cout << "0\n"; // 输出空模式的约定位置。
        return 0; // 已处理完毕。
    }
    std::vector<int> pi(m, 0); // pi[i] 是模式前缀的最长相等真前后缀长度。
    for (int i = 1, j = 0; i < m; ++i) { // 从第二个字节开始构建前缀表。
        while (j > 0 && pattern[i] != pattern[j]) // 当前候选失配。
            j = pi[j - 1]; // 回退到更短的候选。
        if (pattern[i] == pattern[j]) // 可以延长当前相等前后缀。
            ++j; // 相等前后缀延长一字节。
        pi[i] = j; // 保存本位置的最长长度。
    }
    int answer = -1; // 默认没有匹配。
    for (int i = 0, j = 0; i < n; ++i) { // 逐字节扫描文本。
        while (j > 0 && text[i] != pattern[j]) // 失配时缩短已匹配长度。
            j = pi[j - 1]; // 回退到前缀表给出的长度。
        if (text[i] == pattern[j]) // 该字节匹配则继续扩展。
            ++j; // 已匹配长度增加一。
        if (j == m) { // 整个模式已匹配。
            answer = i - m + 1; // 将末尾位置转换为起点。
            break; // 立即停止，保证得到首次匹配。
        }
    }
    std::cout << answer << '\n'; // 输出起点或 -1；也可用 find 并检查 npos。
}
