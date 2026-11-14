/* 50_sign_count：统计十个整数的正、负、零个数（S2 PDF p52 编程6）。
 * 输入十个整数，每个在 -10^9..10^9；按符号分别计数。
 * 输出一行正数、负数、零的个数，单空格分隔，行末换行。
 * 时间 O(10)，额外空间 O(1)。
 * 对照 50_sign_count.c：C++ 用 cin/cout，C 用 scanf/printf；
 * 两者均以 long long 读入检查范围，并用 int 保存计数。
 */
#include <iostream> // 提供标准输入输出。

int main() { // 程序入口。
    int positive = 0, negative = 0, zero = 0; // 分别记录三类个数。
    for (int i = 0; i < 10; ++i) { // 恰好读取十个整数。
        long long value; // 用较宽类型检查范围。
        if (!(std::cin >> value) || value < -1000000000LL || value > 1000000000LL) return 1; // 检查输入。
        if (value > 0) { // 正数归入正数计数。
            ++positive; // 增加正数个数。
        } else if (value < 0) { // 负数归入负数计数。
            ++negative; // 增加负数个数。
        } else { // 剩余情况为零。
            ++zero; // 增加零的个数。
        }
    }
    std::cout << positive << ' ' << negative << ' ' << zero << '\n'; // 按指定顺序输出。
    return 0; // 正常结束。
}
