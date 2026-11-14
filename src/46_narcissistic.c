/* S1 PDF 第108页模拟一编程1：枚举全部三位水仙花数。
 * 算法：遍历100至999，拆出百位、十位和个位，比较各位立方之和。
 * 时间复杂度 O(900)，空间复杂度 O(1)；对应 C++11：46_narcissistic.cpp。
 * 输入：无；枚举范围为100至999。输出：一行升序结果，数字间单空格，行末换行。
 * C++11 对照使用 std::cout 输出、bool 标记首项；本版用 printf 和整数标志。
 */
#include <stdio.h> /* 提供标准输出函数。 */

int main(void) { /* 程序入口；void 表示不接收参数。 */
    int first = 1; /* 标记是否尚未输出第一个结果。 */
    for (int n = 100; n <= 999; ++n) { /* 从100开始逐一递增，包含999。 */
        int hundreds = n / 100; /* 整除取得百位。 */
        int tens = n / 10 % 10; /* 去掉个位后取得十位。 */
        int units = n % 10; /* 取余取得个位。 */
        int sum = hundreds * hundreds * hundreds + tens * tens * tens + units * units * units; /* 计算各位立方和。 */
        if (sum == n) { /* 立方和等于原数时输出。 */
            if (!first) { /* 后续结果前需要分隔符。 */
                putchar(' '); /* 输出一个空格。 */
            }
            printf("%d", n); /* %d 按十进制输出当前水仙花数。 */
            first = 0; /* 后续结果不再是第一个。 */
        }
    }
    putchar('\n'); /* 结束唯一的输出行。 */
    return 0; /* 表示正常结束。 */
}
