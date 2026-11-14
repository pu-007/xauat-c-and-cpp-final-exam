/* 08_prime 单个整数的素数判定 | ISO C++11 | 基础
 * 来源/关系：S2 编程12；S5 p2/7；S1 模拟二编程1（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入-10^9..10^9的整数；输出0或1（是否素数）
 * 思想：非素数至少有一个因子<=平方根；d<=n/d避免d*d溢出。
 * 复杂度：O(sqrt(n))，空间O(1)
 * 练习：用函数筛选数组素数，再用12排序；对应S1模拟三最后一题。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * C对照：同目录08_prime.c包含stdbool.h并用scanf/printf；C++内置bool，使用cin/cout。
 */
#include <iostream> // 声明cin和cout；C版使用stdio.h。
bool is_prime(long long n) { // 判定一个整数是否为素数。
    if (n < 2) // 负数、0和1不满足素数定义。
        return false; // 直接排除小于2的数。
    for (long long d = 2; d <= n / d; ++d) // 只试除到平方根，避免d*d溢出。
        if (n % d == 0) // 整除说明存在非1且非自身的因子。
            return false; // 找到因子，停止试除。
    return true; // 没有找到因子，所以是素数。
}
int main() { // C++程序入口。
    long long n; // 保存待判断的整数。
    if (!(std::cin >> n) || n < -1000000000 || n > 1000000000)
        return 1; // 读取失败或超出范围时退出。
    std::cout << is_prime(n) << '\n'; // 默认将bool输出为0或1。
} // main自然结束时返回0。
