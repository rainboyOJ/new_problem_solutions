/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:11
 * update_at: 2026-10-09 21:11
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法就是按题面直译：每个询问都从询问的格子出发单独 BFS 一次，数出能走到的格子数。
// m 个询问就要搜索 m 次，复杂度 O(m * n^2)，只有小数据跑得动，
// 所以这里专门用来和 main.cpp 对拍，不作为正解。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 暴力只跑小数据，n <= 100，下标、计数都用 int。
const int MAXN = 105; // 暴力只服务小数据，n <= 100 就够用

char g[MAXN][MAXN]; // g[i][j]：迷宫第 i 行第 j 列的字符，行列下标从 1 开始
int vis[MAXN][MAXN]; // vis[i][j]：这一次搜索里格子有没有走过，每次询问前清空
int n, m;

// 四个方向的增量：下、上、右、左
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 只清实际用到的 1..n 范围，不必清整个数组
void clear_vis() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            vis[i][j] = 0;
        }
    }
}

// 从 (sx, sy) 出发单独 BFS 一次，返回这一片能走到的格子数（包含起点）
int bfs_count(int sx, int sy) {
    clear_vis();

    queue<pair<int, int> > q;
    q.push(make_pair(sx, sy));
    vis[sx][sy] = 1;

    int cnt = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        cnt++;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue; // 走出迷宫
            if (vis[nx][ny]) continue;                          // 这次搜索已经走过
            if (g[nx][ny] == g[x][y]) continue;                 // 只能走到数值不同的相邻格
            vis[nx][ny] = 1;
            q.push(make_pair(nx, ny));
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= n; j++) {
            g[i][j] = row[j - 1];
        }
    }

    for (int k = 1; k <= m; k++) {
        int i, j;
        cin >> i >> j;
        cout << bfs_count(i, j) << '\n';
    }

    return 0;
}
