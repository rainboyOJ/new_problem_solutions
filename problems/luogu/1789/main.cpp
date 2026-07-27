/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

bool lit[105][105]; // 是否被照亮
int n, t, g;        // 棋盘大小、火把数、萤石数

int main() {
    cin >> n >> t >> g;
    int x, y;
    // 处理火把：曼哈顿距离 <= 2
    for (int k = 1; k <= t; k++) {
        cin >> x >> y;
        for (int dx = -2; dx <= 2; dx++)
            for (int dy = -2; dy <= 2; dy++)
                if (abs(dx) + abs(dy) <= 2) { // 曼哈顿距离条件
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n)
                        lit[nx][ny] = true;
                }
    }
    // 处理萤石：5x5 正方形
    for (int k = 1; k <= g; k++) {
        cin >> x >> y;
        for (int dx = -2; dx <= 2; dx++)
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n)
                    lit[nx][ny] = true;
            }
    }
    // 统计未被照亮的格子
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!lit[i][j]) ans++;
    cout << ans;
    return 0;
}
