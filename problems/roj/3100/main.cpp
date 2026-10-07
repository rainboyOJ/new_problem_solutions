/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:43
 * update_at: 2026-10-06 18:43
 */

#include <cstdio>

typedef long long ll;

// 模数 a_i 两两互质，最终模数 M 最大约 6.2e60（61 位十进制），
// 超过 64 位范围，所以自己写一个 1e9 进制的简单大整数。
const int MAXL = 12;         // 12 个 1e9 进制位可存 108 位十进制，足够放下 M
const ll BASE = 1000000000LL;

struct Big {
    int len;                 // 有效位数
    ll d[MAXL];              // 低位在前，每位的基是 BASE
};

Big g_v;                     // 当前不变量 x ≡ g_v (mod g_m) 的余数
Big g_m;                     // 当前不变量的模数

// 大整数乘小数 k：把 x 就地乘上 k
void mul_small(Big &x, ll k) {
    ll carry = 0;
    for (int i = 0; i < x.len; i++) {
        ll cur = x.d[i] * k + carry;
        x.d[i] = cur % BASE;
        carry = cur / BASE;
    }
    while (carry > 0 && x.len < MAXL) {
        x.d[x.len] = carry % BASE;
        carry /= BASE;
        x.len++;
    }
    while (x.len > 1 && x.d[x.len - 1] == 0) x.len--;   // 去掉高位 0，保证表示唯一
}

// 大整数加法：x += y
void add_big(Big &x, const Big &y) {
    ll carry = 0;
    int n = x.len > y.len ? x.len : y.len;
    for (int i = 0; i < n; i++) {
        ll cur = carry;
        if (i < x.len) cur += x.d[i];
        if (i < y.len) cur += y.d[i];
        x.d[i] = cur % BASE;
        carry = cur / BASE;
    }
    x.len = n;
    if (carry > 0 && x.len < MAXL) {
        x.d[x.len] = carry;
        x.len++;
    }
    while (x.len > 1 && x.d[x.len - 1] == 0) x.len--;   // 去掉高位 0，保证表示唯一
}

// 大整数对小数 a 取模，返回 [0, a) 内的余数
ll mod_small(const Big &x, ll a) {
    if (a == 1) return 0;
    ll rem = 0;
    for (int i = x.len - 1; i >= 0; i--) {
        rem = (rem * BASE + x.d[i]) % a;
    }
    return rem;
}

// 扩展欧几里得：求 gcd(a, b) 以及一组解 a*x + b*y = gcd
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, x, y);
    ll nx = y;
    ll ny = x - (a / b) * y;
    x = nx;
    y = ny;
    return g;
}

// 求 a 在模 mod 下的逆元；mod = 1 时约定逆元为 0
ll mod_inverse(ll a, ll mod) {
    if (mod == 1) return 0;
    ll x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// 输出大整数（不带前导零）
void print_big(const Big &x) {
    printf("%lld", x.d[x.len - 1]);
    for (int i = x.len - 2; i >= 0; i--) {
        printf("%09lld", x.d[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    // 空约束的单位元：x ≡ 0 (mod 1) 对一切 x 成立
    g_v.len = 1;
    g_v.d[0] = 0;
    g_m.len = 1;
    g_m.d[0] = 1;

    for (int i = 1; i <= n; i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);

        // 已合并部分等价于 x = g_v + g_m * t，代入 x ≡ b (mod a)
        // 得 g_m * t ≡ b - g_v (mod a)，a_i 两两互质故 g_m 可逆
        ll v_mod_a = mod_small(g_v, a);
        ll m_mod_a = mod_small(g_m, a);
        ll inv = mod_inverse(m_mod_a, a);
        ll diff = ((b - v_mod_a) % a + a) % a;   // 归一化到 [0, a)
        ll t = diff * inv % a;

        // 合并：新模数 m*a，新余数 v + m*t（一定落在 [0, m*a) 内）
        Big mt = g_m;
        mul_small(mt, t);
        add_big(g_v, mt);
        mul_small(g_m, a);
    }

    // g_v 是 [0, g_m) 内的解；题目要求正整数，g_v = 0 时取最小正解 g_m
    if (g_v.len == 1 && g_v.d[0] == 0) {
        print_big(g_m);
    } else {
        print_big(g_v);
    }

    return 0;
}
