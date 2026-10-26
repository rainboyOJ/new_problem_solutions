/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:20
 * update_at: 2026-10-26 13:20
 */
// main.cpp：按二进制位维护最长合法子序列长度，把 O(n^2) 的枚举压成 O(n * 30)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXB = 31; // a_i <= 1e9 < 2^30，最多用到第 30 位

ll n;
ll best[MAXB]; // best[b]：以某个含第 b 位的数结尾的、最长合法子序列的长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;

        // 第 i 个数能接在任何一个末项与它有公共位的子序列后面，取这些长度里的最大值。
        ll cur = 0;
        for (int b = 0; b < MAXB; b++) {
            if (((x >> b) & 1) && best[b] > cur) {
                cur = best[b];
            }
        }
        cur = cur + 1; // 接上自己

        // 以 x 结尾的最优子序列长度 cur，可以更新 x 的每一个二进制位。
        for (int b = 0; b < MAXB; b++) {
            if (((x >> b) & 1) && cur > best[b]) {
                best[b] = cur;
            }
        }

        if (cur > ans) {
            ans = cur;
        }
    }

    cout << ans << '\n';
    return 0;
}
