/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:11
 * update_at: 2026-10-06 18:11
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXF = 64;          // 一个数的不同质因子个数上限，远小于 64
const int MAXDIV = 100000;    // phi(m) 的因数个数上限，1.8e10 内最多几千个

ll fac_p[MAXF];               // 当前分解结果里的质因子
int fac_e[MAXF];              // 与 fac_p 对应的指数
int fac_cnt;                  // 当前分解结果里的不同质因子个数

ll divs[MAXDIV];              // phi(m) 的全部正因数，生成后排序
int div_cnt;

// 试除分解 n，结果写入 fac_p / fac_e，并把 fac_cnt 置为质因子个数。
void factorize(ll n) {
    fac_cnt = 0;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            fac_p[fac_cnt] = p;
            fac_e[fac_cnt] = e;
            fac_cnt++;
        }
    }
    if (n > 1) { // 剩下的 n 本身是质因子
        fac_p[fac_cnt] = n;
        fac_e[fac_cnt] = 1;
        fac_cnt++;
    }
}

// 用当前 fac_p / fac_e 计算欧拉函数 phi(n) = 乘积 (p-1) * p^(e-1)。
ll euler_phi() {
    ll phi = 1;
    for (int i = 0; i < fac_cnt; i++) {
        ll p = fac_p[i];
        int e = fac_e[i];
        for (int j = 0; j < e - 1; j++) {
            phi *= p;
        }
        phi *= (p - 1);
    }
    return phi;
}

// 递归展开当前 fac_p / fac_e 的全部正因数，存入 divs。
void gen_divisors(int idx, ll cur) {
    if (idx == fac_cnt) {
        divs[div_cnt] = cur;
        div_cnt++;
        return;
    }
    ll val = cur;
    for (int k = 0; k <= fac_e[idx]; k++) {
        gen_divisors(idx + 1, val);
        val *= fac_p[idx];
    }
}

// 计算 a * b % mod；m 可达 1.8e10，直接相乘会溢出 ll，所以借用 __int128。
ll mul_mod(ll a, ll b, ll mod) {
    __int128 t = (__int128)a * b; // 与 __int128 对接必须显式转换
    return (ll)(t % mod);
}

// 快速幂：返回 a^e % mod。
ll pow_mod(ll a, ll e, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) {
            res = mul_mod(res, a, mod);
        }
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

// 求 10 模 m 的乘法阶（调用前保证 gcd(10, m) = 1）。
// 阶整除 phi(m)，故在 phi(m) 的升序因数中取第一个使 10^d ≡ 1 的 d。
ll multiplicative_order(ll mod) {
    factorize(mod);
    ll phi = euler_phi();

    factorize(phi);
    div_cnt = 0;
    gen_divisors(0, 1);
    sort(divs, divs + div_cnt);

    for (int i = 0; i < div_cnt; i++) {
        if (pow_mod(10, divs[i], mod) == 1) {
            return divs[i];
        }
    }
    return phi;
}

// 返回 L 的最小全 8 倍数位数；不存在时返回 0。
ll smallest_lucky_length(ll L) {
    // n 位全 8 数 = 8(10^n-1)/9，于是 9L | 8(10^n-1)；
    // 约去 g = gcd(9L,8) = gcd(L,8) 后化为 10^n ≡ 1 (mod 9L/g)。
    ll m = 9 * L / gcd(L, 8LL);
    if (gcd(m, 10LL) != 1) { // m 含因子 2 或 5 时无解
        return 0;
    }
    return multiplicative_order(m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll L;
    int case_id = 0;
    while (cin >> L && L != 0) {
        case_id++;
        cout << "Case " << case_id << ": " << smallest_lucky_length(L) << "\n";
    }
    return 0;
}
