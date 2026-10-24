/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:30
 * update_at: 2026-10-23 23:30
 */
// brute.cpp：小数据指数级枚举暴力解
// 枚举全部 2^N 种选择方案，逐一检查前置依赖是否全部满足且总空间不超过 M
// 时间复杂度 O(2^N * N)，仅适用于 N <= 20 的小规模数据对拍与验证
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n, m;
ll w[MAXN], v[MAXN], d[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];

    ll ans = 0;
    int limit = 1 << n;
    for (int mask = 0; mask < limit; ++mask) {
        bool ok = true;
        ll total_w = 0;
        ll total_v = 0;

        for (int i = 1; i <= n; ++i) {
            if ((mask >> (i - 1)) & 1) {
                total_w += w[i];
                total_v += v[i];
                if (d[i] != 0) {
                    if (!((mask >> (d[i] - 1)) & 1)) {
                        ok = false;
                        break;
                    }
                }
            }
        }

        if (ok && total_w <= m) {
            if (total_v > ans) {
                ans = total_v;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
