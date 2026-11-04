/* 22_josephus 约瑟夫环：模拟到递推 | ISO C99 | 提高
 * 来源/关系：S1 p32 编程16、p77 编程3（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10000,k=1..100000；输出从0编号的最终幸存者
 * 思想：删除一个人后重编号；f(n)=(f(n-1)+k)%n，从f(1)=0递推。
 * 复杂度：O(n)，空间O(1)
 * 练习：先用数组标记出局过程验证n=5,k=3；一基编号最后加1。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n, k;
    if (scanf("%d%d", &n, &k) != 2 || n < 1 || n > 10000 || k < 1 || k > 100000)
        return 1;
    int survivor = 0;
    for (int size = 2; size <= n; ++size)
        survivor = (survivor + k) % size;
    printf("%d\n", survivor);
    return 0;
}
