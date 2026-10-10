/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:16
 * update_at: 2026-10-08 06:16
 */
/*
 * 一本通 1814 「方格染色」 —— 期望的线性性 + 二项式展开，O(n^2)
 *
 * 记 r 为被整行涂黑的行数，c 为被整列涂黑的列数，要求 E[2^(r+c)]。
 * 关键恒等式：2^(r+c) = (1+1)^r * (1+1)^c = Σ_{R⊆黑行} Σ_{C⊆黑列} 1，
 * 即 "得分" 等于 "黑行集合的子集数 × 黑列集合的子集数"。
 * 于是取期望后可以直接枚举 "指定的 i 行 j 列全黑" 这一事件，绕开容斥：
 *
 *     E = Σ_{i=0..n} Σ_{j=0..n} C(n,i)·C(n,j)·P(指定的 i 行 j 列全黑)
 *
 * 这 i 行 j 列覆盖的格子数为 t = n·i + n·j − i·j（行并列的并集），
 * 指定 t 个格子的取值构成 [m] 的均匀 t-子集，全黑等价于它落在选出的 k 个数里：
 *
 *     P(t) = C(m−t, k−t)/C(m,k) = Π_{p=0..t−1} (k−p)/(m−p)，t > k 时 P(t) = 0
 *
 * 数值注意：C(300,150) ≈ 9.4e88 远超 long long，所以组合数与概率全程用 double；
 * double 上限 1.7e308，单项最大约 9.4e88 × 9.4e88 × 1 ≈ 8.8e177，不会溢出。
 * P(t) 在连乘中下溢成 0 时，该项 < 1e-130，远小于答案下界 1，可以安全忽略。
 */
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 305;    // n ≤ 300，多开一点留余量
const int MAXT = 90005;  // 覆盖格子数 t ≤ n^2 ≤ 90000

double comb[MAXN][MAXN]; // comb[i][j] = C(i,j)，帕斯卡三角形（double 存储，不会溢出）
double prob[MAXT];       // prob[t] = P(指定的 t 个格子全黑)，题面要求 t ≤ m

int main() {
    ll n, m, k;
    if (scanf("%lld %lld %lld", &n, &m, &k) != 3) return 1;

    // comb 用 Pascal 递推：C(i,j) = C(i-1,j-1) + C(i-1,j)
    for (ll i = 0; i <= n; i++) {
        comb[i][0] = 1.0;
        for (ll j = 1; j <= i; j++)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }

    // prob[t] = Π_{p=0..t-1} (k-p)/(m-p)；t > k 时选不出这么多数，概率为 0
    ll tmax = std::min(n * n, k);
    prob[0] = 1.0;
    for (ll t = 1; t <= tmax; t++)
        prob[t] = prob[t - 1] * (double)(k - t + 1) / (double)(m - t + 1);

    double sum = 0.0;
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= n; j++) {
            ll t = n * i + n * j - i * j; // 指定 i 行 j 列覆盖的格子数
            if (t > k) continue;          // 概率为 0，直接跳过
            sum += comb[n][i] * comb[n][j] * prob[t];
        }
    }

    if (sum > 1e99) sum = 1e99; // 题面要求答案超过 1e99 时输出 1e99
    printf("%.10e\n", sum);
    return 0;
}
