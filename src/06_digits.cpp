/* 06_digits 数位拆分、水仙花数 | ISO C++11 | 基础
 * 来源/关系：S1 p22 编程12、p120 编程1；S5 p6–7 水仙花数（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..999999999；输出位数、数字和、倒序数字；再输出所有三位水仙花数
 * 思想：模10取末位，除10删末位；do-while正确处理0。
 * 复杂度：O(log n)，枚举三位数为常数工作
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * C对照：同目录06_digits.c使用scanf/printf和整数标志；本版使用cin/cout和bool。
 */
#include <iostream> // 声明cin和cout；C版使用stdio.h。
int main() { // C++程序入口。
    long long n; // 保存待拆分的非负整数。
    if (!(std::cin >> n) || n < 0 || n > 999999999)
        return 1; // 读取失败或超出范围时退出。
    int count = 0, sum = 0; // 依次记录已处理的位数与数字和。
    long long reversed = 0; // 保存从右向左拼出的倒序数字。
    do { // 至少执行一次，因此输入0也能正确算出一位。
        int d = static_cast<int>(n % 10); // 取末位并显式转换为int。
        ++count; // 多处理了一位。
        sum += d; // 加入数字和。
        reversed = reversed * 10 + d; // 原结果左移一位后接上当前数字。
        n /= 10; // 删除刚处理的末位。
    } while (n); // 还有更高位时继续。
    std::cout << count << ' ' << sum << ' ' << reversed << '\n'; // 输出三项结果。
    bool first = true; // 控制第一个水仙花数前没有空格。
    for (int x = 100; x < 1000; ++x) { // 枚举每个三位数。
        int a = x / 100, b = x / 10 % 10, c = x % 10; // 取百位、十位、个位。
        if (a * a * a + b * b * b + c * c * c == x) { // 三位立方和等于原数。
            if (!first) // 第二项开始在数字前输出空格。
                std::cout << ' '; // 输出分隔符。
            std::cout << x; // 输出当前水仙花数。
            first = false; // 后续结果不再是首项。
        }
    }
    std::cout << '\n'; // 结束水仙花数所在行。
} // main自然结束时返回0。
