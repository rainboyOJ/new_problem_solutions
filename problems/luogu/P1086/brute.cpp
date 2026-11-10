/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:57
 * update_at: 2026-11-10 22:57
 */
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// 暴力模拟：每次两重循环扫描整个矩阵，找到当前花生数最大的格子
int m, n, k;
int grid[25][25];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> m >> n >> k)) return 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }

    int total_peanuts = 0;
    int time_used = 0;
    int cur_x = 0;
    int cur_y = 0;
    bool is_first = true;

    while (true) {
        int max_val = 0;
        int target_x = 0, target_y = 0;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (grid[i][j] > max_val) {
                    max_val = grid[i][j];
                    target_x = i;
                    target_y = j;
                }
            }
        }

        if (max_val == 0) break; // 没有花生了

        int move_time = 0;
        if (is_first) {
            move_time = target_x;
        } else {
            move_time = abs(target_x - cur_x) + abs(target_y - cur_y);
        }

        int pick_time = 1;
        int return_time = target_x;

        if (time_used + move_time + pick_time + return_time <= k) {
            time_used += move_time + pick_time;
            total_peanuts += max_val;
            cur_x = target_x;
            cur_y = target_y;
            grid[target_x][target_y] = 0; // 采摘后清空
            is_first = false;
        } else {
            break;
        }
    }

    cout << total_peanuts << "\n";

    return 0;
}
