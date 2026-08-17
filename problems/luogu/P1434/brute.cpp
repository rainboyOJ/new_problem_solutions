/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-17 13:04
 * update_at: 2026-08-17 13:10
 */
// brute.cpp：小数据暴力解，把每一步的移动方向看成选择序列来递归枚举所有滑坡路线。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;

int R, C;
int h[maxn][maxn];   // h[i][j] 格子 (i,j) 的高度
int ans = 1;         // 最长滑坡长度

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 当前停在 (x,y)，这条路线已经经过 len 个格子。
// 这一层要做选择：从上下左右四个方向里挑一个还没越界且高度严格更小的方向继续滑。
// 高度严格递减保证路线不会绕回走重复格子，所以不需要记录访问状态。
void dfs(int x, int y, int len) {
    if (ans < len) ans = len;   // 无论继续与否，当前都是一条完整路线，更新答案
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > R || ny < 1 || ny > C) continue;
        if (h[nx][ny] >= h[x][y]) continue;   // 只能滑到高度严格更小的格子
        dfs(nx, ny, len + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            cin >> h[i][j];

    // 从每个格子出发各枚举一次所有路线，取最长的那条。
    // 路线数量随格子数指数增长，只适合小数据对拍。
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            dfs(i, j, 1);

    cout << ans << endl;
    return 0;
}
