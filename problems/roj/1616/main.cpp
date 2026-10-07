/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:04
 * update_at: 2026-10-06 01:04
 */

#include <iostream>
using namespace std;

typedef long long ll;

ll a, b, m;

// 二进制快速幂：把指数 b 拆成二进制，边平方边取模
ll qpow(ll base, ll exp, ll mod) {
    ll ans = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) ans = ans * base % mod; // 当前二进制位为 1，乘入答案
        base = base * base % mod;            // 底数平方，准备下一位
        exp >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> m;
    cout << qpow(a, b, m) << '\n';
    return 0;
}
