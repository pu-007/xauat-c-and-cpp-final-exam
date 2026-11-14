/* S1 PDF 第115页模拟二编程1：输出200至300之间的全部素数。
 * 算法：依次枚举区间内整数，由独立函数试除至平方根判断素数。
 * 时间复杂度 O(101*sqrt(300))，空间复杂度 O(1)；对应 C++11：48_prime_interval.cpp。
 * 输入：无；枚举闭区间200至300。输出：一行升序素数，数字间单空格，行末换行。
 * C++11 对照使用返回 bool 的 is_prime 函数及 std::cout；本版用整数真假和 printf。
 */
#include <stdio.h> /* 提供标准输出函数。 */

static int is_prime(int n) { /* 文件内使用的判断函数；整数0表示假，1表示真。 */
    if (n < 2) { /* 小于2的整数不是素数。 */
        return 0; /* 返回假。 */
    }
    for (int divisor = 2; divisor <= n / divisor; ++divisor) { /* 从2试除到平方根；除法写法避免平方溢出。 */
        if (n % divisor == 0) { /* 找到非平凡因子。 */
            return 0; /* 返回假。 */
        }
    }
    return 1; /* 没有因子，返回真。 */
}

int main(void) { /* 程序入口；void 表示不接收参数。 */
    int first = 1; /* 标记是否尚未输出第一个素数。 */
    for (int n = 200; n <= 300; ++n) { /* 从200递增到300，包含两个端点。 */
        if (is_prime(n)) { /* 只输出素数。 */
            if (!first) { /* 后续结果前需要分隔符。 */
                putchar(' '); /* 输出一个空格。 */
            }
            printf("%d", n); /* %d 按十进制输出当前素数。 */
            first = 0; /* 后续结果不再是第一个。 */
        }
    }
    putchar('\n'); /* 结束唯一的输出行。 */
    return 0; /* 表示正常结束。 */
}
