/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 02:25
 * update_at: 2026-11-11 03:00
 */

// brute.cpp：小数据多重循环暴力枚举
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long;
const int MOD = 998244353;

void solve() {
    int n, m, c, f;
    cin >> n >> m >> c >> f;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    ll ans_c = 0, ans_f = 0;

    for (int y0 = 0; y0 < m; ++y0) {
        for (int x1 = 0; x1 < n; ++x1) {
            for (int x2 = x1 + 2; x2 < n; ++x2) {
                // 检查 [x1, x2] 列 y0 是否全为 '0'
                bool col_ok = true;
                for (int r = x1; r <= x2; ++r) {
                    if (g[r][y0] == '1') { col_ok = false; break; }
                }
                if (!col_ok) continue;

                // 统计 x1 行向右可延伸端点
                ll len1 = 0;
                for (int c1 = y0 + 1; c1 < m; ++c1) {
                    if (g[x1][c1] == '0') len1++;
                    else break;
                }

                // 统计 x2 行向右可延伸端点
                ll len2 = 0;
                for (int c2 = y0 + 1; c2 < m; ++c2) {
                    if (g[x2][c2] == '0') len2++;
                    else break;
                }

                ll cur_c = (len1 * len2) % MOD;
                ans_c = (ans_c + cur_c) % MOD;

                // 统计 x3 延伸（从 x2+1 开始向下直到遇到 1 或出界）
                ll down_len = 0;
                for (int x3 = x2 + 1; x3 < n; ++x3) {
                    if (g[x3][y0] == '0') down_len++;
                    else break;
                }
                ans_f = (ans_f + cur_c * down_len) % MOD;
            }
        }
    }

    cout << (1LL * c * ans_c) % MOD << " " << (1LL * f * ans_f) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, id;
    if (!(cin >> t >> id)) return 0;
    while (t--) solve();
    return 0;
}
