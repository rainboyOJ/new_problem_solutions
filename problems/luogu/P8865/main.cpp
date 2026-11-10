/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 02:25
 * update_at: 2026-11-11 03:05
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long;

const int MOD = 998244353;
const int MAXN = 1005;

string grid[MAXN];
int R[MAXN][MAXN]; // 向右可延伸长度（不含主干自身）
int D[MAXN][MAXN]; // 向下可延伸长度（不含主干自身）

void solve() {
    int n, m, c, f;
    cin >> n >> m >> c >> f;

    for (int i = 1; i <= n; ++i) {
        cin >> grid[i];
    }

    // 清空边界
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            R[i][j] = 0;
            D[i][j] = 0;
        }
    }

    // 预处理 R[i][j]：第 i 行从第 j 列向右可延伸的端点数（y1 > j）
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (grid[i][j - 1] == '1' || grid[i][j] == '1') {
                R[i][j] = 0;
            } else {
                R[i][j] = R[i][j + 1] + 1;
            }
        }
    }

    // 预处理 D[i][j]：第 j 列从第 i 行向下可延伸的端点数（x3 > i）
    for (int j = 1; j <= m; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            if (grid[i][j - 1] == '1' || grid[i + 1][j - 1] == '1') {
                D[i][j] = 0;
            } else {
                D[i][j] = D[i + 1][j] + 1;
            }
        }
    }

    ll total_C = 0;
    ll total_F = 0;

    for (int j = 1; j <= m; ++j) {
        ll sum_up = 0;

        for (int i = 1; i <= n; ++i) {
            if (grid[i][j - 1] == '1') {
                sum_up = 0;
            } else {
                if (i >= 3 && grid[i - 1][j - 1] == '0') {
                    sum_up = (sum_up + R[i - 2][j]) % MOD;
                }

                int cur_r = R[i][j];
                int cur_d = D[i][j];

                if (cur_r > 0 && sum_up > 0) {
                    total_C = (total_C + sum_up * cur_r) % MOD;
                }
                if (cur_r > 0 && sum_up > 0 && cur_d > 0) {
                    total_F = (total_F + sum_up * cur_r % MOD * cur_d) % MOD;
                }
            }
        }
    }

    ll ans_C = (1LL * c * total_C) % MOD;
    ll ans_F = (1LL * f * total_F) % MOD;

    cout << ans_C << " " << ans_F << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, id;
    if (!(cin >> t >> id)) return 0;

    while (t--) {
        solve();
    }

    return 0;
}
