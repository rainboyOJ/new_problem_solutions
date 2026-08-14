/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1605 迷宫：网格 DFS，访问标记与回溯恢复。 */

#include <iostream>

const int max_n = 15;  // N、M 最大为 5，留出余量

int rows, cols;                 // 迷宫长宽
int obstacle_count;             // 障碍个数
int start_row, start_col;       // 起点坐标
int end_row, end_col;           // 终点坐标
int blocked[max_n][max_n];      // blocked[row][col] = 1 表示障碍，不可走
int visited[max_n][max_n];      // visited[row][col] = 1 表示在当前路径上已走过
int path_count = 0;             // 从起点到终点的方案总数
int dir_row[4] = {0, 0, 1, -1};
int dir_col[4] = {1, -1, 0, 0};

// 从 (row, col) 出发继续走，每到达一次终点就找到一条完整路径。
void dfs(int row, int col) {
    if (row == end_row && col == end_col) {
        path_count += 1;  // 到达终点，统计当前这条路径
        return;
    }

    // 这一层枚举四个方向的下一步选择。
    for (int dir = 0; dir < 4; dir += 1) {
        int next_row = row + dir_row[dir];
        int next_col = col + dir_col[dir];
        if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols) {
            continue;  // 出界
        }
        if (blocked[next_row][next_col] || visited[next_row][next_col]) {
            continue;  // 障碍或已被当前路径走过
        }

        visited[next_row][next_col] = 1;  // 前进阶段：先标记下一格已访问
        dfs(next_row, next_col);
        visited[next_row][next_col] = 0;  // 回溯阶段：撤销标记，把格子还给其它分支
    }
}

int main() {
    std::cin >> rows >> cols >> obstacle_count;
    std::cin >> start_row >> start_col >> end_row >> end_col;
    // 输入是 1 起始坐标，数组内部统一转成 0 起始下标。
    start_row -= 1;
    start_col -= 1;
    end_row -= 1;
    end_col -= 1;

    for (int k = 0; k < obstacle_count; k += 1) {
        int x, y;
        std::cin >> x >> y;
        blocked[x - 1][y - 1] = 1;
    }

    visited[start_row][start_col] = 1;  // 起点视为已访问，防止路径绕回起点
    dfs(start_row, start_col);
    std::cout << path_count << '\n';
    return 0;
}
