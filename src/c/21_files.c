/* 21_files 文件写入、读回与返回值 | ISO C99 | 提高
 * 来源/关系：S1 p79–82 文件单元（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及n个绝对值<=10^6整数；写入程序私有临时流，再读回输出总和
 * 思想：不能用while(!feof)控制读操作；以fscanf成功数控制循环；检查ferror/fclose。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0 || n > 100)
        return 1;
    FILE *fp = tmpfile(); /* 自动清理临时文件，避免练习覆盖已有文件。 */
    if (!fp)
        return 1;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1 || x < -1000000 || x > 1000000 || fprintf(fp, "%d\n", x) < 0) {
            fclose(fp);
            return 1;
        }
    }
    if (fflush(fp) != 0 || fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return 1;
    }
    long long sum = 0;
    int x, status;
    while ((status = fscanf(fp, "%d", &x)) == 1)
        sum += x;
    int failed = ferror(fp) || status != EOF;
    if (fclose(fp) != 0)
        failed = 1;
    if (failed)
        return 1;
    printf("%lld\n", sum);
    return 0;
}
