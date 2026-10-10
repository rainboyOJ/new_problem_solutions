/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:35
 * update_at: 2026-10-08 03:35
 */
// 一本通 1795《散步》：数轴上从 0 出发，n 步每步 ±1，每段离家的连续时间 <= m，
// 第 n 步恰好回到家，求方案数 mod 1e9+7。2<=n<=1e9，2<=m<=100，n、m 均为偶数。
//
// 把「每次回家」当作一次分界，整条路径唯一拆成若干段「远足」（起点终点为 0、
// 中途坐标不为 0）。长为 2j 的远足数 = 2*Catalan(j-1)：首步 ±1 定符号，
// 中间 2j-2 步是平移后的非负走法。
// 记 h(t) = 走 2t 步恰好回家的合法方案数，d = m/2，则
//     h(0) = 1,  h(t) = sum_{j=1..d} c_j * h(t-j),  c_j = 2*Catalan(j-1)。
// 这是 d (<=50) 阶常系数线性递推，用伴随矩阵快速幂求第 N = n/2 项。

#include <cstdio>
#include <cstring>

typedef long long ll;

const ll MOD = 1000000007LL;
const int MAXD = 55;   // m <= 100 时阶数 d = m/2 <= 50，留一点余量

int d;                 // 递推阶数 d = m/2
ll coef[MAXD];         // coef[j] = 长为 2(j+1) 的远足方案数 = 2*Catalan(j)
ll fact[2 * MAXD + 5];      // 阶乘表，最大用到 (2d)!
ll inv_fact[2 * MAXD + 5];  // 阶乘的逆元表，配合费马小定理求组合数

struct Mat {
    ll a[MAXD][MAXD];
    Mat() { memset(a, 0, sizeof(a)); }
};

// 矩阵乘法，全部 64 位并即时取模，避免中间乘积溢出
Mat mul(const Mat &x, const Mat &y) {
    Mat r;
    for (int i = 0; i < d; i++) {
        for (int k = 0; k < d; k++) {
            if (x.a[i][k] == 0) continue;      // 稀疏时直接跳过，省一半常数
            ll v = x.a[i][k];
            for (int j = 0; j < d; j++) {
                r.a[i][j] = (r.a[i][j] + v * y.a[k][j]) % MOD;
            }
        }
    }
    return r;
}

Mat mpow(Mat base, ll e) {
    Mat r;
    for (int i = 0; i < d; i++) r.a[i][i] = 1;  // 单位矩阵
    while (e > 0) {
        if (e & 1) r = mul(r, base);
        base = mul(base, base);
        e >>= 1;
    }
    return r;
}

ll qpow(ll a, ll b) {
    ll r = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0;
    d = m / 2;                     // m <= 100，故 d <= 50，int 足够

    // Catalan(j) = (2j)! / (j! (j+1)!)，j 最大取到 d-1，故阶乘只需到 2d
    int lim = 2 * d;
    fact[0] = 1;
    for (int i = 1; i <= lim; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[lim] = qpow(fact[lim], MOD - 2);
    for (int i = lim; i >= 1; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;

    for (int j = 0; j < d; j++) {
        ll cat = fact[2 * j] * inv_fact[j] % MOD * inv_fact[j + 1] % MOD;
        coef[j] = 2 * cat % MOD;
    }

    // 伴随矩阵：第一行放递推系数，次对角线全为 1
    Mat A;
    for (int j = 0; j < d; j++) A.a[0][j] = coef[j];
    for (int i = 1; i < d; i++) A.a[i][i - 1] = 1;

    // 初始状态 [h(0), h(-1), ..., h(1-d)] = [1, 0, ..., 0]，
    // 于是 h(N) = (A^N)[0][0]，无需单独构造初始向量。
    ll t = n / 2;
    Mat P = mpow(A, t);
    printf("%lld\n", P.a[0][0] % MOD);
    return 0;
}
