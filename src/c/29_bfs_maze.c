/* 29_bfs_maze 迷宫广度优先搜索 | ISO C99 | 拓展
 * 来源/关系：S1 p95 附加82：寻找路径的最短路拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：行列1..20；矩阵0可走、1墙；从左上到右下四方向；输出最少步数，不通为-1
 * 思想：队列按距离分层；入队时标记，保证每格只入队一次。
 * 复杂度：O(行×列)，空间同阶
 * 练习：增加前驱数组恢复路径；有权边不能直接套普通BFS。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int rows, cols, a[20][20], dist[20][20], qr[400], qc[400];
    if (scanf("%d%d", &rows, &cols) != 2 || rows < 1 || rows > 20 || cols < 1 || cols > 20)
        return 1;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            if (scanf("%d", &a[r][c]) != 1 || (a[r][c] != 0 && a[r][c] != 1))
                return 1;
            dist[r][c] = -1;
        }
    int head = 0, tail = 0;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    if (a[0][0] == 0) {
        qr[tail] = 0;
        qc[tail++] = 0;
        dist[0][0] = 0;
    }
    while (head < tail) {
        int r = qr[head], c = qc[head++];
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !a[nr][nc] && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                qr[tail] = nr;
                qc[tail++] = nc;
            }
        }
    }
    printf("%d\n", dist[rows - 1][cols - 1]);
    return 0;
}
