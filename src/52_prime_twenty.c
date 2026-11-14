/* 52_prime_twenty：筛选并排序20个正整数中的素数 | ISO C99
 * 依据：S1 PDF第109页模拟一编程3；为方便上机核对，限定每数为1..1000000。
 * 题目：输入20个正整数；用函数找出素数，再用函数升序排序，重复素数保留。
 * 输出：一行素数，以单个空格分隔；没有素数时输出空行。
 * 算法：先试除判断每个数，把素数连续存入另一个数组；冒泡排序有效部分。
 * 复杂度：n个数、最大值M、k个素数时，最坏O(n*sqrt(M)+k*k)，空间O(n)。
 * C++对照：52_prime_twenty.cpp使用std::array与引用；本文件用数组和指针参数，
 *          用scanf/printf代替std::cin/std::cout；两版都手写素数判断和冒泡排序。
 */
#include <stdio.h> /* 声明scanf、printf和putchar。 */

#define COUNT 20 /* 原卷要求输入20个正整数。 */

static int is_prime(int value) { /* 返回1表示素数，返回0表示不是素数。 */
    if (value < 2) /* 1不是素数；保留此判断便于函数独立使用。 */
        return 0; /* 小于2的数直接排除。 */
    for (int divisor = 2; divisor <= value / divisor; ++divisor) { /* 只需试除到平方根。 */
        if (value % divisor == 0) /* 整除说明找到了非1且非自身的因子。 */
            return 0; /* 一旦发现因子就不再继续试除。 */
    }
    return 1; /* 没有发现因子，所以是素数。 */
}

static int find_primes(const int input[], int output[], int count) { /* 筛选并返回素数个数。 */
    int used = 0; /* output中已保存的有效元素数量。 */
    for (int i = 0; i < count; ++i) { /* 按输入顺序扫描每个数。 */
        if (is_prime(input[i])) { /* 只保留素数。 */
            output[used] = input[i]; /* 当前素数放在下一个空位。 */
            ++used; /* 扩大有效区间；重复素数也单独保存。 */
        }
    }
    return used; /* 主函数和排序函数只处理前used项。 */
}

static void bubble_sort(int values[], int count) { /* 原地将有效元素升序排列。 */
    for (int end = count - 1; end > 0; --end) { /* 每轮确定末尾一个最大值。 */
        for (int i = 0; i < end; ++i) { /* 相邻比较，不再处理已排好的后缀。 */
            if (values[i] > values[i + 1]) { /* 前项更大时交换。 */
                int temp = values[i]; /* 暂存前项，防止覆盖。 */
                values[i] = values[i + 1]; /* 较小值移到前面。 */
                values[i + 1] = temp; /* 较大值移到后面。 */
            }
        }
    }
}

int main(void) { /* C标准程序入口，无命令行参数。 */
    int input[COUNT]; /* 保存20个输入值。 */
    int primes[COUNT]; /* 最多有20个素数，容量与输入相同。 */
    for (int i = 0; i < COUNT; ++i) { /* 恰好读取20个值。 */
        if (scanf("%d", &input[i]) != 1 || input[i] < 1 || input[i] > 1000000) /* 读入并检查范围。 */
            return 1; /* 数据缺失或越界时退出，不输出结果。 */
    }
    int used = find_primes(input, primes, COUNT); /* 返回素数数组的有效长度。 */
    bubble_sort(primes, used); /* 排序有效元素；used为0或1时循环自然跳过。 */
    for (int i = 0; i < used; ++i) { /* 依次输出排序结果。 */
        if (i > 0) /* 首项之前不输出空格。 */
            putchar(' '); /* 其余元素之前输出一个分隔空格。 */
        printf("%d", primes[i]); /* 输出当前素数。 */
    }
    putchar('\n'); /* 无素数时也输出一行，保持输出契约。 */
    return 0; /* 正常结束。 */
}
