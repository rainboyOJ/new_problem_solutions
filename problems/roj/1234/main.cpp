/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:12
 * update_at: 2026-10-05 06:12
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MOD = 10000;   // 只保留后四位
const ll BASE = 2011;   // 底数

// 快速幂：返回 base^e % mod
ll qpow(ll base, ll e, ll mod) {
    ll res = 1 % mod;
    ll a = base % mod;
    while (e > 0) {
        if (e & 1) res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

// 取字符串最后至多 4 位对应的整数
ll last_four(const string &s) {
    int len = s.length();
    int start = max(0, len - 4);
    ll val = 0;
    for (int i = start; i < len; i++) {
        val = val * 10 + (s[i] - '0');
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k;
    if (!(cin >> k)) return 0;

    string last_n, n;
    for (int i = 0; i < k; i++) {
        if (cin >> n) {
            last_n = n;                 // 读成功则更新
        }
        // 读失败时 last_n 保持原值，对齐旧版 cin>>string 的失败语义
        ll e = last_four(last_n);
        cout << qpow(BASE, e, MOD) << "\n";
    }
    return 0;
}
