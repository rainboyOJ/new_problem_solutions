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

ll n, m, k, x; // n 个位置、每轮平移 m、轮数为 10^k、询问 x 号小伙伴

// 快速幂：返回 base^exp mod mod，中间乘积用 ll 不会溢出。
ll qpow(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> x;

    // 每轮全体位置 +m，10^k 轮后位置为 (x + m*10^k) mod n。
    ll ten_pow = qpow(10, k, n);       // 10^k mod n
    ll ans = (x + m * ten_pow) % n;    // 平移总量 m*10^k 对 n 取模
    cout << ans << '\n';

    return 0;
}
