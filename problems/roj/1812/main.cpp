/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:12
 * update_at: 2026-10-08 06:12
 */
// 1812《网格》正解
// 题意：网格 [0,W]x[0,H] 的 (W+1)(H+1) 个格点里选 N 个互不相同的点，要求它们共线，
//       并且沿这条直线相邻两点的欧氏距离 >= D，求方案数 mod 1e9。
// 做法：按直线的“本原方向”分类计数。方向 (1,0)、(0,1) 各算一次；斜率 +b 与 -b 关于
//       y 轴对称、方案数相同，所以 a,b>=1 的部分算好后乘 2。
//       固定本原方向 (a,b) 后，直线上的格点按 (a,b) 等距排开，相邻格点距离为
//       sqrt(a^2+b^2)，于是“相邻距离 >= D”等价于“指标差 >= K”，
//       K = 最小的正整数使 K^2*(a^2+b^2) >= D^2（用整数平方判定，不用 sqrt）。
//       设首末两点的指标跨度 M：把 M 拆成 N-1 段、每段 >= K 的方案数是
//       C(M-(N-1)K+N-2, N-2)；首点 p 的取法数为 (W+1-M*a)*(H+1-M*b)。
//       对所有 M 累加即该方向贡献。N=1 时答案直接是格点数。
// 说明：模数 1e9 不是质数，组合数只能用杨辉三角递推，不能用逆元。
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll MOD = 1000000000LL; // 题面模数，非质数，不能靠费马小定理求逆元
const int MAX_UP = 560;      // 组合数上标上限：M <= W <= 500，再加 N-2 <= 48
const int MAX_LO = 50;       // 组合数下标上限：N-2 <= 48

ll comb_tab[MAX_UP + 1][MAX_LO + 1]; // comb_tab[i][j] = C(i,j) mod 1e9（杨辉三角）

// 手写 gcd，避免 __gcd（libstdc++ 专有）在其它标准库下不可用
ll gcd_ll(ll x, ll y) {
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

// 本原方向 (a,b)（a,b >= 0 且不同时为 0）贡献的方案数，不含斜率正负对称的 2 倍。
ll count_direction(ll a, ll b, ll n, ll w, ll h, ll d2) {
    ll s2 = a * a + b * b;         // 方向向量长度的平方
    ll k = 1;
    while (k * k * s2 < d2) k++;   // 最小步长（整数判定，避开浮点误差）
    ll base = (n - 1) * k;         // 首末点跨度 M 的下界：N-1 段每段至少 k
    ll max_m = base - 1;           // 上界先给一个必然空集的值
    if (a == 0) max_m = h / b;     // 纯竖直方向，只受 y 跨度限制
    else if (b == 0) max_m = w / a; // 纯水平方向，只受 x 跨度限制
    else max_m = min(w / a, h / b);
    ll res = 0;
    for (ll m = base; m <= max_m; m++) {
        // 把跨度 m 拆成 N-1 段（每段 >= k）的方案数，乘首点可选位置数
        ll ways = comb_tab[m - base + (n - 2)][n - 2];
        res = (res + ways * (w + 1 - m * a) % MOD * (h + 1 - m * b)) % MOD;
    }
    return res;
}

int main() {
    for (int i = 0; i <= MAX_UP; i++) { // 杨辉三角预处理组合数
        comb_tab[i][0] = 1;
        for (int j = 1; j <= min(i, MAX_LO); j++)
            comb_tab[i][j] = (comb_tab[i - 1][j - 1] + comb_tab[i - 1][j]) % MOD;
    }
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        ll n, w, h, d;
        scanf("%lld %lld %lld %lld", &n, &w, &h, &d);
        if (n == 1) { // 只选一个点：任取一个格点
            printf("%lld\n", (w + 1) * (h + 1) % MOD);
            continue;
        }
        ll d2 = d * d;
        ll ans = count_direction(1, 0, n, w, h, d2) + count_direction(0, 1, n, w, h, d2);
        ll span = n - 1; // 斜向要有解必须 M >= span，于是 a <= w/span、b <= h/span
        for (ll a = 1; a <= w / span; a++)
            for (ll b = 1; b <= h / span; b++)
                if (gcd_ll(a, b) == 1) // 只取本原方向，避免同一斜率重复计数
                    ans = (ans + 2 * count_direction(a, b, n, w, h, d2)) % MOD;
        printf("%lld\n", ans % MOD);
    }
    return 0;
}
