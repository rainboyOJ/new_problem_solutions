/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:20
 * update_at: 2026-10-26 16:36
 */
// brute.cpp：小数据暴力解，直接枚举子序列的上一个元素，O(n^2)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

ll n;
ll a[MAXN]; // 输入的数列
ll f[MAXN]; // f[i]：以第 i 个数结尾的最长合法子序列长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll ans = 1;
    // 枚举每一对 (j, i)，j < i 且 a[j] & a[i] != 0 时可以把 i 接在 j 后面。
    for (ll i = 1; i <= n; i++) {
        f[i] = 1;
        for (ll j = 1; j < i; j++) {
            if ((a[j] & a[i]) != 0 && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > ans) {
            ans = f[i];
        }
    }

    cout << ans << '\n';
    return 0;
}
