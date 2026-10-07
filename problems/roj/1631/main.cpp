/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:22
 * update_at: 2026-10-05 23:22
 */
// main.cpp：把相遇条件写成线性同余方程 (m-n)*t ≡ y-x (mod L)，用 exgcd 求最小非负解。

#include <cstdio>

typedef long long ll;

// 扩展欧几里得：返回 gcd(a, b)，并求出 x, y 使得 a*x + b*y = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1; // 回代：下层解 (x1, y1) 推出本层解
    return g;
}

ll x, y, m, n, L; // 题目输入：起点、步长、环长

int main() {
    scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L);

    // t 次跳跃后相遇 ⇔ x + m*t ≡ y + n*t (mod L) ⇔ (m-n)*t ≡ y-x (mod L)
    ll a = (m - n) % L; // 系数可能是负数，先归一化到 [0, L)
    if (a < 0) a += L;
    ll c = (y - x) % L; // 目标余数同样归一化到 [0, L)
    if (c < 0) c += L;

    ll s, k;
    ll g = exgcd(a, L, s, k); // a*s + L*k = g，即 a*s ≡ g (mod L)

    if (c % g != 0) { // g 不整除 c 时同余方程无解
        printf("Impossible\n");
        return 0;
    }

    // 两边同乘 c/g 得特解 t0 = s * (c/g)；全部解构成公差 L/g 的等差数列
    ll step = L / g;
    ll t = s % step * (c / g) % step; // 先取模防溢出，再归一化到最小非负解
    if (t < 0) t += step;
    printf("%lld\n", t);
    return 0;
}
