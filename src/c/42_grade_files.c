/* 42_grade_files 文本→二进制→排序→文本/二进制 | ISO C99 | 提高
 * 来源/关系：S6实验2(5)、3(5)、4(5)、5(5)同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：标准输入10行：姓名(无空格<=19字节)及三科0..100整数；输出按总分降序的姓名、三科、总分；默认二进制使用私有临时流，四路径参数可生成持久文件
 * 思想：读、写、排序分函数；二进制逐字段写，避免struct填充；只保证相同实现往返。
 * 复杂度：O(n²)教学排序，n=10；二进制往返O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <string.h>
struct Student {
    char name[20];
    int score[3];
};
static int total(const struct Student *s) {
    return s->score[0] + s->score[1] + s->score[2];
}
static int read_text(struct Student a[10]) {
    for (int i = 0; i < 10; ++i) {
        if (scanf("%19s%d%d%d", a[i].name, &a[i].score[0], &a[i].score[1], &a[i].score[2]) != 4)
            return 0;
        for (int j = 0; j < 3; ++j)
            if (a[i].score[j] < 0 || a[i].score[j] > 100)
                return 0;
    }
    return 1;
}
static int write_binary(FILE *fp, const struct Student a[10]) {
    for (int i = 0; i < 10; ++i)
        if (fwrite(a[i].name, 1, 20, fp) != 20 || fwrite(a[i].score, sizeof(int), 3, fp) != 3)
            return 0;
    return fflush(fp) == 0;
}
static int read_binary(FILE *fp, struct Student a[10]) {
    if (fseek(fp, 0, SEEK_SET) != 0)
        return 0;
    for (int i = 0; i < 10; ++i)
        if (fread(a[i].name, 1, 20, fp) != 20 || fread(a[i].score, sizeof(int), 3, fp) != 3)
            return 0;
    return 1;
}
static void sort(struct Student a[10]) {
    for (int end = 9; end > 0; --end)
        for (int j = 0; j < end; ++j)
            if (total(&a[j]) < total(&a[j + 1])) {
                struct Student temporary = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temporary;
            }
}
static void print(FILE *out, const struct Student a[10]) {
    for (int i = 0; i < 10; ++i)
        fprintf(out, "%s %d %d %d %d\n", a[i].name, a[i].score[0], a[i].score[1], a[i].score[2],
                total(&a[i]));
}
/* 可选参数：输入文本 输出文本 原序二进制 排序二进制。
 * 输出路径应与输入路径不同；使用仓库build/labs下的练习文件。
 */
int main(int argc, char **argv) {
    if (argc != 1 && argc != 5)
        return 1;
    if (argc == 5) {
        for (int i = 1; i < 5; ++i)
            for (int j = i + 1; j < 5; ++j)
                if (strcmp(argv[i], argv[j]) == 0)
                    return 1;
        if (!freopen(argv[1], "r", stdin))
            return 1;
    }
    struct Student input[10] = {0}, output[10] = {0};
    if (!read_text(input))
        return 1;
    FILE *raw = argc == 5 ? fopen(argv[3], "w+b") : tmpfile();
    if (!raw)
        return 1;
    if (!write_binary(raw, input) || !read_binary(raw, output)) {
        fclose(raw);
        return 1;
    }
    if (fclose(raw) != 0)
        return 1;
    sort(output);
    FILE *sorted = argc == 5 ? fopen(argv[4], "wb") : tmpfile();
    if (!sorted)
        return 1;
    int success = write_binary(sorted, output);
    if (fclose(sorted) != 0)
        success = 0;
    if (!success)
        return 1;
    if (argc == 5) {
        FILE *text = fopen(argv[2], "w");
        if (!text)
            return 1;
        print(text, output);
        int error = ferror(text);
        if (fclose(text) != 0)
            error = 1;
        if (error)
            return 1;
    }
    print(stdout, output);
    return ferror(stdout) ? 1 : 0;
}
