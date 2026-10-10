#include <cstdio>

typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 1000000007LL;
const int SZ = 4;

ll a1, a2, x, y;

// 状态向量 v = (a_n^2, a_n * a_{n-1}, a_{n-1}^2, S_n)，S_n = sum_{i=1}^{n} a_i^2
//   a_{n+1}^2   = x^2 * a_n^2 + 2xy * a_n a_{n-1} + y^2 * a_{n-1}^2
//   a_{n+1}a_n  = x   * a_n^2 + y   * a_n a_{n-1}
//   a_n^2       = a_n^2
//   S_{n+1}     = S_n + a_{n+1}^2
struct Mat {
    ll v[SZ][SZ];
};

Mat mul(const Mat &p, const Mat &q) {
    Mat r;
    for (int i = 0; i < SZ; i++)
        for (int j = 0; j < SZ; j++) {
            ull acc = 0; // 用 128 位安全的累加方式：每步取模
            for (int k = 0; k < SZ; k++)
                acc = (acc + (ull)(p.v[i][k] * q.v[k][j] % MOD)) % MOD;
            r.v[i][j] = (ll)acc;
        }
    return r;
}

Mat pow(Mat m, ll e) {
    Mat r;
    for (int i = 0; i < SZ; i++)
        for (int j = 0; j < SZ; j++)
            r.v[i][j] = (i == j);
    while (e > 0) {
        if (e & 1) r = mul(r, m);
        m = mul(m, m);
        e >>= 1;
    }
    return r;
}

ll sq(ll v) { return v % MOD * (v % MOD) % MOD; }

// 返回 sum_{i=1}^{n} a_i^2 mod MOD
ll solve_one(ll n) {
    if (n <= 0) return 0;
    if (n == 1) return sq(a1);
    if (n == 2) return (sq(a1) + sq(a2)) % MOD;
    // v_2 = (a2^2, a2 a1, a1^2, S_2)
    Mat T;
    ll xx = x % MOD, yy = y % MOD;
    T.v[0][0] = xx * xx % MOD; T.v[0][1] = 2 * xx % MOD * yy % MOD; T.v[0][2] = yy * yy % MOD; T.v[0][3] = 0;
    T.v[1][0] = xx;            T.v[1][1] = yy;                      T.v[1][2] = 0;            T.v[1][3] = 0;
    T.v[2][0] = 1;             T.v[2][1] = 0;                       T.v[2][2] = 0;            T.v[2][3] = 0;
    T.v[3][0] = T.v[0][0];     T.v[3][1] = T.v[0][1];               T.v[3][2] = T.v[0][2];    T.v[3][3] = 1;
    // ★ S_{n+1} = S_n + a_{n+1}^2，而 a_{n+1}^2 = T 第 0 行的线性组合
    //   ⇒ S 行 = (x², 2xy, y², 1)，不是 (0,0,0,1) —— 写成后者是本文件曾出过的 bug
    Mat P = pow(T, n - 2);
    ll a2m = a2 % MOD, a1m = a1 % MOD;
    ll v0 = a2m * a2m % MOD;
    ll v1 = a2m * a1m % MOD;
    ll v2 = a1m * a1m % MOD;
    ll v3 = (v0 + v2) % MOD; // S_2
    ll r0 = (ll)((ull)P.v[3][0] * v0 % MOD + (ull)P.v[3][1] * v1 % MOD + (ull)P.v[3][2] * v2 % MOD + (ull)P.v[3][3] * v3 % MOD) % MOD;
    return r0;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t-- > 0) {
        ll n;
        if (scanf("%lld %lld %lld %lld %lld", &n, &a1, &a2, &x, &y) != 5) break;
        printf("%lld\n", solve_one(n));
    }
    return 0;
}
