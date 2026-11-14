/* 35_union_enum 结构体、共用体与枚举 | ISO C++11 | 提高
 * 来源/关系：S1 第八单元；C++类型安全拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出一个整数型记录及一个实数型记录
 * 思想：共用体共享存储；用标签记住最后写入的成员；C++11用enum class标签与构造函数管理访问。
 * 复杂度：O(1)
 * 对照 35_union_enum.c：C 用普通枚举和指定初始化，C++ 用强类型枚举和构造函数。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cout；C 对照使用 printf。
enum class Kind { Integer, Real }; // 强类型枚举避免名字污染和隐式整型转换。
struct Value {
    Kind kind; // 记录当前使用的共用体成员。
    union { // 两个成员共享存储。
        int integer; // 整数值。
        double real; // 实数值。
    } data;
    explicit Value(int x) : kind(Kind::Integer) { // 整数构造设置对应标签。
        data.integer = x; // 写入整数成员。
    }
    explicit Value(double x) : kind(Kind::Real) { // 实数构造设置对应标签。
        data.real = x; // 写入实数成员。
    }
};
void print(const Value &value) { // 只读引用避免复制记录。
    switch (value.kind) { // 根据标签选择合法成员。
    case Kind::Integer:
        std::cout << value.data.integer << '\n'; // 输出整数。
        break;
    case Kind::Real:
        std::cout << value.data.real << '\n'; // 输出实数。
        break;
    }
}
int main() {
    Value a(7), b(2.5); // 分别调用整数和实数构造函数。
    print(a); // 输出第一条记录。
    print(b); // 输出第二条记录。
}
