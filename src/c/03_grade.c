/* 03_grade switch百分制成绩 | ISO C99 | 基础
 * 来源/关系：S3 编程1；S2 编程4；S1 p14 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..100整数；输出A/B/C/D/E；范围外退出码1
 * 思想：按十位数分组，100单独并入A，break防贯穿。
 * 复杂度：O(1)
 * 练习：测试59/60/69/70/79/80/89/90/100；再改为if版本。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int score;
    char grade;
    if (scanf("%d", &score) != 1 || score < 0 || score > 100)
        return 1;
    switch (score / 10) {
    case 10:
    case 9:
        grade = 'A';
        break;
    case 8:
        grade = 'B';
        break;
    case 7:
        grade = 'C';
        break;
    case 6:
        grade = 'D';
        break;
    default:
        grade = 'E';
    }
    printf("%c\n", grade);
    return 0;
}
