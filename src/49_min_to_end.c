/* 49_min_to_end：把首次出现的最小元素交换到末尾（S1 PDF p115 模拟二编程3）。
 * 输入 n（1..100）和 n 个整数（-10^9..10^9）；自定义函数交换首次最小项和末项。
 * 输出一行 n 个整数，相邻项单空格分隔，行末换行。
 * 先线性查找，再交换；时间 O(n)，数组空间 O(n)。
 * 对照 49_min_to_end.cpp：C 用 scanf/printf、定长数组及数组参数和长度；
 * C++ 用 cin/cout、vector<int> 和引用参数，输入均先用 long long 检查范围。
 */
#include <stdio.h> /* 提供标准输入输出。 */

static void min_to_end(int a[], int n) { /* 接收数组及其有效长度。 */
    int min_index = 0; /* 默认首项是首次最小项。 */
    for (int i = 1; i < n; ++i) { /* 扫描其余各项。 */
        if (a[i] < a[min_index]) { /* 严格小于才更新，保留首次位置。 */
            min_index = i; /* 记录更小元素的位置。 */
        }
    }
    int temp = a[min_index]; /* 暂存最小元素。 */
    a[min_index] = a[n - 1]; /* 把末项放到最小元素原位置。 */
    a[n - 1] = temp; /* 把最小元素放到末尾。 */
}

int main(void) { /* 程序入口。 */
    int n, a[100]; /* 保存长度及最多 100 项。 */
    long long value; /* 使用较宽类型先检查输入范围。 */
    if (scanf("%lld", &value) != 1 || value < 1 || value > 100) return 1; /* %lld 写入 long long；读取失败或长度越界时返回 1。 */
    n = (int)value; /* 已确认长度可安全转换。 */
    for (int i = 0; i < n; ++i) { /* 逐项读取。 */
        if (scanf("%lld", &value) != 1 || value < -1000000000LL || value > 1000000000LL) return 1; /* 读取失败或元素越界时返回 1。 */
        a[i] = (int)value; /* 保存合法元素。 */
    }
    min_to_end(a, n); /* 调用自定义函数完成交换。 */
    for (int i = 0; i < n; ++i) { /* 依次输出各项。 */
        if (i != 0) printf(" "); /* 相邻元素之间输出一个空格。 */
        printf("%d", a[i]); /* 输出当前元素。 */
    }
    printf("\n"); /* 结束结果行。 */
    return 0; /* 正常结束。 */
}
