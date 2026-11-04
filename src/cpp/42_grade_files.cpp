/* 42_grade_files 文本→二进制→排序→文本/二进制 | ISO C++11 | 提高
 * 来源/关系：S6实验2(5)、3(5)、4(5)、5(5)同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：标准输入10行：姓名(无空格<=19字节)及三科0..100整数；输出按总分降序的姓名、三科、总分；默认二进制使用私有临时流，四路径参数可生成持久文件
 * 思想：读、写、排序分函数；二进制逐字段写，避免struct填充；只保证相同实现往返。
 * 复杂度：O(n²)教学排序，n=10；二进制往返O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <algorithm>
#include <string>
struct Student {
    std::array<char, 20> name;
    std::array<int, 3> score;
};
int total(const Student &s) {
    return s.score[0] + s.score[1] + s.score[2];
}
bool read_text(std::istream &in, std::array<Student, 10> &a) {
    for (auto &s : a) {
        std::string name;
        if (!(in >> name) || name.size() > 19)
            return false;
        std::copy(name.begin(), name.end(), s.name.begin());
        for (int &x : s.score)
            if (!(in >> x) || x < 0 || x > 100)
                return false;
    }
    return true;
}
bool write_binary(std::ostream &out, const std::array<Student, 10> &a) {
    for (const auto &s : a) {
        out.write(s.name.data(), 20);
        out.write(reinterpret_cast<const char *>(s.score.data()), 3 * sizeof(int));
    }
    return static_cast<bool>(out);
}
bool read_binary(std::istream &in, std::array<Student, 10> &a) {
    for (auto &s : a) {
        in.read(s.name.data(), 20);
        in.read(reinterpret_cast<char *>(s.score.data()), 3 * sizeof(int));
    }
    return static_cast<bool>(in);
}
void print(std::ostream &out, const std::array<Student, 10> &a) {
    for (const auto &s : a)
        out << s.name.data() << ' ' << s.score[0] << ' ' << s.score[1] << ' ' << s.score[2] << ' '
            << total(s) << '\n';
}
int main(int argc, char **argv) {
    if (argc != 1 && argc != 5)
        return 1;
    if (argc == 5)
        for (int i = 1; i < 5; ++i)
            for (int j = i + 1; j < 5; ++j)
                if (std::string(argv[i]) == argv[j])
                    return 1;
    std::array<Student, 10> input{}, output{};
    std::ifstream source;
    if (argc == 5) {
        source.open(argv[1]);
        if (!source || !read_text(source, input))
            return 1;
    } else if (!read_text(std::cin, input))
        return 1;
    if (argc == 5) {
        std::ofstream raw(argv[3], std::ios::binary);
        if (!raw || !write_binary(raw, input))
            return 1;
        raw.close();
        if (!raw)
            return 1;
        std::ifstream saved(argv[3], std::ios::binary);
        if (!saved || !read_binary(saved, output))
            return 1;
    } else {
        std::stringstream raw(std::ios::in | std::ios::out | std::ios::binary);
        if (!write_binary(raw, input))
            return 1;
        raw.seekg(0);
        if (!read_binary(raw, output))
            return 1;
    }
    std::stable_sort(output.begin(), output.end(),
                     [](const Student &a, const Student &b) { return total(a) > total(b); });
    if (argc == 5) {
        std::ofstream sorted(argv[4], std::ios::binary);
        if (!sorted || !write_binary(sorted, output))
            return 1;
        sorted.close();
        if (!sorted)
            return 1;
        std::ofstream text(argv[2]);
        if (!text)
            return 1;
        print(text, output);
        text.close();
        if (!text)
            return 1;
    } else {
        std::ostringstream sorted(std::ios::out | std::ios::binary);
        if (!write_binary(sorted, output))
            return 1;
    }
    print(std::cout, output);
    return std::cout ? 0 : 1;
}
