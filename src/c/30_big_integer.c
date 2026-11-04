/* 30_big_integer 十进制高精度阶乘 | ISO C99 | 拓展
 * 来源/关系：S1 p93 附加75、p94 附加77的大数思想（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000；输出精确n!
 * 思想：低位在前存每个十进制位；乘法逐位传播进位，绕开机器整数整体上限。
 * 复杂度：O(n·D)，D为n!位数，空间O(D)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0 || n > 1000)
        return 1;
    int digit[3000] = {1}, length = 1; /* 1000!有2568位，3000位容量足够。 */
    for (int factor = 2; factor <= n; ++factor) {
        int carry = 0;
        for (int i = 0; i < length; ++i) {
            int value = digit[i] * factor + carry;
            digit[i] = value % 10;
            carry = value / 10;
        }
        while (carry) {
            if (length == 3000)
                return 1;
            digit[length++] = carry % 10;
            carry /= 10;
        }
    }
    for (int i = length - 1; i >= 0; --i)
        printf("%d", digit[i]);
    putchar('\n');
    return 0;
}
