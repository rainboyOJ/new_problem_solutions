/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:47
 * update_at: 2026-11-10 22:47
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 暴力 DFS：双人同步搜索
int m, n;
int a[55][55];
int ans = 0;

void dfs(int s, int x1, int x2, int current_sum) {
    int y1 = s - x1;
    int y2 = s - x2;

    if (s == m + n - 1) {
        if (x1 == m - 1 && x2 == m) {
            ans = max(ans, current_sum);
        }
        return;
    }

    // 四种走向：下下、下右、右下、右右
    int dx[2] = {1, 0};

    for (int d1 = 0; d1 < 2; ++d1) {
        int nx1 = x1 + dx[d1];
        int ny1 = y1 + (1 - dx[d1]);
        if (nx1 > m || ny1 > n) continue;

        for (int d2 = 0; d2 < 2; ++d2) {
            int nx2 = x2 + dx[d2];
            int ny2 = y2 + (1 - dx[d2]);
            if (nx2 > m || ny2 > n) continue;

            // 保持 nx1 < nx2，防止相交
            if (nx1 >= nx2) continue;

            dfs(s + 1, nx1, nx2, current_sum + a[nx1][ny1] + a[nx2][ny2]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> m >> n)) return 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    // 特判 2x2
    if (m == 2 && n == 2) {
        cout << a[1][2] + a[2][1] << "\n";
        return 0;
    }

    // 离开起点到达 s = 3，必为 (1, 2) 和 (2, 1)
    ans = 0;
    dfs(3, 1, 2, a[1][2] + a[2][1]);
    cout << ans << "\n";

    return 0;
}
