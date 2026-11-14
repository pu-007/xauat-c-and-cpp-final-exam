/* 49_min_to_end：把首次出现的最小元素交换到末尾（S1 PDF p115 模拟二编程3）。
 * 输入 n（1..100）和 n 个整数（-10^9..10^9）；自定义函数交换首次最小项和末项。
 * 输出一行 n 个整数，相邻项单空格分隔，行末换行。
 * 先线性查找，再交换；时间 O(n)，数组空间 O(n)。
 * 对照 49_min_to_end.c：C++ 用 cin/cout、vector<int> 和引用参数；
 * C 用 scanf/printf、定长数组及数组参数和长度，输入均先用 long long 检查范围。
 */
#include <iostream> // 提供标准输入输出。
#include <vector> // 提供动态数组。

void min_to_end(std::vector<int>& a) { // 引用允许函数修改原数组。
    std::size_t min_index = 0; // 首项暂定为首次最小项。
    for (std::size_t i = 1; i < a.size(); ++i) { // 扫描其余各项。
        if (a[i] < a[min_index]) { // 严格比较以保留首次位置。
            min_index = i; // 更新最小元素的位置。
        }
    }
    int temp = a[min_index]; // 暂存最小元素。
    a[min_index] = a.back(); // 把末项放到原位置。
    a.back() = temp; // 把最小元素放到末尾。
}

int main() { // 程序入口。
    long long value; // 用较宽类型检查输入范围。
    if (!(std::cin >> value) || value < 1 || value > 100) return 1; // 检查长度。
    const int n = static_cast<int>(value); // 已确认长度可安全转换。
    std::vector<int> a(n); // 创建 n 个元素的数组。
    for (int i = 0; i < n; ++i) { // 逐项读取。
        if (!(std::cin >> value) || value < -1000000000LL || value > 1000000000LL) return 1; // 检查元素。
        a[i] = static_cast<int>(value); // 保存合法元素。
    }
    min_to_end(a); // 调用自定义函数完成交换。
    for (int i = 0; i < n; ++i) { // 依次输出各项。
        if (i != 0) std::cout << ' '; // 相邻元素之间输出一个空格。
        std::cout << a[i]; // 输出当前元素。
    }
    std::cout << '\n'; // 结束结果行。
    return 0; // 正常结束。
}
