/* 44_reservations 订餐信息管理：插入查询修改删除显示 | ISO C99 | 综合
 * 来源/关系：S6实验6 p47–51；链表C版与vector C++11版（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：菜单1 id name people HH:MM插入；2 id查询；3 id people HH:MM修改；4
 * id删除；5显示；6退出。编号正且唯一，姓名无空格<=31字节，人数1..1000
 * 思想：分离查找、验证、修改和释放；修改失败不破坏已有记录；维护唯一编号。
 * 复杂度：每条增删查改O(n)，空间O(n)
 * 练习：增设姓名修改、按时间排序、文件保存；先写数据格式再扩展菜单。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Reservation {
    int id, people;
    char name[32], time[6];
    struct Reservation *next;
};
static int valid_time(const char *s) {
    if (strlen(s) != 5 || s[2] != ':')
        return 0;
    if (s[0] < '0' || s[0] > '9' || s[1] < '0' || s[1] > '9' || s[3] < '0' || s[3] > '9' ||
        s[4] < '0' || s[4] > '9')
        return 0;
    return (s[0] - '0') * 10 + s[1] - '0' < 24 && (s[3] - '0') * 10 + s[4] - '0' < 60;
}
static struct Reservation *find(struct Reservation *head, int id) {
    while (head && head->id != id)
        head = head->next;
    return head;
}
static void print(const struct Reservation *r) {
    printf("%d %s %d %s\n", r->id, r->name, r->people, r->time);
}
static void destroy(struct Reservation *head) {
    while (head) {
        struct Reservation *next = head->next;
        free(head);
        head = next;
    }
}
static int insert(struct Reservation **head, int id, const char *name, int people,
                  const char *time) {
    if (find(*head, id))
        return 0;
    struct Reservation *node = malloc(sizeof *node);
    if (!node)
        return -1;
    node->id = id;
    node->people = people;
    strcpy(node->name, name);
    strcpy(node->time, time);
    node->next = NULL;
    while (*head)
        head = &(*head)->next; /* 二级指针最终指向应当接入新结点的链接。 */
    *head = node;
    return 1;
}
static int erase(struct Reservation **head, int id) {
    while (*head && (*head)->id != id)
        head = &(*head)->next;
    if (!*head)
        return 0;
    struct Reservation *dead = *head;
    *head = dead->next;
    free(dead);
    return 1;
}
int main(void) {
    struct Reservation *head = NULL;
    char line[256];
    int failed = 0;
    while (fgets(line, sizeof line, stdin)) {
        size_t length = strlen(line);
        if (length && line[length - 1] != '\n' && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            puts("INVALID");
            continue;
        }
        int op, id, people;
        char name[128], time[128], extra;
        if (sscanf(line, "%d", &op) != 1) {
            puts("INVALID");
            continue;
        }
        if (op == 1) {
            if (sscanf(line, "%d%d%127s%d%127s %c", &op, &id, name, &people, time, &extra) != 5 ||
                id < 1 || strlen(name) > 31 || people < 1 || people > 1000 || !valid_time(time)) {
                puts("INVALID");
                continue;
            }
            int status = insert(&head, id, name, people, time);
            if (status < 0) {
                failed = 1;
                break;
            }
            puts(status ? "OK" : "DUPLICATE");
        } else if (op == 2 || op == 4) {
            if (sscanf(line, "%d%d %c", &op, &id, &extra) != 2 || id < 1) {
                puts("INVALID");
                continue;
            }
            if (op == 4)
                puts(erase(&head, id) ? "OK" : "NOT_FOUND");
            else {
                struct Reservation *r = find(head, id);
                if (r)
                    print(r);
                else
                    puts("NOT_FOUND");
            }
        } else if (op == 3) {
            if (sscanf(line, "%d%d%d%127s %c", &op, &id, &people, time, &extra) != 4 || id < 1 ||
                people < 1 || people > 1000 || !valid_time(time)) {
                puts("INVALID");
                continue;
            }
            struct Reservation *r = find(head, id);
            if (!r)
                puts("NOT_FOUND");
            else {
                r->people = people;
                strcpy(r->time, time);
                puts("OK");
            }
        } else if (op == 5 || op == 6) {
            if (sscanf(line, "%d %c", &op, &extra) != 1) {
                puts("INVALID");
                continue;
            }
            if (op == 6)
                break;
            if (!head)
                puts("EMPTY");
            else
                for (struct Reservation *r = head; r; r = r->next)
                    print(r);
        } else
            puts("INVALID");
    }
    destroy(head);
    return failed;
}
