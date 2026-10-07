/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:31
 * update_at: 2026-10-05 23:31
 */

// 曹冲养猪：解两两互质模数下的同余方程组 x ≡ b_i (mod a_i)，输出最小正解。
// 做法：逐条合并剩余类（增量 CRT）。维护不变量 x = v + m*t，
// 新条件代入得 m*t ≡ b - v (mod a)，由互质性用扩展欧几里得求逆元解出 t。

#include <cstdio>

typedef long long ll;
typedef __int128 lll; // 合并模数 m = ∏a_i 最大可达 1000^10 ≈ 10^30，超出 long long，用 __int128

const int MAXN = 15;

int n;
ll a[MAXN]; // a[i]：第 i 次建猪圈的个数（模数）
ll b[MAXN]; // b[i]：第 i 次剩下没去处的猪数（余数）
lll v, m;   // 已合并条件等价于 x = v + m*t，v 是当前最小非负代表元

// 扩展欧几里得：求 a*x + b*y = gcd(a,b) 的一组解，返回 gcd(a,b)
lll exgcd(lll a, lll b, lll &x, lll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lll x1, y1;
    lll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// 并入一条新条件 x ≡ b_ (mod a_)：把 x = v + m*t 代入得 m*t ≡ b - v (mod a)
void merge_cong(ll a_, ll b_) {
    lll a = a_, b = b_;
    lll r = ((b - v) % a + a) % a; // b - v 可能为负，归一化到 [0, a)
    lll x, y;
    exgcd(m % a, a, x, y);     // a 两两互质 ⇒ gcd(m, a) = 1，逆元必存在
    lll inv = (x % a + a) % a; // m 在模 a 下的逆元
    lll t = r * inv % a;       // t ≡ (b - v) * m^{-1} (mod a)，在 [0, a) 内唯一
    v = v + m * t;             // 新的合并余数
    m = m * a;                 // 新的合并模数：这组条件的公共周期
}

// 输出 __int128
void print_lll(lll x) {
    if (x >= 10) print_lll(x / 10);
    int d = (int)(x % 10); // 每次取出的数字在 0..9，降到 int 输出
    putchar('0' + d);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld %lld", &a[i], &b[i]);
    v = 0;
    m = 1; // 无约束：x = 0 + 1*t 对一切 x 成立，是合并的单位元
    for (int i = 1; i <= n; i++) merge_cong(a[i], b[i]);
    if (v == 0) v = m; // 所有条件在 x=0 同时成立时取周期本身，保证输出正整数
    print_lll(v);
    putchar('\n');
    return 0;
}
