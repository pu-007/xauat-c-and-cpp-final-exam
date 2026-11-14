/* 11_reverse_rotate 逆序、循环右移、最小最大交换 | ISO C++11 | 提高
 * 来源/关系：S5 p5 例8.8、p8 习题3；S1 p61 编程2/3（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100,k=0..10^9，再输入n个int；先右移k位输出，再将最小换到首、最大换到尾后输出
 * 思想：用 rotate 将末尾 k 项移至前面；交换最小值后重新查找最大值。
 * 复杂度：时间 O(n)，vector 存储 O(n)。
 * 对照 11_reverse_rotate.c：C 三次反转；C++ 使用 rotate 和 iter_swap。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 标准输入输出。
#include <vector> // vector 管理元素，对应 C 定长数组。
#include <algorithm> // rotate、极值查找和 iter_swap 对应 C 手写操作。
void print(const std::vector<int> &a) {
    // 按顺序输出元素，首项之前不加空格。
    for (std::size_t i = 0; i < a.size(); ++i) // 遍历有效下标。
        std::cout << (i ? " " : "") << a[i]; // 首元素之前不加空格。
    std::cout << '\n'; // 结束当前行。
}
int main() {
    // 验证输入后构造长度为 n 的容器。
    int n, k; // 数组长度和旋转位数。
    if (!(std::cin >> n >> k) || n < 1 || n > 100 || k < 0 || k > 1000000000)
        return 1; // 防止长度无效或位数越界。
    std::vector<int> a(n); // 创建 n 个元素。
    for (int &x : a) // 引用直接指向容器中的元素。
        if (!(std::cin >> x))
            return 1; // 输入不完整。
    // 将右移 k 位转成以 end-k 为新首的旋转；k=0 时保持原样。
    k %= n; // 去除完整的旋转圈数。
    std::rotate(a.begin(), a.end() - k, a.end()); // 把后 k 项移到前面。
    print(a); // 输出旋转结果。
    // 先交换最小值，再在修改后的数组重新查找最大值。
    std::iter_swap(a.begin(), std::min_element(a.begin(), a.end())); // 首个最小值换到首位。
    std::iter_swap(a.end() - 1, std::max_element(a.begin(), a.end())); // 重新找首个最大值并换到末位。
    // 输出调整极值后的数组。
    print(a); // 输出调整后的结果。
}
