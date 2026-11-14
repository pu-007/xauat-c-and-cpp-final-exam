/* 30_big_integer 十进制高精度阶乘 | ISO C++11 | 拓展
 * 来源/关系：S1 p93 附加75、p94 附加77的大数思想（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000；输出精确n!
 * 思想：低位在前存每个十进制位；乘法逐位传播进位，绕开机器整数整体上限。
 * 复杂度：O(n·D)，D为n!位数，空间O(D)
 * 对照 30_big_integer.c：C 的位数组固定容量，C++ 的 vector 可动态增长。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 使用 scanf、printf 和 putchar。
#include <vector> // 提供可追加位数的 vector；C 使用定长数组。
int main() {
    int n; // 阶乘的上界。
    if (!(std::cin >> n) || n < 0 || n > 1000) // 拒绝读取失败或越界。
        return 1; // 输入非法，退出。
    std::vector<int> digit{1}; // 低位在前；初始值 1 也对应 0!。
    for (int factor = 2; factor <= n; ++factor) { // 依次乘入每个因子。
        int carry = 0; // 每次乘法从零进位开始。
        for (int &d : digit) { // 引用使修改直接写回每一位。
            int value = d * factor + carry; // 当前乘积加低位进位。
            d = value % 10; // 存储当前位。
            carry = value / 10; // 向高位传递进位。
        }
        while (carry) { // 继续拆出剩余进位。
            digit.push_back(carry % 10); // 动态追加新的最高位。
            carry /= 10; // 去掉已追加的最低位。
        }
    }
    for (auto it = digit.rbegin(); it != digit.rend(); ++it) // 反向迭代器从高位走到低位。
        std::cout << *it; // 输出迭代器指向的位。
    std::cout << '\n'; // 输出完成后换行。
}
