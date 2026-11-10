/**
 * Problem: luogu P1982 - [NOIP 2013 普及组] 小朋友的数字 (Brute Force using __int128)
 * Author: rainboy
 * Date: 2026-11-11 00:35
 * Description: __int128 全局真实值最大值跟踪基准
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using int128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p_ll;
    if (!(cin >> n >> p_ll)) return 0;

    int128 p = p_ll;
    vector<int128> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long val;
        cin >> val;
        a[i] = val;
    }

    vector<int128> f(n + 1);
    int128 cur_seg = a[1];
    f[1] = a[1];
    for (int i = 2; i <= n; ++i) {
        cur_seg = max(cur_seg + a[i], a[i]);
        f[i] = max(f[i - 1], cur_seg);
    }

    vector<int128> g(n + 1);
    g[1] = f[1];
    int128 max_score = g[1];

    if (n >= 2) {
        g[2] = g[1] + f[1];
        max_score = max(max_score, g[2]);
        int128 max_prev = g[1] + f[1];
        for (int i = 3; i <= n; ++i) {
            max_prev = max(max_prev, g[i - 1] + f[i - 1]);
            g[i] = max_prev;
            max_score = max(max_score, g[i]);
        }
    }

    if (max_score < 0) {
        long long ans = -((-max_score) % p);
        cout << ans << "\n";
    } else {
        long long ans = max_score % p;
        cout << ans << "\n";
    }

    return 0;
}
