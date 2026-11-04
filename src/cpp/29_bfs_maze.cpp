/* 29_bfs_maze 迷宫广度优先搜索 | ISO C++11 | 拓展
 * 来源/关系：S1 p95 附加82：寻找路径的最短路拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：行列1..20；矩阵0可走、1墙；从左上到右下四方向；输出最少步数，不通为-1
 * 思想：队列按距离分层；入队时标记，保证每格只入队一次。
 * 复杂度：O(行×列)，空间同阶
 * 练习：增加前驱数组恢复路径；有权边不能直接套普通BFS。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
int main() {
    int rows, cols;
    if (!(std::cin >> rows >> cols) || rows < 1 || rows > 20 || cols < 1 || cols > 20)
        return 1;
    std::vector<std::vector<int>> a(rows, std::vector<int>(cols)),
        dist(rows, std::vector<int>(cols, -1));
    for (auto &row : a)
        for (int &x : row)
            if (!(std::cin >> x) || (x != 0 && x != 1))
                return 1;
    std::queue<std::pair<int, int>> q;
    if (!a[0][0]) {
        q.emplace(0, 0);
        dist[0][0] = 0;
    }
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty()) {
        std::pair<int, int> cell = q.front();
        q.pop();
        int r = cell.first, c = cell.second; // C++11用pair成员取值。
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !a[nr][nc] && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }
    }
    std::cout << dist[rows - 1][cols - 1] << '\n';
}
