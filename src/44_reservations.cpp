/* 44_reservations 订餐信息管理：插入查询修改删除显示 | ISO C++11 | 综合
 * 来源/关系：S6实验6 p47–51；链表C版与vector C++11版（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：菜单1 id name people HH:MM插入；2 id查询；3 id people HH:MM修改；4
 * id删除；5显示；6退出。编号正且唯一，姓名无空格<=31字节，人数1..1000
 * 思想：分离查找、验证、修改和释放；修改失败不破坏已有记录；维护唯一编号。
 * 复杂度：每条增删查改O(n)，空间O(n)
 * 对照 44_reservations.c：C 用链表并手动释放结点，C++ 用 vector 自动管理记录。
 * getline/istringstream 对应 C 的 fgets/sscanf；find_if 对应链表查找，容器析构对应 free。
 * 练习：增设姓名修改、按时间排序、文件保存；先写数据格式再扩展菜单。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 标准输入输出流。
#include <sstream> // 按行解析命令。
#include <vector> // 保存预约记录。
#include <string> // 保存命令、姓名和时间。
#include <algorithm> // find_if 按编号查找。
struct Reservation {
    int id, people; // 记录编号和人数。
    std::string name, time; // 姓名和 HH:MM 时间由 string 管理。
};
// 先检查长度和冒号，再确认四个数字及小时、分钟范围。
bool valid_time(const std::string &s) {
    if (s.size() != 5 || s[2] != ':') // 先验证长度再访问位置 2。
        return false;
    for (std::size_t i = 0; i < s.size(); ++i) // 逐字节检查数字位。
        if (i != 2 && (s[i] < '0' || s[i] > '9'))
            return false;
    return (s[0] - '0') * 10 + s[1] - '0' < 24 && (s[3] - '0') * 10 + s[4] - '0' < 60; // 检查时、分上界。
}
// 以引用读取一条记录，按统一格式输出。
void print(const Reservation &r) {
    std::cout << r.id << ' ' << r.name << ' ' << r.people << ' ' << r.time << '\n';
}
int main() {
    // vector 按插入顺序保存记录，string 保存一行完整命令。
    std::vector<Reservation> data; // 保存当前记录，初始为空。
    std::string line; // 当前输入行。
    while (std::getline(std::cin, line)) { // EOF 时退出循环。
        // 限制行长后用独立输入流解析，避免非法行影响下一条命令。
        if (line.size() > 254) {
            std::cout << "INVALID\n"; // 长行整体拒绝。
            continue;
        }
        std::istringstream input(line); // 当前行独立解析，作用域结束自动销毁。
        int op, id, people; // 操作编号及数字参数。
        std::string name, time, extra; // extra 用于检测多余字段。
        if (!(input >> op)) { // 没有可解析的操作号。
            std::cout << "INVALID\n";
            continue;
        }
        if (op == 1) {
            // 插入前验证全部字段，find_if 检查编号是否已经存在。
            if (!(input >> id >> name >> people >> time) || input >> extra || id < 1 ||
                name.size() > 31 || people < 1 || people > 1000 || !valid_time(time)) {
                std::cout << "INVALID\n"; // 字段数量、范围或时间不合法。
                continue; // 不修改已有记录。
            }
            auto it = std::find_if(data.begin(), data.end(), // 捕获编号，寻找首个相同编号。
                                   [id](const Reservation &r) { return r.id == id; });
            if (it != data.end())
                std::cout << "DUPLICATE\n"; // 编号已存在。
            else {
                data.push_back(Reservation{id, people, name, time}); // 追加新记录。
                std::cout << "OK\n";
            }
        } else if (op == 2 || op == 4) {
            // 查询或删除先检查参数，再用相同的编号查找。
            if (!(input >> id) || input >> extra || id < 1) { // 检查唯一正编号且无多余字段。
                std::cout << "INVALID\n";
                continue;
            }
            auto it = std::find_if(data.begin(), data.end(), // 查找对应记录。
                                   [id](const Reservation &r) { return r.id == id; });
            if (it == data.end())
                std::cout << "NOT_FOUND\n";
            else if (op == 2)
                print(*it); // 查询只读取记录。
            else {
                data.erase(it); // 删除该元素，后续元素前移。
                std::cout << "OK\n";
            }
        } else if (op == 3) {
            // 修改仅在全部字段合法且记录存在后执行。
            if (!(input >> id >> people >> time) || input >> extra || id < 1 || people < 1 ||
                people > 1000 || !valid_time(time)) {
                std::cout << "INVALID\n"; // 校验失败，原记录保持不变。
                continue;
            }
            auto it = std::find_if(data.begin(), data.end(), // 查找要修改的编号。
                                   [id](const Reservation &r) { return r.id == id; });
            if (it == data.end())
                std::cout << "NOT_FOUND\n";
            else {
                it->people = people; // 更新人数。
                it->time = time; // 更新有效时间。
                std::cout << "OK\n";
            }
        } else if (op == 5 || op == 6) {
            // 显示与退出不接受额外参数；显示顺序即 vector 顺序。
            if (input >> extra) { // 显示和退出均不能附加字段。
                std::cout << "INVALID\n";
                continue;
            }
            if (op == 6)
                break; // 离开循环后容器自动销毁。
            if (data.empty())
                std::cout << "EMPTY\n";
            else
                for (const auto &r : data) // 按当前保存顺序显示，不复制记录。
                    print(r);
        } else
            std::cout << "INVALID\n"; // 操作号不在菜单中。
    }
} // vector及string自动销毁，新增记录后不要保留可能失效的迭代器。
