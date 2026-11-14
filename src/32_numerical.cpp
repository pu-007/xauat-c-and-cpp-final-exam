/* 32_numerical 数值迭代：莱布尼茨级数与牛顿法 | ISO C++11 | 提高
 * 来源/关系：S5 p1–2 求π；S1 p23 编程22的求根变式（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入x，0<=x<=10^12；输出牛顿法sqrt(x)及以原资料1e-6项阈值求得的π（六位小数）
 * 思想：递推避免重复运算；迭代要有容差和次数上限；项误差不等于最终π误差。
 * 复杂度：平方根至多1100次迭代；π约500000项，空间O(1)。
 * 对照 32_numerical.c：C 使用 math.h 的 fabs 和 printf，C++ 使用标准库流。
 * 练习：把sqrt结果与库函数比较；解释为何不能声称π精确到小数点后8位。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 使用 scanf、printf。
#include <iomanip> // 提供 setprecision；C 使用 printf 格式说明。
#include <cmath> // 提供 std::abs；C 对应使用 fabs。
int main() {
    double x; // 平方根的输入。
    if (!(std::cin >> x) || !(x >= 0 && x <= 1e12)) // 检查读取和范围。
        return 1; // 输入无效，退出。
    double root = x > 1 ? x : 1; // 选取正的初始值以避免除零。
    if (x == 0) // 零单独处理。
        root = 0; // 零的平方根为零。
    else
        for (int i = 0; i < 1100; ++i) { // 给极小正数足够迭代次数。
            double next = (root + x / root) / 2; // 牛顿法下一近似。
            if (std::abs(next - root) <= 1e-12 * std::abs(next)) { // 相对容差适用于小数。
                root = next; // 保存最新结果。
                break; // 已满足收敛条件。
            }
            root = next; // 更新后继续迭代。
        }
    double sum = 0; // π/4 的级数和。
    for (int k = 0; k < 1000000; ++k) { // 设置额外的循环上限。
        double term = (k % 2 ? -1.0 : 1.0) / (2 * k + 1); // 交替符号和奇数分母。
        if (std::abs(term) < 1e-6) // 小于阈值的首项不加入。
            break; // 阈值以下的项不累加。
        sum += term; // 累加当前项。
    }
    std::cout << std::fixed << std::setprecision(6) << root << ' ' << 4 * sum << '\n'; // 固定输出六位小数。
}
