/* 21_files 文件写入、读回与返回值 | ISO C99 | 提高
 * 来源/关系：S1 p79–82 文件单元（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及n个绝对值<=10^6整数；写入程序私有临时流，再读回输出总和
 * 思想：不能用while(!feof)控制读操作；以fscanf成功数控制循环；检查ferror/fclose。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：21_files.cpp用unique_ptr托管同样的FILE和fclose；C在各退出路径显式fclose。
 */
#include <stdio.h> /* 标准输入输出和临时文件操作。 */
int main(void) {
    int n; /* 待写入整数个数。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 100)
        return 1; /* 数量读取失败或超出约定范围。 */
    FILE *fp = tmpfile(); /* 创建私有临时流，关闭后自动移除。 */
    if (!fp)
        return 1; /* 系统无法创建临时流。 */
    for (int i = 0; i < n; ++i) { /* 按输入顺序写入n个整数。 */
        int x; /* 当前待写整数。 */
        if (scanf("%d", &x) != 1 || x < -1000000 || x > 1000000 || fprintf(fp, "%d\n", x) < 0) {
            fclose(fp); /* 输入或写入失败时释放文件。 */
            return 1;
        }
    }
    if (fflush(fp) != 0 || fseek(fp, 0, SEEK_SET) != 0) { /* 刷新写入并回到文件头。 */
        fclose(fp); /* 定位或刷新失败也需关闭。 */
        return 1; /* 报告文件操作失败。 */
    }
    long long sum = 0; /* 累积和使用宽整数。 */
    int x, status; /* 当前读到的值及转换结果。 */
    while ((status = fscanf(fp, "%d", &x)) == 1) /* 成功读到一个数才累加。 */
        sum += x;
    int failed = ferror(fp) || status != EOF; /* 区分正常末尾与读取错误。 */
    if (fclose(fp) != 0) /* 关闭错误也必须报告。 */
        failed = 1; /* 记录关闭失败。 */
    if (failed) /* 读取或关闭异常时不输出结果。 */
        return 1; /* 报告失败。 */
    printf("%lld\n", sum); /* 空文件的和为零。 */
    return 0; /* 正常结束。 */
}
