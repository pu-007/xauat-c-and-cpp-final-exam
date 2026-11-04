/* 35_union_enum 结构体、共用体与枚举 | ISO C++11 | 提高
 * 来源/关系：S1 第八单元；C++类型安全拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出一个整数型记录及一个实数型记录
 * 思想：共用体共享存储；用标签记住最后写入的成员；C++11用enum class标签与构造函数管理访问。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
enum class Kind { Integer, Real }; // 强类型枚举避免名字污染和隐式整型转换。
struct Value {
    Kind kind;
    union {
        int integer;
        double real;
    } data;
    explicit Value(int x) : kind(Kind::Integer) {
        data.integer = x;
    }
    explicit Value(double x) : kind(Kind::Real) {
        data.real = x;
    }
};
void print(const Value &value) {
    switch (value.kind) {
    case Kind::Integer:
        std::cout << value.data.integer << '\n';
        break;
    case Kind::Real:
        std::cout << value.data.real << '\n';
        break;
    }
}
int main() {
    Value a(7), b(2.5);
    print(a);
    print(b);
}
