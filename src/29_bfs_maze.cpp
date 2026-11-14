/* 29_bfs_maze 迷宫广度优先搜索 | ISO C++11 | 拓展
 * 来源/关系：S1 p95 附加82：寻找路径的最短路拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：行列1..20；矩阵0可走、1墙；从左上到右下四方向；输出最少步数，不通为-1
 * 思想：队列按距离分层；入队时标记，保证每格只入队一次。
 * 复杂度：O(行×列)，空间同阶
 * 对照 29_bfs_maze.c：C 用定长数组模拟队列，C++ 用 vector 和 queue。
 * 练习：增加前驱数组恢复路径；有权边不能直接套普通BFS。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 声明 cin 和 cout；C 使用 scanf、printf。
#include <vector> // 提供动态二维网格；C 使用固定数组。
#include <queue> // 提供先进先出队列；C 使用数组和首尾下标。
#include <utility> // 提供 pair 保存行列；C 用两个数组保存坐标。
int main() {
    int rows, cols; // 迷宫的行列数。
    if (!(std::cin >> rows >> cols) || rows < 1 || rows > 20 || cols < 1 || cols > 20) // 验证尺寸。
        return 1; // 尺寸不合法，退出。
    std::vector<std::vector<int>> a(rows, std::vector<int>(cols)), // 按实际尺寸建立迷宫。
        dist(rows, std::vector<int>(cols, -1)); // 所有格子初始未访问。
    for (auto &row : a) // 通过引用逐行填充。
        for (int &x : row) // 通过引用读取每格。
            if (!(std::cin >> x) || (x != 0 && x != 1)) // 排除非法内容。
                return 1; // 格子内容不合法，退出。
    std::queue<std::pair<int, int>> q; // 队列元素包含行和列。
    if (!a[0][0]) { // 只有可走的起点才入队。
        q.emplace(0, 0); // 原位构造起点坐标。
        dist[0][0] = 0; // 起点到自身的距离为零。
    }
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1}; // 四个方向的增量。
    while (!q.empty()) { // 逐个处理已发现的格子。
        std::pair<int, int> cell = q.front(); // 取得队首坐标。
        q.pop(); // 移除队首。
        int r = cell.first, c = cell.second; // C++11 用 pair 成员取行列。
        for (int d = 0; d < 4; ++d) { // 枚举邻居方向。
            int nr = r + dr[d], nc = c + dc[d]; // 算出邻居坐标。
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !a[nr][nc] && dist[nr][nc] == -1) { // 必须在界内、可走且未访问。
                dist[nr][nc] = dist[r][c] + 1; // 入队前标记最短距离。
                q.emplace(nr, nc); // 后续处理这个邻居。
            }
        }
    }
    std::cout << dist[rows - 1][cols - 1] << '\n'; // 不可达时保留初值 -1。
}
