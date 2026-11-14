/* 52_prime_twenty：筛选并排序20个正整数中的素数 | ISO C++11
 * 依据：S1 PDF第109页模拟一编程3；为方便上机核对，限定每数为1..1000000。
 * 题目：输入20个正整数；用函数找出素数，再用函数升序排序，重复素数保留。
 * 输出：一行素数，以单个空格分隔；没有素数时输出空行。
 * 算法：先试除判断每个数，把素数连续存入另一个数组；冒泡排序有效部分。
 * 复杂度：n个数、最大值M、k个素数时，最坏O(n*sqrt(M)+k*k)，空间O(n)。
 * C对照：52_prime_twenty.c使用普通数组与指针参数，本版用std::array及引用；
 *        C用scanf/printf，本版用std::cin/std::cout；两版均手写素数判断和排序。
 */
#include <array> /* 声明固定大小数组std::array。 */
#include <iostream> /* 声明标准输入输出流。 */

const int COUNT = 20; /* 原卷要求输入20个正整数。 */

static bool is_prime(int value) { /* 返回true表示素数。 */
    if (value < 2) /* 1不是素数；保留此判断便于函数独立使用。 */
        return false; /* 小于2的数直接排除。 */
    for (int divisor = 2; divisor <= value / divisor; ++divisor) { /* 只需试除到平方根。 */
        if (value % divisor == 0) /* 整除说明找到了非1且非自身的因子。 */
            return false; /* 找到因子，停止试除。 */
    }
    return true; /* 没有发现因子，所以是素数。 */
}

static int find_primes(const std::array<int, COUNT> &input, std::array<int, COUNT> &output) { /* 引用避免复制数组。 */
    int used = 0; /* output中已保存的有效元素数量。 */
    for (int value : input) { /* 按输入顺序读取每个元素。 */
        if (is_prime(value)) { /* 只保留素数。 */
            output[used] = value; /* 当前素数放在下一个空位。 */
            ++used; /* 扩大有效区间；重复素数也单独保存。 */
        }
    }
    return used; /* 主函数和排序函数只处理前used项。 */
}

static void bubble_sort(std::array<int, COUNT> &values, int count) { /* 引用使修改作用于调用者数组。 */
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

int main() { /* C++程序入口。 */
    std::array<int, COUNT> input; /* 保存20个输入值。 */
    std::array<int, COUNT> primes; /* 最多有20个素数，容量与输入相同。 */
    for (int &value : input) { /* 引用使输入操作直接写入数组元素。 */
        if (!(std::cin >> value) || value < 1 || value > 1000000) /* 读入并检查范围。 */
            return 1; /* 数据缺失或越界时退出，不输出结果。 */
    }
    int used = find_primes(input, primes); /* 返回素数数组的有效长度。 */
    bubble_sort(primes, used); /* 排序有效元素；used为0或1时循环自然跳过。 */
    for (int i = 0; i < used; ++i) { /* 依次输出排序结果。 */
        if (i > 0) /* 首项之前不输出空格。 */
            std::cout << ' '; /* 其余元素之前输出一个分隔空格。 */
        std::cout << primes[i]; /* 输出当前素数。 */
    }
    std::cout << '\n'; /* 无素数时也输出一行，保持输出契约。 */
    return 0; /* 正常结束。 */
}
