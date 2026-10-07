/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-02-14 09:30
 * update_at: 2026-02-14 09:30
 */
// 一本通 1806「计算器」：三个数论子问题合在一份程序里。
//   type 1: y^z mod P                    —— 快速幂           O(log z)
//   type 2: y^x ≡ z (mod P) 的最小非负 x —— 扩展 BSGS        O(sqrt(P))
//   type 3: C(z,y) mod P                 —— 扩展 Lucas + CRT O(sum p_i^a_i * log)
// 题面保证 P 为合数时每个质因数幂 p_i^a_i ≤ 1e5，所以 exLucas 的前缀积表很短；
// 质数 P 走 Lucas 定理（逐位直接算小组合数），不需要开 O(P) 的表。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll PK_LIMIT = 1000000; // 前缀积表规模上限（合数的 p^a 按题面保证 ≤ 1e5）

ll pre[PK_LIMIT + 1]; // pre[i] = ∏_{1≤j≤i, p∤j} j mod p^a，只为当前的 (p, p^a) 重建

// 快速幂：返回 a^b mod m
ll qpow(ll a, ll b, ll m) {
    if (m == 1) return 0;
    a %= m;
    ll res = 1 % m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// 扩展欧几里得：返回 gcd(a,b)，并顺带解出 a*x + b*y = gcd(a,b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 求 a 在模 m 下的逆元，要求 gcd(a,m)=1 且 m ≥ 2
ll inv_mod(ll a, ll m) {
    ll x, y;
    exgcd(a % m, m, x, y);
    return ((x % m) + m) % m;
}

/* ---------------- type 1：快速幂 ---------------- */

ll solve_pow(ll y, ll z, ll P) { return qpow(y, z, P); }

/* ---------------- type 2：扩展 BSGS ---------------- */

struct BabyStep {
    ll val; // 值 z * y^j mod p
    ll j;   // 对应的指数 j；同一 val 下保留最大的 j，才能让 x = i*m - j 最小
};

vector<BabyStep> baby; // 小步表：排序后二分查找

bool baby_cmp(const BabyStep &u, const BabyStep &v) {
    if (u.val != v.val) return u.val < v.val;
    return u.j < v.j; // 同值按 j 升序，方便把每段的最大 j 传播给整段
}

// 求 a^x ≡ b (mod p) 的最小非负整数 x，无解返回 -1
ll exbsgs(ll a, ll b, ll p) {
    a %= p;
    b %= p;
    if (p == 1) return 0; // 模 1 时一切同余都成立，最小 x = 0
    if (b == 1) return 0; // a^0 = 1
    // 第一步：消去 gcd(a,p) 的公共因子，把问题化为 gcd(a,p)=1 的情形。
    // 若 d = gcd(a,p)，则 d | a^x 必须 d | b，否则无解；两边同除 d 后
    // p ← p/d, b ← b/d, k ← k*(a/d)（k 是"已经提出来的那部分系数"）。
    ll cnt = 0;
    ll k = 1;
    ll d = __gcd(a, p);
    while (d != 1) {
        if (b % d != 0) return -1;
        b /= d;
        p /= d;
        k = k * (a / d) % p;
        cnt++;
        if (b == k) return cnt; // x = cnt 时 k*a^0 ≡ b 已成立，且 cnt 是最小的
        d = __gcd(a, p);
    }
    if (p == 1) return cnt; // 化到模 1：任何 x ≥ cnt 都是解，最小取 cnt
    // 第二步：标准 BSGS。设 x - cnt = y = i*m - j，则 k*(a^m)^i ≡ b*a^j (mod p)。
    ll m = (ll)ceil(sqrt((double)p)) + 1;
    baby.clear();
    baby.reserve((size_t)m + 1);
    ll cur = b;
    for (ll j = 0; j <= m; j++) {
        baby.push_back(BabyStep{cur, j});
        cur = cur * a % p;
    }
    sort(baby.begin(), baby.end(), baby_cmp);
    ll sz = (ll)baby.size();
    for (ll i = sz - 2; i >= 0; i--) { // 同值段内把最大的 j 向后传播
        if (baby[i].val == baby[i + 1].val) baby[i].j = baby[i + 1].j;
    }
    ll base = qpow(a, m, p);
    cur = k;
    for (ll i = 1; i <= m; i++) {
        cur = cur * base % p;
        ll lo = 0, hi = sz - 1, pos = -1;
        while (lo <= hi) {
            ll mid = (lo + hi) >> 1;
            if (baby[mid].val == cur) {
                pos = mid;
                break;
            }
            if (baby[mid].val < cur) lo = mid + 1;
            else hi = mid - 1;
        }
        if (pos >= 0) return i * m - baby[pos].j + cnt;
    }
    return -1;
}

/* ---------------- type 3：扩展 Lucas ---------------- */

// 建立前缀积表：pre[i] = ∏_{1≤j≤i, p∤j} j mod p^a（pre[0] 是空积 1）
void build_table(ll p, ll pk) {
    pre[0] = 1 % pk;
    for (ll i = 1; i <= pk; i++) {
        ll v = (i % p == 0) ? 1 : i; // 跳过 p 的倍数（它的 p 因子由 count_p_in_fact 单独统计）
        pre[i] = pre[i - 1] * v % pk;
    }
}

// n! 剔除全部质因子 p 之后模 p^a 的值（有前缀积表版本）
ll fac_without_p(ll n, ll p, ll pk) {
    ll res = 1;
    while (n > 0) {
        res = res * qpow(pre[pk], n / pk, pk) % pk; // 完整周期的重复部分
        res = res * pre[n % pk] % pk;               // 不完整周期
        n /= p;                                     // 递归处理 ⌊n/p⌋!
    }
    return res;
}

// n! 剔除全部质因子 p 之后模 p^a 的值（无表兜底，O(p^a) 每次；题面保证用不到）
ll fac_without_p_slow(ll n, ll p, ll pk) {
    if (n == 0) return 1;
    ll cycle = 1;
    for (ll i = 1; i <= pk; i++)
        if (i % p != 0) cycle = cycle * i % pk; // 一个完整周期的乘积
    ll res = qpow(cycle, n / pk, pk);
    for (ll i = 1; i <= n % pk; i++)
        if (i % p != 0) res = res * i % pk;
    return res * fac_without_p_slow(n / p, p, pk) % pk;
}

// n! 中质因子 p 的个数（Legendre 公式）
ll count_p_in_fact(ll n, ll p) {
    ll s = 0;
    while (n > 0) {
        n /= p;
        s += n;
    }
    return s;
}

// C(n,m) mod p^a（p 为质数，p^a 为模数）；调用前若 p^a ≤ PK_LIMIT 需先 build_table
ll comb_mod_prime_power(ll n, ll m, ll p, ll pk) {
    if (m < 0 || m > n) return 0;
    ll e = count_p_in_fact(n, p) - count_p_in_fact(m, p) - count_p_in_fact(n - m, p);
    if (e < 0) return 0;
    if (qpow(p, e, pk) == 0) return 0; // e ≥ a 时组合数被 p^a 整除，余 0
    ll res = qpow(p, e, pk);
    if (pk <= PK_LIMIT) {
        res = res * fac_without_p(n, p, pk) % pk;
        res = res * inv_mod(fac_without_p(m, p, pk), pk) % pk;
        res = res * inv_mod(fac_without_p(n - m, p, pk), pk) % pk;
    } else {
        res = res * fac_without_p_slow(n, p, pk) % pk;
        res = res * inv_mod(fac_without_p_slow(m, p, pk), pk) % pk;
        res = res * inv_mod(fac_without_p_slow(n - m, p, pk), pk) % pk;
    }
    return res;
}

// C(n,m) mod p（p 为质数），Lucas 定理 + 逐位直接算小组合数
ll lucas_prime(ll n, ll m, ll p) {
    if (m < 0 || m > n) return 0;
    ll res = 1;
    while (n > 0 || m > 0) {
        ll a = n % p;
        ll b = m % p;
        if (b > a) return 0;   // 该位上 C(a,b) = 0，整体为 0
        ll bb = min(b, a - b); // 用对称性少乘一半
        ll num = 1, den = 1;
        for (ll j = 1; j <= bb; j++) {
            num = num * ((a - bb + j) % p) % p;
            den = den * (j % p) % p;
        }
        res = res * num % p;
        if (den != 1) res = res * qpow(den, p - 2, p) % p; // p 是质数，费马小定理求逆元
        n /= p;
        m /= p;
    }
    return res;
}

struct PrimePower {
    ll p;  // 质因子
    ll pk; // 对应的幂 p^a
};

// C(z,y) mod P，P 不保证是质数（C(z,y) 表示 z 中取 y）
ll solve_comb(ll y, ll z, ll P) {
    ll n = z, m = y;
    if (P == 1) return 0;        // 模 1 恒为 0
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1 % P;
    // 分解 P = ∏ p_i^a_i
    PrimePower fac[64]; // 1e9 内的不同质因子最多 9 个，64 足够
    ll fac_cnt = 0;
    ll tmp = P;
    for (ll d = 2; d * d <= tmp; d++) {
        if (tmp % d == 0) {
            ll pk = 1;
            while (tmp % d == 0) {
                tmp /= d;
                pk *= d;
            }
            fac[fac_cnt].p = d;
            fac[fac_cnt].pk = pk;
            fac_cnt++;
        }
    }
    if (tmp > 1) {
        fac[fac_cnt].p = tmp;
        fac[fac_cnt].pk = tmp;
        fac_cnt++;
    }
    if (fac_cnt == 1 && fac[0].p == P) return lucas_prime(n, m, P); // P 本身是质数
    // 一般情形：每个质数幂算一个余数，再用 CRT 合并（各 p_i^a_i 两两互质）
    ll x = 0, M = 1;
    for (ll i = 0; i < fac_cnt; i++) {
        ll p = fac[i].p, pk = fac[i].pk;
        if (pk <= PK_LIMIT) build_table(p, pk);
        ll r = comb_mod_prime_power(n, m, p, pk);
        ll t = ((r - x) % pk + pk) % pk * inv_mod(M % pk, pk) % pk;
        x = (x + M * t) % (M * pk); // 把 x ≡ r (mod pk) 合并到当前模 M 上
        M *= pk;
    }
    return x;
}

/* ---------------- main ---------------- */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    if (!(cin >> N)) return 0;
    string out;
    out.reserve((size_t)N * 12);
    while (N--) {
        ll op, y, z, P;
        cin >> op >> y >> z >> P;
        if (op == 1) {
            out += to_string(solve_pow(y, z, P));
        } else if (op == 2) {
            ll r = exbsgs(y, z, P);
            if (r < 0) out += "Math Error";
            else out += to_string(r);
        } else {
            out += to_string(solve_comb(y, z, P));
        }
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
