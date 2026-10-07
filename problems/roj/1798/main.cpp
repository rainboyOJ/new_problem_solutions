/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:50
 * update_at: 2026-10-08 03:50
 */
// main.cpp：递推数列 f(i) = (a*f(i-1)+b) / (c*f(i-1)+d) (mod p)，求 f(n)。
// 把分式线性变换看作莫比乌斯变换，用齐次坐标 (分子 x, 分母 y) 转成 2x2 矩阵的幂：
//   (x_i, y_i)^T = [[a,b],[c,d]]^i (x_0, y_0)^T,  f(i) = x_i * inv(y_i)。
// n 达 1e18，用矩阵快速幂 O(log n)；逆元用扩展欧几里得（p 不保证是素数）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT = 10000 + 5; // 数据组数上界，本题不需要存下来，仅作规模备注

ll p;                 // 当前这组数据的模数
ll f0, a, b, c, d;    // 当前这组数据的初值与四个系数
ll n;                 // 当前这组数据要求的目标下标

// 把任意整数规范到 [0, p)，系数可能为负（题面 0<=|x|<p）
static inline ll norm(ll x) {
    x %= p;
    if (x < 0) x += p;
    return x;
}

// 2x2 矩阵：模 p 意义下的幺半群
struct Mat {
    ll m[2][2];
};

// 矩阵乘法，p<=1e9<2^30，单项乘积 <2^60，两项求和 <2^61，long long 不溢出
static Mat mul(const Mat &A, const Mat &B) {
    Mat C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ll s = (A.m[i][0] * B.m[0][j] + A.m[i][1] * B.m[1][j]) % p;
            C.m[i][j] = s;
        }
    }
    return C;
}

// 矩阵快速幂：返回 M^e（e 用 unsigned long long，n<=1e18 也在范围内）
static Mat mpow(Mat M, unsigned long long e) {
    Mat R;                       // 单位矩阵
    R.m[0][0] = 1; R.m[0][1] = 0;
    R.m[1][0] = 0; R.m[1][1] = 1;
    while (e) {
        if (e & 1ULL) R = mul(R, M);
        M = mul(M, M);
        e >>= 1;
    }
    return R;
}

// 扩展欧几里得：返回 gcd(x,y)=1 时 x 的逆元（不要求模数是素数）
static ll exgcd(ll x, ll y, ll &g, ll &h) {
    if (y == 0) { g = 1; h = 0; return x; }
    ll r = exgcd(y, x % y, h, g);
    h -= (x / y) * g;
    return r;
}

// 求 a 在模 p 下的逆元，题面保证 gcd(a,p)=1
static ll inv(ll x) {
    ll g, h;
    exgcd(norm(x), p, g, h);
    return norm(g);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int tc = 0; tc < t; tc++) {
        scanf("%lld %lld %lld %lld %lld %lld %lld", &f0, &a, &b, &c, &d, &n, &p);
        f0 = norm(f0); a = norm(a); b = norm(b); c = norm(c); d = norm(d);
        if (n == 0) {            // 0 次迭代，答案就是规范化的 f(0)
            printf("%lld\n", f0);
            continue;
        }
        Mat M;
        M.m[0][0] = a; M.m[0][1] = b;
        M.m[1][0] = c; M.m[1][1] = d;
        Mat R = mpow(M, (unsigned long long)n);
        // (x_n, y_n) = M^n * (f0, 1)^T
        ll x = (R.m[0][0] * f0 + R.m[0][1]) % p;
        ll y = (R.m[1][0] * f0 + R.m[1][1]) % p;
        printf("%lld\n", x * inv(y) % p);
    }
    return 0;
}
