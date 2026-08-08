/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:24
 * update_at: 2026-08-04 12:24
 */

/* P1002 [NOIP 2002 普及组] 过河卒 */
/* 网格路径计数 DP：卒只能向右/向下走，马所在格与马一步能跳到的格子不能走。
 * 每个格子的路径数 = 上方格子的路径数 + 左方格子的路径数。 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 25;

int n, m;             // 终点坐标 (n, m)，起点 (0, 0)
int hx, hy;           // 马的位置
ll dp[MAXN][MAXN];    // dp[x][y]：从 (0,0) 走到 (x,y) 的合法路径数
bool blocked[MAXN][MAXN]; // blocked[x][y] = true 表示该格不能走

// 马的控制格偏移：0 号是马自己，其余 8 个是马一步能跳到的位置
int dx[] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {0, 2, -2, 2, -2, 1, -1, 1, -1};

// 判断 (x, y) 是否在棋盘内
bool in_board(int x, int y) {
    return x >= 0 && x <= n && y >= 0 && y <= m;
}

// 把马所在格和 8 个控制格全部标记为不能走
void mark_horse() {
    for (int i = 0; i < 9; i++) {
        int nx = hx + dx[i];
        int ny = hy + dy[i];
        if (in_board(nx, ny)) {
            blocked[nx][ny] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> hx >> hy;
    mark_horse();

    // 起点本身不能被马控制
    if (!blocked[0][0]) dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (blocked[i][j]) {
                dp[i][j] = 0;   // 不能走的格子路径数为 0
                continue;
            }
            // 卒只能从上方或左方走来，两个来源的路径数相加
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
