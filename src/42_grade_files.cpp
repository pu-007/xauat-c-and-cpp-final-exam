/* 42_grade_files 文本→二进制→排序→文本/二进制 | ISO C++11 | 提高
 * 来源/关系：S6实验2(5)、3(5)、4(5)、5(5)同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：标准输入10行：姓名(无空格<=19字节)及三科0..100整数；输出按总分降序的姓名、三科、总分；默认二进制使用私有临时流，四路径参数可生成持久文件
 * 思想：读、写、排序分函数；二进制逐字段写，避免struct填充；只保证相同实现往返。
 * 复杂度：读写 O(n)；stable_sort 复杂度取决于可用内存；空间 O(n)。
 * 对照 42_grade_files.c：C 用 FILE 和冒泡排序，C++ 用流和 stable_sort。
 * ostream::write/istream::read 对应 C 的 fwrite/fread；私有 stringstream 对应 C 临时流。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 标准输入输出流。
#include <sstream> // 私有内存输入输出流。
#include <fstream> // 持久文件输入输出流。
#include <array> // 固定长度记录和字段。
#include <algorithm> // copy 和 stable_sort。
#include <string> // 姓名及路径比较。
struct Student {
    std::array<char, 20> name; // 固定宽度姓名，含终止零。
    std::array<int, 3> score; // 三科本机整数成绩。
};
// 以三科总分作为排序键；同分由 stable_sort 保持原顺序。
int total(const Student &s) {
    return s.score[0] + s.score[1] + s.score[2]; // 计算该生总分。
}
// 文本姓名先读入 string 检查长度，复制到已经零初始化的固定字段。
bool read_text(std::istream &in, std::array<Student, 10> &a) {
    for (auto &s : a) { // 依次填入十条记录。
        std::string name; // 暂存完整姓名，以便检查长度。
        if (!(in >> name) || name.size() > 19)
            return false;
        std::copy(name.begin(), name.end(), s.name.begin()); // 余下零字节作为终止符。
        for (int &x : s.score) // 直接读取每一科成绩。
            if (!(in >> x) || x < 0 || x > 100)
                return false;
    }
    return true; // 十条记录均合法。
}
// 按姓名字段和本机 int 数组写入，避免直接写结构体填充字节。
bool write_binary(std::ostream &out, const std::array<Student, 10> &a) {
    for (const auto &s : a) { // 不修改原记录。
        out.write(s.name.data(), 20); // 写固定宽度姓名。
        out.write(reinterpret_cast<const char *>(s.score.data()), 3 * sizeof(int)); // 按字节写本机整数。
    }
    return static_cast<bool>(out); // 检查流状态。
}
// 按写入顺序读回字段；流状态报告短读或其他错误。
bool read_binary(std::istream &in, std::array<Student, 10> &a) {
    for (auto &s : a) {
        in.read(s.name.data(), 20); // 先读姓名。
        in.read(reinterpret_cast<char *>(s.score.data()), 3 * sizeof(int)); // 再读三科整数。
    }
    return static_cast<bool>(in); // 任一短读导致失败。
}
// 用同一输出函数写文本文件或标准输出，附带计算出的总分。
void print(std::ostream &out, const std::array<Student, 10> &a) {
    for (const auto &s : a) // 按当前排序顺序读取，不复制记录。
        out << s.name.data() << ' ' << s.score[0] << ' ' << s.score[1] << ' ' << s.score[2] << ' '
            << total(s) << '\n'; // 输出姓名、三科和总分。
}
int main(int argc, char **argv) {
    // 四路径模式拒绝相同路径字符串，实际路径也须避免指向同一文件。
    if (argc != 1 && argc != 5) // 参数数目必须对应两种模式之一。
        return 1;
    if (argc == 5)
        for (int i = 1; i < 5; ++i) // 两两比较路径字符串。
            for (int j = i + 1; j < 5; ++j)
                if (std::string(argv[i]) == argv[j])
                    return 1; // 防止明显的同名覆盖。
    // 值初始化使姓名余下字节为零，保证复制后存在字符串终止符。
    std::array<Student, 10> input{}, output{}; // 分别保存输入和二进制回读记录。
    std::ifstream source; // 持久输入流，离开作用域时自动关闭。
    if (argc == 5) {
        source.open(argv[1]); // 从指定文本文件读取。
        if (!source || !read_text(source, input))
            return 1; // 打开或解析失败。
    } else if (!read_text(std::cin, input)) // 无参数时使用标准输入。
        return 1;
    // 原序二进制在文件模式写盘并重读；无参数模式通过内存流往返。
    if (argc == 5) {
        std::ofstream raw(argv[3], std::ios::binary); // 创建原序二进制文件。
        if (!raw || !write_binary(raw, input))
            return 1; // 局部流析构时自动关闭。
        raw.close(); // 先关闭写流，再打开读流。
        if (!raw)
            return 1; // 检查关闭时的错误。
        std::ifstream saved(argv[3], std::ios::binary); // 从文件开头重读。
        if (!saved || !read_binary(saved, output))
            return 1; // 读流在离开分支时自动关闭。
    } else {
        std::stringstream raw(std::ios::in | std::ios::out | std::ios::binary); // 私有内存流。
        if (!write_binary(raw, input))
            return 1;
        raw.seekg(0); // 把读取位置移回开头。
        if (!read_binary(raw, output))
            return 1; // 回读失败时离开并销毁内存流。
    }
    // 按总分降序稳定排序，后续输出排序后的二进制和文本。
    std::stable_sort(output.begin(), output.end(), // 用比较器按总分排序整个数组。
                     [](const Student &a, const Student &b) { return total(a) > total(b); }); // 同分保留输入次序。
    if (argc == 5) {
        std::ofstream sorted(argv[4], std::ios::binary); // 创建排序二进制文件。
        if (!sorted || !write_binary(sorted, output))
            return 1;
        sorted.close(); // 显式关闭以检查最终写入。
        if (!sorted)
            return 1;
        std::ofstream text(argv[2]); // 创建排序文本文件。
        if (!text)
            return 1;
        print(text, output); // 写入每条记录和总分。
        text.close(); // 刷新并关闭文件。
        if (!text)
            return 1; // 检查写入和关闭状态。
    } else {
        std::ostringstream sorted(std::ios::out | std::ios::binary); // 无参数模式的私有排序流。
        if (!write_binary(sorted, output))
            return 1;
    }
    print(std::cout, output); // 两种模式均显示文本结果。
    return std::cout ? 0 : 1; // 输出流出错时返回失败。
}
