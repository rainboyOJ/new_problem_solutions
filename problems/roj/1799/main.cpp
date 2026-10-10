/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:52
 * update_at: 2026-10-08 03:52
 */
// main.cpp：数列 —— 每个 m 元子集恰好对应 2 个合法数列（首三项的两种朝向），
// 故答案为 2 * sum_{m=3}^{n} C(n,m) = 2^(n+1) - n^2 - n - 2。
// n 最多 5000 位十进制，只能按字符串读入；指数用费马小定理降到模 (p-1)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL; // 取模质数 p
const ll PERIOD = MOD - 1;   // 费马小定理给出的 2 的指数周期 p-1

// 十进制大串按 Horner 法逐位取模，得到 n mod m
ll mod_of_digits(const string &s, ll m) {
    ll r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % m;
    return r;
}

// 快速幂：base^e mod MOD
ll power(ll base, ll e) {
    ll r = 1;
    base %= MOD;
    while (e > 0) {
        if (e & 1) r = r * base % MOD;
        base = base * base % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    size_t pos = s.find_first_not_of('0'); // 题面保证 n>=3，这里只做健壮性处理
    s = (pos == string::npos) ? string("0") : s.substr(pos);

    ll np = mod_of_digits(s, MOD);     // n mod p，用于多项式部分 n^2+n+2
    ll nm1 = mod_of_digits(s, PERIOD); // n mod (p-1)，用于指数部分
    ll exponent = (nm1 + 1) % PERIOD;  // (n+1) mod (p-1)

    ll pow2 = power(2, exponent);              // 2^(n+1) mod p
    ll poly = (np * np % MOD + np + 2) % MOD;  // n^2 + n + 2 mod p
    ll ans = (pow2 - poly + MOD) % MOD;

    cout << ans << '\n';
    return 0;
}
