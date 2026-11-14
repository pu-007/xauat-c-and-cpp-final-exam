/* 44_reservations 订餐信息管理：插入查询修改删除显示 | ISO C99 | 综合
 * 来源/关系：S6实验6 p47–51；链表C版与vector C++11版（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：菜单1 id name people HH:MM插入；2 id查询；3 id people HH:MM修改；4
 * id删除；5显示；6退出。编号正且唯一，姓名无空格<=31字节，人数1..1000
 * 思想：分离查找、验证、修改和释放；修改失败不破坏已有记录；维护唯一编号。
 * 复杂度：每条增删查改O(n)，空间O(n)
 * 对照 44_reservations.cpp：C 用链表并手动释放结点，C++ 用 vector 自动管理记录。
 * fgets/sscanf 对应 getline/istringstream；链表查找对应 find_if，free 对应容器自动析构。
 * 练习：增设姓名修改、按时间排序、文件保存；先写数据格式再扩展菜单。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 行输入、解析和结果输出。 */
#include <stdlib.h> /* malloc 和 free 管理结点。 */
#include <string.h> /* strlen 和 strcpy 处理字段。 */
struct Reservation {
    int id, people; /* 唯一编号及就餐人数。 */
    char name[32], time[6]; /* 姓名和 HH:MM 均预留结尾零。 */
    struct Reservation *next; /* 后继结点，尾结点为空。 */
};
/* 时间须恰为五字节：冒号在中间，数字组成合法小时和分钟。 */
static int valid_time(const char *s) {
    if (strlen(s) != 5 || s[2] != ':') /* 先确认长度，避免访问不足五字节的字符串。 */
        return 0;
    if (s[0] < '0' || s[0] > '9' || s[1] < '0' || s[1] > '9' || s[3] < '0' || s[3] > '9' ||
        s[4] < '0' || s[4] > '9')
        return 0; /* 数字位出现其他字符。 */
    return (s[0] - '0') * 10 + s[1] - '0' < 24 && (s[3] - '0') * 10 + s[4] - '0' < 60; /* 组合十位和个位并检查范围。 */
}
/* 沿链表查找编号；未找到时返回空指针。 */
static struct Reservation *find(struct Reservation *head, int id) {
    while (head && head->id != id) /* 未到末尾且编号不同就继续。 */
        head = head->next; /* 前进到下一条。 */
    return head; /* 返回匹配结点或空指针。 */
}
/* 输出一条记录，不改变链表。 */
static void print(const struct Reservation *r) {
    printf("%d %s %d %s\n", r->id, r->name, r->people, r->time);
}
/* 先保存后继再释放当前结点，直到整条链表释放完毕。 */
static void destroy(struct Reservation *head) {
    while (head) {
        struct Reservation *next = head->next; /* 释放前保存后继。 */
        free(head); /* 归还当前结点。 */
        head = next; /* 继续处理剩余链表。 */
    }
}
/* 检查重复编号，分配并填充结点，沿二级指针找到尾部链接再接入。 */
static int insert(struct Reservation **head, int id, const char *name, int people,
                  const char *time) {
    if (find(*head, id)) /* 已有同编号时不能插入。 */
        return 0;
    struct Reservation *node = malloc(sizeof *node); /* 分配新结点。 */
    if (!node)
        return -1; /* 分配失败与重复编号区分。 */
    node->id = id; /* 初始化编号。 */
    node->people = people; /* 保存已校验人数。 */
    strcpy(node->name, name); /* 输入长度已检查，不会写越界。 */
    strcpy(node->time, time); /* 时间为五字节，末尾还有零。 */
    node->next = NULL; /* 新结点将位于表尾。 */
    while (*head)
        head = &(*head)->next; /* 二级指针最终指向应当接入新结点的链接。 */
    *head = node; /* 空表头或旧表尾的链接指向新结点。 */
    return 1;
}
/* 二级指针指向当前链接，故删除头结点和中间结点使用同一流程。 */
static int erase(struct Reservation **head, int id) {
    while (*head && (*head)->id != id) /* 沿指向结点的链接查找。 */
        head = &(*head)->next;
    if (!*head)
        return 0; /* 空链接说明编号不存在。 */
    struct Reservation *dead = *head; /* 保存将被删除的结点。 */
    *head = dead->next; /* 前驱链接跳过该结点。 */
    free(dead); /* 释放断开的结点。 */
    return 1;
}
int main(void) {
    /* 空链表起步；按行解析使非法命令不会消耗下一行。 */
    struct Reservation *head = NULL; /* 空表没有首结点。 */
    char line[256]; /* 暂存一条命令及终止零。 */
    int failed = 0; /* 记录内存分配失败的退出状态。 */
    while (fgets(line, sizeof line, stdin)) { /* 每次处理一行，EOF 时结束。 */
        size_t length = strlen(line); /* 已读入的字节数。 */
        /* 未完整读入的长行需丢弃剩余部分，再处理下一条命令。 */
        if (length && line[length - 1] != '\n' && !feof(stdin)) {
            int c; /* getchar 可能返回 EOF，故使用 int。 */
            while ((c = getchar()) != '\n' && c != EOF) { /* 消耗本行剩余字节。 */
            }
            puts("INVALID"); /* 长行整体只报告一次。 */
            continue; /* 不把剩余字节当作另一条命令。 */
        }
        int op, id, people; /* 当前命令及数字参数。 */
        char name[128], time[128], extra; /* extra 用来检测多余非空白字符。 */
        if (sscanf(line, "%d", &op) != 1) { /* 首字段必须是操作编号。 */
            puts("INVALID");
            continue;
        }
        /* 插入：先验证全部字段，重复编号不修改已有数据。 */
        if (op == 1) {
            if (sscanf(line, "%d%d%127s%d%127s %c", &op, &id, name, &people, time, &extra) != 5 ||
                id < 1 || strlen(name) > 31 || people < 1 || people > 1000 || !valid_time(time)) {
                puts("INVALID"); /* 字段数量、范围或时间非法。 */
                continue; /* 记录保持不变。 */
            }
            int status = insert(&head, id, name, people, time); /* 查重并尝试接入结点。 */
            if (status < 0) { /* 分配失败，停止接受命令。 */
                failed = 1;
                break;
            }
            puts(status ? "OK" : "DUPLICATE"); /* 区分成功和重复编号。 */
        } else if (op == 2 || op == 4) {
            /* 查询或删除只需要一个正编号，并拒绝多余字段。 */
            if (sscanf(line, "%d%d %c", &op, &id, &extra) != 2 || id < 1) {
                puts("INVALID"); /* 拒绝缺失、多余或非正编号。 */
                continue;
            }
            if (op == 4)
                puts(erase(&head, id) ? "OK" : "NOT_FOUND"); /* 删除成功或未找到。 */
            else {
                struct Reservation *r = find(head, id); /* 查询不修改链表。 */
                if (r)
                    print(r); /* 打印找到的记录。 */
                else
                    puts("NOT_FOUND");
            }
        } else if (op == 3) {
            /* 修改前完整校验人数和时间；仅在找到记录后写入。 */
            if (sscanf(line, "%d%d%d%127s %c", &op, &id, &people, time, &extra) != 4 || id < 1 ||
                people < 1 || people > 1000 || !valid_time(time)) {
                puts("INVALID"); /* 校验失败不改变原记录。 */
                continue;
            }
            struct Reservation *r = find(head, id); /* 在验证后查找目标。 */
            if (!r)
                puts("NOT_FOUND");
            else {
                r->people = people; /* 覆盖人数。 */
                strcpy(r->time, time); /* 覆盖合法时间及终止零。 */
                puts("OK");
            }
        } else if (op == 5 || op == 6) {
            /* 显示和退出不接受参数；遍历链表保持插入顺序。 */
            if (sscanf(line, "%d %c", &op, &extra) != 1) { /* 不允许附加字段。 */
                puts("INVALID");
                continue;
            }
            if (op == 6)
                break; /* 跳出循环后仍会释放链表。 */
            if (!head)
                puts("EMPTY");
            else
                for (struct Reservation *r = head; r; r = r->next) /* 从表头到表尾。 */
                    print(r);
        } else
            puts("INVALID"); /* 未知操作号。 */
    }
    /* 无论正常退出或分配失败，都释放已保存记录。 */
    destroy(head); /* 释放所有仍在表中的结点。 */
    return failed; /* 分配失败为非零，其余情况为零。 */
}
