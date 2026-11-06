/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 16:49
 * update_at: 2026-11-06 23:10
 */
// main.cpp：朴素解，与 main.py 是同一套写法。
// 固定半长 q，把「s[i] 与 s[i+q] 是否相容」一次算成数组 compat[]，
// 再用 run[] 累计连续相容长度；run[i] >= q 即找到长度 2q 的串联重复。
// 时间 O(n^2)，空间 O(n)。C++ 里这个复杂度已经足够，无需位运算。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

ll t;
char s[MAXN];       // 当前测试串，下标从 1 开始
ll n;

// compat[i] = 1 表示 s[i] 与 s[i+q] 相容（相等，或至少一边是 '?'）
// 有效下标为 1 .. n-q
bool compat[MAXN];

// run[i] 表示以 i 结尾的连续相容长度；run[0] 恒为 0，用作递推起点
ll run[MAXN];

// 判断半长 q 是否存在串联重复；存在返回 q，否则返回 0
ll check(ll q) {
    for (ll i = 1; i + q <= n; i++) {
        compat[i] = (s[i] == s[i + q] || s[i] == '?' || s[i + q] == '?');
    }
    for (ll i = 1; i + q <= n; i++) {
        if (compat[i] == false) {
            run[i] = 0;
        } else {
            run[i] = run[i - 1] + 1;
            // 连续 q 个相容，说明 s[i-q+1 .. i+q] 是长度 2q 的串联重复
            if (run[i] >= q) {
                return q;
            }
        }
    }
    return 0;
}

void solve() {
    ll ans = 0;
    for (ll q = 1; q <= n / 2; q++) {
        ll got = check(q);
        if (got > ans) {
            ans = got;
        }
    }
    cout << ans * 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> (s + 1);
        n = strlen(s + 1);
        solve();
    }

    return 0;
}
