/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:37
 * update_at: 2026-11-10 22:37
 */

// brute.cpp：小数据暴力/四维直接 DP 解，用于辅助对拍和基线验证。
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 12;
int a[MAXN][MAXN];
// f[i][j][k][l] 表示第一条路径在 (i, j)，第二条路径在 (k, l) 时的最大得分
int f[MAXN][MAXN][MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int x, y, v;
    while (cin >> x >> y >> v && (x || y || v)) {
        a[x][y] = v;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                for (int l = 1; l <= n; ++l) {
                    int val = (i == k && j == l) ? a[i][j] : (a[i][j] + a[k][l]);
                    int prev_max = 0;
                    prev_max = max(prev_max, f[i - 1][j][k - 1][l]);
                    prev_max = max(prev_max, f[i - 1][j][k][l - 1]);
                    prev_max = max(prev_max, f[i][j - 1][k - 1][l]);
                    prev_max = max(prev_max, f[i][j - 1][k][l - 1]);
                    f[i][j][k][l] = prev_max + val;
                }
            }
        }
    }

    cout << f[n][n][n][n] << "\n";
    return 0;
}
