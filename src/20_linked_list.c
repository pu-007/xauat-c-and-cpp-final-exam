/* 20_linked_list 动态内存、头插、删除、反转 | ISO C99 | 提高
 * 来源/关系：S1 p77–78 链表题、模拟三编程3；同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100、删除目标；再输入n个int；按输入顺序建表，删除所有目标后反转输出
 * 思想：用二级指针统一删除头结点与普通结点；先保存next再释放。
 * 复杂度：O(n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：20_linked_list.cpp用forward_list的insert_after、remove、reverse代替malloc/free与指针操作。
 */
#include <stdio.h> /* 输入输出。 */
#include <stdlib.h> /* malloc和free。 */
struct Node { /* 单链表结点。 */
    int value; /* 存放的整数。 */
    struct Node *next; /* 指向下一结点或NULL。 */
};
static void destroy(struct Node *head) { /* 释放从head开始的整条链。 */
    while (head) {
        struct Node *next = head->next; /* 释放前保存后继。 */
        free(head); /* 归还当前结点。 */
        head = next; /* 继续处理后继。 */
    }
}
static int push_front(struct Node **head, int value) { /* 允许修改调用者的头指针。 */
    struct Node *p = malloc(sizeof *p); /* C中malloc返回的void指针可直接赋值。 */
    if (!p) /* 分配失败时不改变原链。 */
        return 0; /* 告知调用者插入失败。 */
    p->value = value; /* 初始化新结点数据。 */
    p->next = *head; /* 新结点先指向原头。 */
    *head = p; /* 更新调用者的头指针。 */
    return 1; /* 插入成功。 */
}
static struct Node *reverse(struct Node *head) { /* 返回反转后的头。 */
    struct Node *previous = NULL; /* 已反转部分初始为空。 */
    while (head) {
        struct Node *next = head->next; /* 保存尚未处理的链。 */
        head->next = previous; /* 当前结点改指已反转部分。 */
        previous = head; /* 扩展已反转部分。 */
        head = next; /* 继续原后继。 */
    }
    return previous; /* 原尾现在是新头。 */
}
int main(void) {
    int n, target; /* 数量和待删除的值。 */
    struct Node *head = NULL; /* 空链表。 */
    if (scanf("%d%d", &n, &target) != 2 || n < 0 || n > 100)
        return 1; /* 验证数量及输入。 */
    for (int i = 0; i < n; ++i) { /* 逐个读取并头插。 */
        int x; /* 当前输入。 */
        if (scanf("%d", &x) != 1 || !push_front(&head, x)) {
            destroy(head); /* 中途失败也释放已建结点。 */
            return 1; /* 报告读取或内存分配失败。 */
        }
    }
    head = reverse(head); /* 头插顺序相反，先还原输入顺序。 */
    struct Node **link = &head; /* link指向持有当前结点的指针。 */
    while (*link) { /* 遍历尚未检查的结点。 */
        if ((*link)->value == target) { /* 命中时删除，不移动link。 */
            struct Node *dead = *link; /* 保存将删除的结点。 */
            *link = dead->next; /* 跳过它，头结点也可统一处理。 */
            free(dead); /* link仍指向同一位置，继续检查新后继。 */
        } else
            link = &(*link)->next; /* 保留当前结点，移动到其next字段。 */
    }
    head = reverse(head); /* 按题目要求反转剩余结点。 */
    int first = 1; /* 控制首项前无空格。 */
    for (struct Node *p = head; p; p = p->next) {
        printf("%s%d", first ? "" : " ", p->value); /* 输出当前值。 */
        first = 0; /* 此后每项前添加空格。 */
    }
    putchar('\n'); /* 空表也输出空行。 */
    destroy(head); /* 正常路径释放全部结点。 */
    return 0; /* 成功结束。 */
}
