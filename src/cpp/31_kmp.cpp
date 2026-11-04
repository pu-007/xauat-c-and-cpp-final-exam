/* 31_kmp 字符串匹配：朴素法到KMP | ISO C++11 | 拓展
 * 来源/关系：S1 p61 编程8、p84 附加13的优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入文本和模式各一行<=1000字节；输出第一次匹配下标，未找到-1，空模式0
 * 思想：前缀函数记录最长相等真前后缀；失配时复用已经匹配的信息。
 * 复杂度：O(n+m)，空间O(m)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <string>
#include <vector>
int main() {
    std::string text, pattern;
    if (!std::getline(std::cin, text) || !std::getline(std::cin, pattern) || text.size() > 1000 ||
        pattern.size() > 1000)
        return 1;
    int n = static_cast<int>(text.size()), m = static_cast<int>(pattern.size());
    if (m == 0) {
        std::cout << "0\n";
        return 0;
    }
    std::vector<int> pi(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            ++j;
        pi[i] = j;
    }
    int answer = -1;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j])
            ++j;
        if (j == m) {
            answer = i - m + 1;
            break;
        }
    }
    std::cout << answer << '\n'; // 日常也可用text.find(pattern)，注意npos判定。
}
