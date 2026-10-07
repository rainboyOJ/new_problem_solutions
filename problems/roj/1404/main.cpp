/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:03
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
const ll M = 1LL << 32;          // 32 位环绕模数
const ll HALF = 1LL << 31;       // 有符号 int 正负分界

// 把值按 C++ int（32 位有符号）语义截断
ll v32(ll a) {
    ll r = a % M;
    if (r < 0) r += M;
    if (r >= HALF) r -= M;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    // std 从 sqrt(6+2n)-1 开始枚举 m
    ll i = (ll)(sqrt((double)(6 + 2 * n))) - 1;
    if (i < 1) i = 1;
    while (true) {
        // 模拟 std.cpp 的 int 表达式 i*i + i - 2*n
        ll t = v32(v32(i * i) + i - 2 * n);
        if (t % 6 == 0) {
            ll x = t / 6;
            if (x > 0) {
                cout << x << " " << i << "\n";
                break;
            }
        }
        ++i;
    }
    return 0;
}
