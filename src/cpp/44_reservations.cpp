/* 44_reservations 订餐信息管理：插入查询修改删除显示 | ISO C++11 | 综合
 * 来源/关系：S6实验6 p47–51；链表C版与vector C++11版（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：菜单1 id name people HH:MM插入；2 id查询；3 id people HH:MM修改；4
 * id删除；5显示；6退出。编号正且唯一，姓名无空格<=31字节，人数1..1000
 * 思想：分离查找、验证、修改和释放；修改失败不破坏已有记录；维护唯一编号。
 * 复杂度：每条增删查改O(n)，空间O(n)
 * 练习：增设姓名修改、按时间排序、文件保存；先写数据格式再扩展菜单。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
struct Reservation {
    int id, people;
    std::string name, time;
};
bool valid_time(const std::string &s) {
    if (s.size() != 5 || s[2] != ':')
        return false;
    for (std::size_t i = 0; i < s.size(); ++i)
        if (i != 2 && (s[i] < '0' || s[i] > '9'))
            return false;
    return (s[0] - '0') * 10 + s[1] - '0' < 24 && (s[3] - '0') * 10 + s[4] - '0' < 60;
}
void print(const Reservation &r) {
    std::cout << r.id << ' ' << r.name << ' ' << r.people << ' ' << r.time << '\n';
}
int main() {
    std::vector<Reservation> data;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.size() > 254) {
            std::cout << "INVALID\n";
            continue;
        }
        std::istringstream input(line);
        int op, id, people;
        std::string name, time, extra;
        if (!(input >> op)) {
            std::cout << "INVALID\n";
            continue;
        }
        if (op == 1) {
            if (!(input >> id >> name >> people >> time) || input >> extra || id < 1 ||
                name.size() > 31 || people < 1 || people > 1000 || !valid_time(time)) {
                std::cout << "INVALID\n";
                continue;
            }
            auto it = std::find_if(data.begin(), data.end(),
                                   [id](const Reservation &r) { return r.id == id; });
            if (it != data.end())
                std::cout << "DUPLICATE\n";
            else {
                data.push_back(Reservation{id, people, name, time});
                std::cout << "OK\n";
            }
        } else if (op == 2 || op == 4) {
            if (!(input >> id) || input >> extra || id < 1) {
                std::cout << "INVALID\n";
                continue;
            }
            auto it = std::find_if(data.begin(), data.end(),
                                   [id](const Reservation &r) { return r.id == id; });
            if (it == data.end())
                std::cout << "NOT_FOUND\n";
            else if (op == 2)
                print(*it);
            else {
                data.erase(it);
                std::cout << "OK\n";
            }
        } else if (op == 3) {
            if (!(input >> id >> people >> time) || input >> extra || id < 1 || people < 1 ||
                people > 1000 || !valid_time(time)) {
                std::cout << "INVALID\n";
                continue;
            }
            auto it = std::find_if(data.begin(), data.end(),
                                   [id](const Reservation &r) { return r.id == id; });
            if (it == data.end())
                std::cout << "NOT_FOUND\n";
            else {
                it->people = people;
                it->time = time;
                std::cout << "OK\n";
            }
        } else if (op == 5 || op == 6) {
            if (input >> extra) {
                std::cout << "INVALID\n";
                continue;
            }
            if (op == 6)
                break;
            if (data.empty())
                std::cout << "EMPTY\n";
            else
                for (const auto &r : data)
                    print(r);
        } else
            std::cout << "INVALID\n";
    }
} // vector及string自动销毁，新增记录后不要保留可能失效的迭代器。
