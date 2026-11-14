/* 19_students 结构体数组与成绩统计 | ISO C99 | 提高
 * 来源/关系：S5 p6 例9.4、p9 习题5；S1 p77 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100；每行学号、无空格姓名(<=19字节)、三科0..100成绩；输出三科均分、最高均分学生、按均分降序的学号
 * 思想：记录把相关字段绑定；交换整个结构体；并列最高取输入中第一人。
 * 复杂度：C排序O(n²)；C++ stable_sort有足够缓冲时O(n log n)，不足时比较次数可更高。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：19_students.cpp用cin/cout和string、vector、stable_sort；C用scanf/printf、定长字符数组及稳定冒泡。
 */
#include <stdio.h> /* scanf、printf和putchar。 */
struct Student { /* 将一个人的所有数据作为整体交换。 */
    int id; /* 学号。 */
    char name[20]; /* 最多19字节及结尾的空字符。 */
    double score[3], average; /* 三门分数及个人均分。 */
};
int main(void) {
    int n; /* 实际学生数。 */
    struct Student a[100]; /* 最多保存100条记录。 */
    double sums[3] = {0}; /* 分别累计各科总分。 */
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) /* 拒绝无效人数。 */
        return 1; /* 输入或人数不合法，返回失败状态。 */
    for (int i = 0; i < n; ++i) { /* 逐条读取记录。 */
        if (scanf("%d%19s%lf%lf%lf", &a[i].id, a[i].name, &a[i].score[0], &a[i].score[1],
                  &a[i].score[2]) != 5) /* 限制姓名写入长度并检查字段数。 */
            return 1; /* 缺少字段或字段格式有误。 */
        double total = 0; /* 当前学生三科总分。 */
        for (int j = 0; j < 3; ++j) { /* 检查并累加三个科目。 */
            if (!(a[i].score[j] >= 0 && a[i].score[j] <= 100)) /* 排除越界及NaN。 */
                return 1; /* 分数不在约定范围内。 */
            sums[j] += a[i].score[j]; /* 累加对应科目。 */
            total += a[i].score[j]; /* 累加当前学生成绩。 */
        }
        a[i].average = total / 3; /* 为排序保留未四舍五入的均分。 */
    }
    for (int end = n - 1; end > 0; --end) /* 每轮把最小均分移到未排序区末端。 */
        for (int j = 0; j < end; ++j) /* 比较未排序区相邻记录。 */
            if (a[j].average < a[j + 1].average) { /* 相等不交换，保留输入顺序。 */
                struct Student temp = a[j]; /* 整体复制包含字符数组的结构体。 */
                a[j] = a[j + 1]; /* 较大均分记录移至前位。 */
                a[j + 1] = temp; /* 原前位记录移至后位。 */
            }
    printf("%.2f %.2f %.2f\n", sums[0] / n, sums[1] / n, sums[2] / n); /* 科目均分。 */
    printf("%d %s %.2f\n", a[0].id, a[0].name, a[0].average); /* 排序首位为最高者。 */
    for (int i = 0; i < n; ++i) /* 按排序结果输出所有学号。 */
        printf("%s%d", i ? " " : "", a[i].id); /* 首项前不输出空格。 */
    putchar('\n'); /* 结束学号行。 */
    return 0; /* 正常结束。 */
}
/* 两种实现均按原始均分比较，显示时才保留两位小数。 */
