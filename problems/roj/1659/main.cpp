/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:04
 * update_at: 2026-10-06 01:04
 */
#include <iostream>
#include <utility>
using namespace std;

typedef long long ll;

// 扩展 Lucas（exLucas）：组合数模合数 P。
// 思路：把 P 分解为质因数幂 p^k，在每条 C(n,m) mod p^k 上分别求值，
// 再用中国剩余定理拼回模 P 的答案。

const int MAXF = 40; // P <= 1e9，不同质因数不超过 10 个，40 足够

ll P;
ll n, m;
ll weight[10]; // weight[i] 表示第 i 个人至少要收到的礼物数

ll prime_arr[MAXF]; // 每个质因数 p
ll pow_arr[MAXF];   // 对应的 p^k
ll rest_arr[MAXF];  // 当前答案在模 p^k 下的余数
int fac_cnt;        // P 的质因数个数

// 求 a 在模 mod 下的逆元，保证 gcd(a, mod) = 1。
ll mod_inv(ll a, ll mod) {
    ll b = mod;
    ll u = 1, v = 0; // u 记录 a 的系数，v 记录 mod 的系数
    // 迭代扩展欧几里得，避免递归
    while (b != 0) {
        ll q = a / b;
        a -= q * b;
        swap(a, b);
        u -= q * v;
        swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

// 快速幂：base^exp mod mod。
ll pow_mod(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 计算 n! 抽掉所有 p 因子后得到的数模 pk（pk = p^k）。
// 按 pk 分块：一个完整块 [1..pk] 内与 p 互素的数乘积固定，可整体幂；
// 零头单独乘；再递归处理 n! 中每隔 p 个数的一层，其乘积对应 (n/p)!。
ll fact_pfree(ll n, ll p, ll pk) {
    if (n == 0) return 1 % pk;
    ll block = 1;
    for (ll i = 1; i <= pk; i++) {
        if (i % p != 0) block = block * i % pk;
    }
    ll res = pow_mod(block, n / pk, pk);
    for (ll i = 1; i <= n % pk; i++) {
        if (i % p != 0) res = res * i % pk;
    }
    return res * fact_pfree(n / p, p, pk) % pk;
}

// 计算 C(n, m) mod pk（pk = p^k）。
ll small_comb(ll n, ll m, ll p, ll pk) {
    if (m < 0 || m > n) return 0;

    // 勒让德公式：求 C(n,m) 中 p 的总指数 e = v_p(n!) - v_p(m!) - v_p((n-m)!)
    ll e = 0;
    ll x = n;
    while (x > 0) {
        x /= p;
        e += x;
    }
    x = m;
    while (x > 0) {
        x /= p;
        e -= x;
    }
    x = n - m;
    while (x > 0) {
        x /= p;
        e -= x;
    }

    // 求 pk 中 p 的指数 k，若 e >= k 则结果已是 pk 的倍数
    ll k = 0;
    ll t = pk;
    while (t % p == 0) {
        t /= p;
        k++;
    }
    if (e >= k) return 0;

    // p-free 部分用逆元做除法
    ll unit = fact_pfree(n, p, pk);
    unit = unit * mod_inv(fact_pfree(m, p, pk), pk) % pk;
    unit = unit * mod_inv(fact_pfree(n - m, p, pk), pk) % pk;
    return pow_mod(p, e, pk) * unit % pk;
}

// 把 P 分解为质因数幂，结果存入 prime_arr / pow_arr。
void factorize(ll x) {
    fac_cnt = 0;
    for (ll d = 2; d * d <= x; d++) {
        if (x % d == 0) {
            ll pk = 1;
            while (x % d == 0) {
                x /= d;
                pk *= d;
            }
            prime_arr[fac_cnt] = d;
            pow_arr[fac_cnt] = pk;
            fac_cnt++;
        }
    }
    if (x > 1) {
        prime_arr[fac_cnt] = x;
        pow_arr[fac_cnt] = x;
        fac_cnt++;
    }
}

// 中国剩余定理：模数两两互素，逐个合并余数方程，返回模 ∏pow_arr 下的解。
ll crt_solve(int cnt) {
    ll res = 0;
    ll M = 1;
    for (int i = 0; i < cnt; i++) {
        ll a = rest_arr[i];
        ll q = pow_arr[i];
        ll diff = ((a - res) % q + q) % q;
        ll step = diff * mod_inv(M % q, q) % q;
        res += step * M;
        M *= q;
    }
    return res % M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> P;
    cin >> n >> m;
    ll sum_w = 0;
    for (int i = 1; i <= m; i++) {
        cin >> weight[i];
        sum_w += weight[i];
    }

    if (sum_w > n) {
        cout << "Impossible" << '\n';
        return 0;
    }

    // 先分解模数，再在每条组合数上分别对 p^k 取模
    factorize(P);
    for (int i = 0; i < fac_cnt; i++) {
        rest_arr[i] = 1 % pow_arr[i];
    }

    // 依次给第 i 个人从剩余礼物中选 weight[i] 件，方案数相乘
    ll remain = n;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < fac_cnt; j++) {
            ll c = small_comb(remain, weight[i], prime_arr[j], pow_arr[j]);
            rest_arr[j] = rest_arr[j] * c % pow_arr[j];
        }
        remain -= weight[i];
    }

    if (fac_cnt == 0) {
        // P = 1 时任何数都同余于 0
        cout << 0 << '\n';
        return 0;
    }

    cout << crt_solve(fac_cnt) % P << '\n';
    return 0;
}
