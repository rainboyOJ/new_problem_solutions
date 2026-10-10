/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:32
 * update_at: 2026-10-08 04:32
 */
// 一本通 1808 《斐波那契数列》
// 题意：求最小的 n>=0 使 F_n ≡ a (mod 10^13)，不存在输出 -1。
//
// 思路（逐层截断提升）：
//   先取一个周期极短的基底模数 10^4（皮萨诺周期 pi(10^4)=15000），
//   暴力枚举一个周期，收集所有满足 F_n ≡ a (mod 10^4) 的下标作为候选集。
//   对 k>=3 有 pi(10^k)=15*10^(k-1)，即周期随 k 每增 1 恰好扩大 10 倍。
//   于是"模 10^k 的解"必须落在"模 10^(k-1) 的某个解 r 加上 c*pi(10^(k-1))"
//   这 10 个类里（c=0..9），逐层过滤到 k=13，剩下的候选取最小下标即为答案。
//   每层判断用快速倍增求 F_n mod 10^k，O(log n) 一次。
//
// 溢出：模 10^13 时两数相乘可达 10^26，必须用 unsigned __int128 承接中间结果。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned __int128 u128;

const ll MOD13 = 10000000000000LL;  // 10^13
const ll MOD4 = 10000LL;            // 基底模数 10^4
const ll PERIOD4 = 15000LL;         // 皮萨诺周期 pi(10^4) = 1.5*10^4

ll a;                 // 待查询的值
vector<ll> cur, nxt;  // 候选下标集（逐层交替使用）

// 模 m 乘法：m 最大 10^13，乘积最大 10^26，用 128 位承接
ll mulmod(ll x, ll y, ll m) {
    return (ll)((u128)x * y % (u128)m);
}

// 快速倍增求 F_n mod m，返回 F_n；迭代处理 n 的二进制位
ll fib_mod(ll n, ll m) {
    ll fk = 0, fk1 = 1 % m;  // 当前 (F_k, F_{k+1})，初始 k=0
    for (int bit = 62; bit >= 0; bit--) {
        // (F_{2k}, F_{2k+1}) = (F_k*(2F_{k+1}-F_k), F_k^2 + F_{k+1}^2)
        ll c = mulmod(fk, ((2 * fk1 - fk) % m + m) % m, m);
        ll d = (mulmod(fk, fk, m) + mulmod(fk1, fk1, m)) % m;
        if ((n >> bit) & 1) {
            fk = d;
            fk1 = (c + d) % m;
        } else {
            fk = c;
            fk1 = d;
        }
    }
    return fk;
}

int main() {
    scanf("%lld", &a);

    // 第 4 层：暴力枚举一个模 10^4 的周期，收集全部候选下标
    ll f0 = 0, f1 = 1;
    for (ll n = 0; n < PERIOD4; n++) {
        if (f0 == a % MOD4) cur.push_back(n);
        ll t = (f0 + f1) % MOD4;
        f0 = f1;
        f1 = t;
    }

    // 第 5..13 层：每层候选只可能来自上一层的 x + c*period（c=0..9）
    ll mod = MOD4, period = PERIOD4;
    while (!cur.empty() && mod < MOD13) {
        ll step = period;  // 上一层的周期，也是本层的扩散步长
        period *= 10;      // pi(10^k) 随 k 每增 1 扩大 10 倍
        mod *= 10;
        nxt.clear();
        for (size_t i = 0; i < cur.size(); i++) {
            for (int c = 0; c < 10; c++) {
                ll n = cur[i] + (ll)c * step;  // n < 1.5*10^13，ll 足够
                if (fib_mod(n, mod) == a % mod) nxt.push_back(n);
            }
        }
        cur.swap(nxt);
    }

    if (cur.empty()) {
        printf("-1\n");
    } else {
        ll best = cur[0];
        for (size_t i = 1; i < cur.size(); i++)
            if (cur[i] < best) best = cur[i];
        printf("%lld\n", best);
    }
    return 0;
}
