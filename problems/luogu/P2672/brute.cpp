/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:55
 * update_at: 2026-11-11 01:55
 */

// brute.cpp：小数据全组合枚举暴力验证
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> s(n), a(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<ll> ans(n + 1, 0);

    // 枚举所有 2^n 集合
    for (int mask = 1; mask < (1 << n); ++mask) {
        int cnt = 0;
        ll max_s = 0, sum_a = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                cnt++;
                max_s = max(max_s, s[i]);
                sum_a += a[i];
            }
        }
        ans[cnt] = max(ans[cnt], 2 * max_s + sum_a);
    }

    for (int x = 1; x <= n; ++x) cout << ans[x] << "\n";
    return 0;
}
