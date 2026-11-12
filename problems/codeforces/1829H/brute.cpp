/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 14:26
 * update_at: 2026-11-12 15:05
 */
// brute.cpp：小数据子集枚举暴力解，用来帮助理解题意并辅助对拍。
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 30;
int a[maxn];
const int MOD = 1e9 + 7;

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = 0;
    // 枚举所有 2^n - 1 个非空子集
    for (int mask = 1; mask < (1 << n); ++mask) {
        int and_sum = -1;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                if (and_sum == -1) and_sum = a[i];
                else and_sum &= a[i];
            }
        }
        if (__builtin_popcount(and_sum) == k) {
            ans = (ans + 1) % MOD;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
