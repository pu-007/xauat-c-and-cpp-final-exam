/* S1 PDF 第115页模拟二编程1：输出200至300之间的全部素数。
 * 算法：依次枚举区间内整数，由独立函数试除至平方根判断素数。
 * 时间复杂度 O(101*sqrt(300))，空间复杂度 O(1)；对应 C99：48_prime_interval.c。
 * 输入：无；枚举闭区间200至300。输出：一行升序素数，数字间单空格，行末换行。
 * C99 对照使用返回 int 的 is_prime 函数及 printf/putchar；本版用 bool 和输出流。
 */
#include <iostream> // 提供标准输出流。

static bool is_prime(int n) { // 文件内使用的判断函数；bool 表示真或假。
    if (n < 2) { // 小于2的整数不是素数。
        return false; // 返回假。
    }
    for (int divisor = 2; divisor <= n / divisor; ++divisor) { // 从2试除到平方根；除法写法避免平方溢出。
        if (n % divisor == 0) { // 找到非平凡因子。
            return false; // 返回假。
        }
    }
    return true; // 没有因子，返回真。
}

int main() { // 程序入口，不接收参数。
    bool first = true; // 标记是否尚未输出第一个素数。
    for (int n = 200; n <= 300; ++n) { // 从200递增到300，包含两个端点。
        if (is_prime(n)) { // 只输出素数。
            if (!first) { // 后续结果前需要分隔符。
                std::cout << ' '; // 输出一个空格。
            }
            std::cout << n; // 输出当前素数。
            first = false; // 后续结果不再是第一个。
        }
    }
    std::cout << '\n'; // 结束唯一的输出行。
    return 0; // 表示正常结束。
}
