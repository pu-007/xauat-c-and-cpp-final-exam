/* 30_big_integer 十进制高精度阶乘 | ISO C99 | 拓展
 * 来源/关系：S1 p93 附加75、p94 附加77的大数思想（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000；输出精确n!
 * 思想：低位在前存每个十进制位；乘法逐位传播进位，绕开机器整数整体上限。
 * 复杂度：O(n·D)，D为n!位数，空间O(D)
 * 对照 30_big_integer.cpp：C 的位数组固定容量，C++ 的 vector 可动态增长。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 声明 scanf、printf 和 putchar；C++ 使用输入输出流。 */
int main(void) {
    int n; /* 阶乘的上界。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 1000) /* 检查读入与支持范围。 */
        return 1; /* 输入不合法，退出。 */
    int digit[3000] = {1}, length = 1; /* 低位在前，初值 1；1000! 共 2568 位。 */
    for (int factor = 2; factor <= n; ++factor) { /* 依次乘入每一个因子。 */
        int carry = 0; /* 本轮从最低位开始，初始进位为零。 */
        for (int i = 0; i < length; ++i) { /* 逐位乘法。 */
            int value = digit[i] * factor + carry; /* 当前位乘积加前一位进位。 */
            digit[i] = value % 10; /* 保存当前十进制位。 */
            carry = value / 10; /* 其余部分传给更高位。 */
        }
        while (carry) { /* 已有位处理完后继续拆分剩余进位。 */
            if (length == 3000) /* 避免写出数组边界。 */
                return 1; /* 容量耗尽时停止，避免越界。 */
            digit[length++] = carry % 10; /* 追加最低一位并增加长度。 */
            carry /= 10; /* 去掉已经追加的一位。 */
        }
    }
    for (int i = length - 1; i >= 0; --i) /* 从最高位向最低位输出。 */
        printf("%d", digit[i]); /* 输出当前十进制位。 */
    putchar('\n'); /* 数字结束后换行。 */
    return 0; /* 正常结束。 */
}
