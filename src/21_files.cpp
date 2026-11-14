/* 21_files 文件写入、读回与返回值 | ISO C++11 | 提高
 * 来源/关系：S1 p79–82 文件单元（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及n个绝对值<=10^6整数；写入程序私有临时流，再读回输出总和
 * 思想：不能用while(!feof)控制读操作；以fscanf成功数控制循环；检查ferror/fclose。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：21_files.c手动fclose；本文件用unique_ptr在提前返回时自动关闭，release后显式检查关闭。
 */
#include <cstdio> /* tmpfile及C文件流操作。 */
#include <memory> /* unique_ptr。 */
#include <iostream> /* 标准输入输出。 */
int main() {
    int n; /* 整数数量。 */
    if (!(std::cin >> n) || n < 0 || n > 100)
        return 1; /* 输入无效。 */
    auto close_file = [](std::FILE *file) { std::fclose(file); }; /* 提前退出时关闭资源。 */
    std::unique_ptr<std::FILE, decltype(close_file)> fp(std::tmpfile(), close_file); /* 托管私有流。 */
    if (!fp)
        return 1; /* 创建失败。 */
    for (int i = 0; i < n; ++i) { /* 依次读入并写入临时流。 */
        int x; /* 当前输入。 */
        if (!(std::cin >> x) || x < -1000000 || x > 1000000 ||
            std::fprintf(fp.get(), "%d\n", x) < 0)
            return 1; /* 输入或写入失败，由智能指针关闭。 */
    }
    if (std::fflush(fp.get()) != 0 || std::fseek(fp.get(), 0, SEEK_SET) != 0)
        return 1; /* 刷新并定位到文件头。 */
    int x, status; /* 待读数和读取状态。 */
    long long sum = 0; /* 空流的和为零。 */
    while ((status = std::fscanf(fp.get(), "%d", &x)) == 1)
        sum += x; /* 仅累加成功读取的整数。 */
    bool failed = std::ferror(fp.get()) || status != EOF; /* 判断读取是否正常结束。 */
    if (std::fclose(fp.release()) != 0) /* release先移交所有权，避免二次关闭。 */
        failed = true; /* 显式检查关闭失败。 */
    if (failed) /* 读或关闭出错则不输出总和。 */
        return 1; /* 报告失败。 */
    std::cout << sum << '\n'; /* 输出总和。 */
}
