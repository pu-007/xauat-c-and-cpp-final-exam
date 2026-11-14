/* 22_josephus 约瑟夫环：模拟到递推 | ISO C99 | 提高
 * 来源/关系：S1 p32 编程16、p77 编程3（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10000,k=1..100000；输出从0编号的最终幸存者
 * 思想：删除一个人后重编号；f(n)=(f(n-1)+k)%n，从f(1)=0递推。
 * 复杂度：O(n)，空间O(1)
 * 练习：先用数组标记出局过程验证n=5,k=3；一基编号最后加1。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：22_josephus.cpp用cin/cout代替scanf/printf；两者的int递推式完全相同。
 */
#include <stdio.h> /* 输入输出。 */
int main(void) {
    int n, k; /* 人数与每轮报数上限。 */
    if (scanf("%d%d", &n, &k) != 2 || n < 1 || n > 10000 || k < 1 || k > 100000)
        return 1; /* 检查输入及约定范围。 */
    int survivor = 0; /* 只有一人时其零基编号是0。 */
    for (int size = 2; size <= n; ++size) /* 从较小规模逐步恢复到n人。 */
        survivor = (survivor + k) % size; /* 将子问题编号映射回当前环。 */
    printf("%d\n", survivor); /* 输出零基幸存者。 */
    return 0; /* 返回成功状态。 */
}
