/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:22
 * update_at: 2026-10-05 05:22
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 3005;   // 顶点数上限（n <= 3000）
const int MAXM = 10005;  // 边数上限（m <= 10^4）
const double INF = 1e18; // 不可达哨兵：真实行走权值和至多 3*10^10，远小于此

int n, m;
int eu[MAXM], ev[MAXM]; // 每条有向边的起点、终点（下标从 1 开始）
double ew[MAXM];        // 每条边的权值（题目允许实数，如样例 2 的 -2.9）

// Karp 递推表：F[j][v] = 恰好走 j 条边、以 v 结尾的最小权行走（起点任取）
double F[MAXN][MAXN];

// 逐行递推 F 表：F[0][v] = 0 相当于超级源点向所有点连 0 权边，起点维度被折叠
void karp_dp() {
    for (int v = 1; v <= n; ++v) F[0][v] = 0;
    for (int j = 1; j <= n; ++j) {
        for (int v = 1; v <= n; ++v) F[j][v] = INF;
        for (int e = 1; e <= m; ++e) {
            int u = eu[e], v = ev[e];
            if (F[j - 1][u] >= INF / 2) continue; // 上一行不可达，不参与松弛
            double x = F[j - 1][u] + ew[e];
            if (x < F[j][v]) F[j][v] = x;
        }
    }
}

// Karp 定理：mu* = min_v max_k (F[n][v] - F[k][v]) / (n - k)
// 分数扫描用 long double：分子至多 6*10^10，long double 的精度保证
// 两个候选分数（间隔至少 1/(d1*d2) >= 1.1*10^-7）的比较不会误序
long double karp_answer() {
    long double ans = 1e18L;
    for (int v = 1; v <= n; ++v) {
        if (F[n][v] >= INF / 2) continue; // 没有长度恰为 n 的行走到达 v，跳过
        long double best = -1e18L;
        for (int k = 0; k < n; ++k) {
            long double fn = F[n][v];
            long double fk = F[k][v];
            long double q = (fn - fk) / (n - k); // 候选分数；F[k][v]=INF 时极小，不会当选
            if (q > best) best = q;
        }
        if (best < ans) ans = best;
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int e = 1; e <= m; ++e) {
        scanf("%d %d %lf", &eu[e], &ev[e], &ew[e]);
    }
    karp_dp();
    long double ans = karp_answer();
    printf("%.8Lf\n", ans);
    return 0;
}
