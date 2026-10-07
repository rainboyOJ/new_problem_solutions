/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:25
 * update_at: 2026-10-06 15:25
 */

#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 题目 n, m <= 100

int n, m;
char grid[MAXN][MAXN];

// 8 个方向偏移：三行三列去掉中心 (0,0)
int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 计算 (r, c) 八邻域内且仍在雷区中的地雷数
int count_neighbor_mines(int r, int c) {
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 1 && nr <= n && nc >= 1 && nc <= m) { // 越界方向直接丢弃
            if (grid[nr][nc] == '*') cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (grid[i] + 1); // 从 grid[i][1] 开始读入 m 个字符
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '*') {
                cout << '*';
            } else {
                cout << count_neighbor_mines(i, j);
            }
        }
        cout << '\n';
    }

    return 0;
}
