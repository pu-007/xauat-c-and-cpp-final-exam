/* 41_global_scores 全局数组与输出参数 | ISO C++11 | 提高
 * 来源/关系：S6实验3(4) p18、p23–24；题意重写（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10个0..100成绩；输出均分、最低、最高；再输出两次静态计数器结果
 * 思想：全局数组体现实验要求；再通过指针/引用返回多个结果；static保存跨调用状态。
 * 复杂度：固定10项；推广n项时O(n)
 * 对照 41_global_scores.c：C 指针返回极值；C++ 引用返回极值，array 保存成绩。
 * statistics(low,high) 的引用对应 C 传入 &low、&high；fixed/setprecision(2) 对应 %.2f。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 读写成绩。
#include <array> // 固定长度成绩数组。
#include <iomanip> // fixed 和 setprecision 控制小数位。
namespace {
std::array<double, 10> scores; // 匿名命名空间内的文件作用域数组。
} // namespace
double statistics(double &low, double &high) {
    low = high = scores[0]; // 引用直接修改调用者的极值变量。
    double sum = 0; // 从零累计。
    for (double x : scores) { // 遍历全部十项。
        sum += x;
        if (x < low)
            low = x; // 更新最低分。
        if (x > high)
            high = x; // 更新最高分。
    }
    return sum / 10; // 返回平均分。
}
int counter() {
    static int calls = 0; // 局部静态变量只初始化一次。
    return ++calls; // 返回递增后的调用次数。
}
int main() {
    for (double &x : scores) // 通过引用逐项读入。
        if (!(std::cin >> x) || !(x >= 0 && x <= 100))
            return 1; // 拒绝输入失败或非法成绩。
    double low, high, average = statistics(low, high); // 引用参数接收极值。
    std::cout << std::fixed << std::setprecision(2) << average << ' ' << low << ' ' << high << '\n';
    int a = counter(), b = counter(); // 顺序调用两次，状态在调用之间保留。
    std::cout << a << ' ' << b << '\n';
}
