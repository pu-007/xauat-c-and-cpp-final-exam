/* 21_files 文件写入、读回与返回值 | ISO C++11 | 提高
 * 来源/关系：S1 p79–82 文件单元（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及n个绝对值<=10^6整数；写入程序私有临时流，再读回输出总和
 * 思想：不能用while(!feof)控制读操作；以fscanf成功数控制循环；检查ferror/fclose。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <cstdio>
#include <memory>
#include <iostream>
int main() {
    int n;
    if (!(std::cin >> n) || n < 0 || n > 100)
        return 1;
    // 自定义删除器让C资源也能使用RAII；普通文件流见docs中的fstream示例。
    auto close_file = [](std::FILE *file) { std::fclose(file); };
    std::unique_ptr<std::FILE, decltype(close_file)> fp(std::tmpfile(), close_file);
    if (!fp)
        return 1;
    for (int i = 0; i < n; ++i) {
        int x;
        if (!(std::cin >> x) || x < -1000000 || x > 1000000 ||
            std::fprintf(fp.get(), "%d\n", x) < 0)
            return 1;
    }
    if (std::fflush(fp.get()) != 0 || std::fseek(fp.get(), 0, SEEK_SET) != 0)
        return 1;
    int x, status;
    long long sum = 0;
    while ((status = std::fscanf(fp.get(), "%d", &x)) == 1)
        sum += x;
    bool failed = std::ferror(fp.get()) || status != EOF;
    if (std::fclose(fp.release()) != 0)
        failed = true; // 显式close可检查失败，release防止二次关闭。
    if (failed)
        return 1;
    std::cout << sum << '\n';
}
