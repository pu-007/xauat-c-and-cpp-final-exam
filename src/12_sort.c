/* 12_sort 冒泡、选择、插入三种排序 | ISO C99 | 提高
 * 来源/关系：S5 p2/p4/p6；S2 填空8；S1 p89 附加49（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100，再输入n个int；三行分别输出三种升序排序结果
 * 思想：冒泡固定后缀，选择固定前缀，插入维护已排序前缀。
 * 复杂度：最坏O(n²)，单个排序额外空间O(1)
 * 对照 12_sort.cpp：C 显式复制数组，C++ vector 复制内容并使用标准算法找最小值。
 * 练习：比较相等元素是否交换，解释冒泡/插入的稳定性及选择排序的不稳定性。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 输入输出函数；C++ 对应 iostream。 */
static void swap(int *a, int *b) {
    /* 通过地址交换调用者数组中的两个元素。 */
    int t = *a; /* 保存第一个元素。 */
    *a = *b; /* 第二个值放入第一个位置。 */
    *b = t; /* 暂存值放入第二个位置。 */
}
static void bubble(int a[], int n) {
    /* 每轮将未排序部分最大值送到 end，随后缩短范围。 */
    for (int end = n - 1; end > 0; --end) { /* 已排序后缀从 end+1 开始。 */
        int changed = 0; /* 每轮重新清零。 */
        /* changed 记录本轮是否存在逆序的相邻元素。 */
        for (int j = 0; j < end; ++j) /* 比较到 end，不进入已排序后缀。 */
            if (a[j] > a[j + 1]) { /* 相等不交换，保留相对次序。 */
                swap(&a[j], &a[j + 1]); /* 较大值右移。 */
                changed = 1; /* 本轮发生了交换。 */
            }
        if (!changed)
            break; /* 一轮未交换说明已经有序。 */
    }
}
static void selection(int a[], int n) {
    /* 在后缀中找首次出现的最小值，与前缀下一位置交换。 */
    for (int i = 0; i < n; ++i) { /* i 左边已经排好。 */
        int best = i; /* 当前后缀的最小值候选。 */
        for (int j = i + 1; j < n; ++j) /* 扫描剩余后缀。 */
            if (a[j] < a[best]) /* 相等时保留先出现的位置。 */
                best = j; /* 更新候选下标。 */
        swap(&a[i], &a[best]); /* 固定当前位置。 */
    }
}
static void insertion(int a[], int n) {
    /* 左侧已排序；暂存 key，逐个右移大于 key 的元素。 */
    for (int i = 1; i < n; ++i) { /* 逐个扩展有序前缀。 */
        int key = a[i], j = i; /* 暂存当前值和空位。 */
        while (j > 0 && a[j - 1] > key) { /* 防止访问 -1，且相等值不移动。 */
            a[j] = a[j - 1]; /* 较大值右移。 */
            --j; /* 空位向左移动。 */
        }
        a[j] = key; /* 写入最终空位。 */
    }
}
static void print(const int a[], int n) {
    /* 即使 n=0 也输出一行。 */
    for (int i = 0; i < n; ++i) /* 遍历有效元素。 */
        printf("%s%d", i ? " " : "", a[i]); /* 首项不加空格。 */
    putchar('\n'); /* 结束本行。 */
}
int main(void) {
    /* 检查长度并逐项复制，使三种排序处理同一输入。 */
    int n, a[100], b[100], c[100]; /* 三份定长存储。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) /* 检查容量。 */
        return 1; /* 长度无效。 */
    for (int i = 0; i < n; ++i) { /* 每项输入一次。 */
        if (scanf("%d", &a[i]) != 1)
            return 1; /* 缺少元素。 */
        b[i] = c[i] = a[i]; /* 将相同数据复制给另外两种算法。 */
    }
    /* 分别排序和输出三份数组。 */
    bubble(a, n); /* 冒泡排序第一份。 */
    selection(b, n); /* 选择排序第二份。 */
    insertion(c, n); /* 插入排序第三份。 */
    print(a, n); /* 按算法顺序输出。 */
    print(b, n);
    print(c, n);
    return 0; /* 正常结束。 */
}
