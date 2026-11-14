/* 42_grade_files 文本→二进制→排序→文本/二进制 | ISO C99 | 提高
 * 来源/关系：S6实验2(5)、3(5)、4(5)、5(5)同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：标准输入10行：姓名(无空格<=19字节)及三科0..100整数；输出按总分降序的姓名、三科、总分；默认二进制使用私有临时流，四路径参数可生成持久文件
 * 思想：读、写、排序分函数；二进制逐字段写，避免struct填充；只保证相同实现往返。
 * 复杂度：O(n²)教学排序，n=10；二进制往返O(n)
 * 对照 42_grade_files.cpp：C 用 FILE 和冒泡排序，C++ 用流和 stable_sort。
 * fwrite/fread 对应 ostream::write/istream::read；tmpfile 对应 C++ 私有 stringstream。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* FILE 及文本、二进制读写函数。 */
#include <string.h> /* strcmp 比较路径字符串。 */
struct Student {
    char name[20]; /* 最多 19 字节姓名及终止零。 */
    int score[3]; /* 三科成绩以本机 int 保存。 */
};
/* 三科相加，作为稳定降序排序的比较键。 */
static int total(const struct Student *s) {
    return s->score[0] + s->score[1] + s->score[2]; /* 三科成绩之和。 */
}
/* 逐条读取文本，限制姓名宽度并检查三科范围；任一错误返回失败。 */
static int read_text(struct Student a[10]) {
    for (int i = 0; i < 10; ++i) { /* 恰好读取十名学生。 */
        if (scanf("%19s%d%d%d", a[i].name, &a[i].score[0], &a[i].score[1], &a[i].score[2]) != 4)
            return 0; /* 字段缺失或格式错误。 */
        for (int j = 0; j < 3; ++j) /* 验证每科成绩。 */
            if (a[i].score[j] < 0 || a[i].score[j] > 100)
                return 0;
    }
    return 1; /* 所有记录均有效。 */
}
/* 分字段写入固定长度姓名和三个本机 int；刷新可使随后读取看到数据。 */
static int write_binary(FILE *fp, const struct Student a[10]) {
    for (int i = 0; i < 10; ++i) /* 一条条写，检查写入数量。 */
        if (fwrite(a[i].name, 1, 20, fp) != 20 || fwrite(a[i].score, sizeof(int), 3, fp) != 3)
            return 0;
    return fflush(fp) == 0; /* 检查缓冲区刷新是否成功。 */
}
/* 将流定位到开头，按写入的字段顺序读回十条记录。 */
static int read_binary(FILE *fp, struct Student a[10]) {
    if (fseek(fp, 0, SEEK_SET) != 0) /* 从原序流开头读取。 */
        return 0;
    for (int i = 0; i < 10; ++i)
        if (fread(a[i].name, 1, 20, fp) != 20 || fread(a[i].score, sizeof(int), 3, fp) != 3)
            return 0; /* 任何字段短读均失败。 */
    return 1;
}
/* 冒泡排序仅在前者总分更小时交换，因此相同总分保留输入顺序。 */
static void sort(struct Student a[10]) {
    for (int end = 9; end > 0; --end) /* 每轮固定未排序区间末尾。 */
        for (int j = 0; j < end; ++j)
            if (total(&a[j]) < total(&a[j + 1])) { /* 较大总分向前移动。 */
                struct Student temporary = a[j]; /* 暂存前项。 */
                a[j] = a[j + 1];
                a[j + 1] = temporary; /* 完成整条记录的交换。 */
            }
}
/* 输出每条记录及其计算出的总分，调用者检查流错误。 */
static void print(FILE *out, const struct Student a[10]) {
    for (int i = 0; i < 10; ++i) /* 按当前数组顺序输出。 */
        fprintf(out, "%s %d %d %d %d\n", a[i].name, a[i].score[0], a[i].score[1], a[i].score[2],
                total(&a[i])); /* 姓名、三科和计算出的总分。 */
}
/* 可选参数：输入文本 输出文本 原序二进制 排序二进制。
 * 输出路径应与输入路径不同；使用仓库build/labs下的练习文件。
 */
int main(int argc, char **argv) {
    /* 仅接受无参数和四路径两种模式；后者先检查路径字符串互不相同。 */
    if (argc != 1 && argc != 5) /* 程序名之外要么没有参数，要么恰有四个路径。 */
        return 1;
    if (argc == 5) {
        for (int i = 1; i < 5; ++i) /* 将每个路径与后面的路径逐一比较。 */
            for (int j = i + 1; j < 5; ++j)
                if (strcmp(argv[i], argv[j]) == 0)
                    return 1; /* 同名路径可能覆盖输入或其他结果。 */
        if (!freopen(argv[1], "r", stdin)) /* 让后续 scanf 从指定文本文件读取。 */
            return 1;
    }
    /* 清零记录保证姓名末尾有零；先从文本读入，再写入并读回原序二进制。 */
    struct Student input[10] = {0}, output[10] = {0}; /* 两组分别保存原始和回读记录。 */
    if (!read_text(input)) /* 输入不足或成绩非法时不创建输出流。 */
        return 1;
    FILE *raw = argc == 5 ? fopen(argv[3], "w+b") : tmpfile(); /* 持久文件或自动清理的临时文件。 */
    if (!raw)
        return 1; /* 打开失败，无流需要关闭。 */
    if (!write_binary(raw, input) || !read_binary(raw, output)) { /* 写入、定位并回读。 */
        fclose(raw); /* 失败路径也释放原序流。 */
        return 1;
    }
    if (fclose(raw) != 0) /* 关闭可能暴露延迟的文件错误。 */
        return 1;
    /* 回读后稳定排序，再将排序结果写入另一个二进制流。 */
    sort(output); /* 只重新排列回读数组。 */
    FILE *sorted = argc == 5 ? fopen(argv[4], "wb") : tmpfile(); /* 排序后的持久文件或临时流。 */
    if (!sorted)
        return 1;
    int success = write_binary(sorted, output); /* 记录写入及刷新是否成功。 */
    if (fclose(sorted) != 0) /* 即使写入失败也必须关闭。 */
        success = 0; /* 关闭失败同样视为失败。 */
    if (!success)
        return 1;
    /* 四路径模式还写出文本文件；最后两种模式均向标准输出显示。 */
    if (argc == 5) {
        FILE *text = fopen(argv[2], "w"); /* 创建或截断指定输出文本。 */
        if (!text)
            return 1;
        print(text, output); /* 逐条写排序结果。 */
        int error = ferror(text); /* 保存写入错误状态。 */
        if (fclose(text) != 0) /* 关闭并检查缓冲写入。 */
            error = 1;
        if (error)
            return 1;
    }
    print(stdout, output); /* 两种模式都向标准输出显示。 */
    return ferror(stdout) ? 1 : 0; /* 向调用者报告标准输出错误。 */
}
