/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 14:09
 * update_at: 2026-11-12 10:35
 */
// brute.cpp：小数据子集枚举暴力解，用来帮助理解题意并辅助对拍。
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 30;
int a[maxn];
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = 0;
    // 枚举所有 2^n - 1 个非空子集
    for (int mask = 1; mask < (1 << n); ++mask) {
        int idx = 1;
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                if (a[i] % idx != 0) {
                    ok = false;
                    break;
                }
                ++idx;
            }
        }
        if (ok) {
            ans = (ans + 1) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
