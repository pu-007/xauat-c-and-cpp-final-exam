/* 20_linked_list 动态内存、头插、删除、反转 | ISO C99 | 提高
 * 来源/关系：S1 p77–78 链表题、模拟三编程3；同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100、删除目标；再输入n个int；按输入顺序建表，删除所有目标后反转输出
 * 思想：用二级指针统一删除头结点与普通结点；先保存next再释放。
 * 复杂度：O(n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <stdlib.h>
struct Node {
    int value;
    struct Node *next;
};
static void destroy(struct Node *head) {
    while (head) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}
static int push_front(struct Node **head, int value) {
    struct Node *p = malloc(sizeof *p); /* C中不强转malloc；先检查分配是否成功。 */
    if (!p)
        return 0;
    p->value = value;
    p->next = *head;
    *head = p;
    return 1;
}
static struct Node *reverse(struct Node *head) {
    struct Node *previous = NULL;
    while (head) {
        struct Node *next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}
int main(void) {
    int n, target;
    struct Node *head = NULL;
    if (scanf("%d%d", &n, &target) != 2 || n < 0 || n > 100)
        return 1;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1 || !push_front(&head, x)) {
            destroy(head);
            return 1;
        }
    }
    head = reverse(head); /* 头插是逆序建表，先还原输入顺序。 */
    struct Node **link = &head;
    while (*link) {
        if ((*link)->value == target) {
            struct Node *dead = *link;
            *link = dead->next;
            free(dead);
        } else
            link = &(*link)->next;
    }
    head = reverse(head);
    int first = 1;
    for (struct Node *p = head; p; p = p->next) {
        printf("%s%d", first ? "" : " ", p->value);
        first = 0;
    }
    putchar('\n');
    destroy(head);
    return 0;
}
