/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char grid[MAXN][MAXN]; // 地图，'*' 表示地雷

// 8 个方向：上左、上、上右、左、右、下左、下、下右
int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 统计 (r,c) 周围 8 格的地雷数量
int count_mine(int r, int c) {
    int cnt = 0;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '*')
            cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*')
                cout << '*';
            else
                cout << count_mine(i, j);
        }
        cout << "\n";
    }

    return 0;
}
