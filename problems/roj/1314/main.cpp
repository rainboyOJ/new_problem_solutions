/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:11
 * update_at: 2026-10-05 09:12
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 25;          // m 不超过 20，留一点余量
const int MAXN = 25;          // n 不超过 20，留一点余量

int n, m, x, y;
ll f[MAXN][MAXM];             // f[i][j] 表示从 (0,0) 走到 (i,j) 的合法路径数
bool blocked[MAXN][MAXM];     // blocked[i][j] 为 true 表示 (i,j) 是马的控制点

// 8 个马跳跃的日字方向（dx,dy）
const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

// 判断坐标 (i,j) 是否在棋盘内
inline bool in_board(int i, int j) {
    return i >= 0 && i <= n && j >= 0 && j <= m;
}

// 标记马的控制点：马自身 + 8 个日字跳跃点
void mark_control() {
    // 马自身
    blocked[x][y] = true;
    // 8 个日字方向
    for (int k = 0; k < 8; k++) {
        int ni = x + dx[k];
        int nj = y + dy[k];
        if (in_board(ni, nj)) {
            blocked[ni][nj] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> x >> y;

    mark_control();

    // 起点保证不是控制点，初始化为 1
    f[0][0] = 1;

    // 按行从上到下、按列从左到右递推
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (blocked[i][j]) {
                f[i][j] = 0;  // 控制点不可达
                continue;
            }
            if (i > 0) f[i][j] += f[i - 1][j];  // 从上方走下来
            if (j > 0) f[i][j] += f[i][j - 1];  // 从左方走过来
        }
    }

    cout << f[n][m] << "\n";
    return 0;
}
