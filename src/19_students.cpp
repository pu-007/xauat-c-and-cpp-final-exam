/* 19_students 结构体数组与成绩统计 | ISO C++11 | 提高
 * 来源/关系：S5 p6 例9.4、p9 习题5；S1 p77 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100；每行学号、无空格姓名(<=19字节)、三科0..100成绩；输出三科均分、最高均分学生、按均分降序的学号
 * 思想：记录把相关字段绑定；交换整个结构体；并列最高取输入中第一人。
 * 复杂度：C排序O(n²)；C++ stable_sort有足够缓冲时O(n log n)，不足时比较次数可更高。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：19_students.c用scanf/printf、字符数组和冒泡；本文件用cin/cout、string、vector与stable_sort。
 */
#include <iostream> /* cin和cout对应C的标准输入输出。 */
#include <iomanip> /* fixed与setprecision控制小数格式。 */
#include <vector> /* 按人数保存学生记录。 */
#include <array> /* 固定长度的成绩与科目总分。 */
#include <string> /* 管理姓名字符串。 */
#include <algorithm> /* stable_sort稳定排序。 */
struct Student { /* 一条记录整体参与排序。 */
    int id; /* 学号。 */
    std::string name; /* 可增长的姓名字符串。 */
    std::array<double, 3> score; /* 三科分数。 */
    double average; /* 未舍入的个人均分。 */
};
int main() {
    int n; /* 学生数。 */
    if (!(std::cin >> n) || n < 1 || n > 100) /* 验证读取与范围。 */
        return 1; /* 数量读取失败或越界。 */
    std::vector<Student> a(n); /* 按实际人数创建记录。 */
    std::array<double, 3> sums{}; /* 值初始化为三个零。 */
    for (auto &s : a) { /* 引用使写入直接修改容器元素。 */
        if (!(std::cin >> s.id >> s.name) || s.name.size() > 19) /* 限制姓名字节数。 */
            return 1; /* 字段缺失或姓名超过约定长度。 */
        double total = 0; /* 当前学生总分。 */
        for (int j = 0; j < 3; ++j) { /* 逐科读入并统计。 */
            if (!(std::cin >> s.score[j]) || !(s.score[j] >= 0 && s.score[j] <= 100))
                return 1; /* 读取失败或分数不合法。 */
            sums[j] += s.score[j]; /* 累计本科总分。 */
            total += s.score[j]; /* 累计个人总分。 */
        }
        s.average = total / 3; /* 保存排序键。 */
    }
    std::stable_sort(a.begin(), a.end(), /* 稳定排序使并列者保留输入顺序。 */
                     [](const Student &x, const Student &y) { return x.average > y.average; });
    std::cout << std::fixed << std::setprecision(2) << sums[0] / n << ' ' << sums[1] / n << ' '
              << sums[2] / n << '\n'; /* 固定小数两位输出科目均分。 */
    std::cout << a[0].id << ' ' << a[0].name << ' ' << a[0].average << '\n'; /* 最高者。 */
    for (int i = 0; i < n; ++i) /* 遍历排序后的学号。 */
        std::cout << (i ? " " : "") << a[i].id; /* 仅在非首项前加空格。 */
    std::cout << '\n'; /* 结束学号行；main隐式返回0。 */
}
