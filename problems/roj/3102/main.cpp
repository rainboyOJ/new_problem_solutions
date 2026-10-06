/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:57
 * update_at: 2026-10-06 18:57
 */

// 概率 DP：状态 = (成功数截到 L, 净余量截到 [-m, m])，
// m 为残片总数，净余量 t = 初始容量 + 成功获得的包容量 - 已得残片数。
// 一次挑战失败：状态原地不动，概率乘 (1-p)；
// 成功：成功数 +1（第 L 档封顶），净余量按 a_i 平移（残片左移 1，包右移 a_i），
// 越过 [-m, m] 边界的概率全部截到边界格（截断不改变最终 t >= 0 的真假）。
// 答案 = 第 L 行中净余量 >= 0 各格概率之和。复杂度 O(N * L * m)。
#include <cstdio>

typedef long long ll;

const int MAXN = 205;
const int MAXT = 405; // 净余量列数最多 2m+1 <= 2N+1

int n;          // 挑战数
ll need;        // 至少要成功的次数 L
ll frag;        // 残片总数 m（a_i = -1 的项数）
ll init_cap;    // 初始包容量 K
double p[MAXN]; // 每项挑战成功的概率（已除以 100）
ll a[MAXN];     // 每项挑战的属性值

// dp[j][t + m]：成功数（截到 L）为 j、净余量（截到 [-m, m]）为 t 的累计概率，
// 列下标整体平移 m 保证非负；滚动时用 cur/newcur 两层
double dp[MAXN][MAXT];
double ndp[MAXN][MAXT];

int span; // 列数 = 2m+1
int top;  // 列下标上限 = span-1（对应净余量 +m）
int base; // 净余量 0 对应的列下标 = m

int main() {
    scanf("%d %lld %lld", &n, &need, &init_cap);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
        p[i] /= 100.0; // 题面给的是百分数
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        if (a[i] == -1) frag++; // 统计残片总数 m
    }

    span = 2 * frag + 1;
    top = span - 1;
    base = frag;

    // 初始状态：0 次成功，净余量 = K（同样先截到 +m）
    dp[0][init_cap > frag ? top : init_cap + base] = 1.0;

    // 逐项做概率转移
    for (int i = 1; i <= n; i++) {
        // 前 i 项最多成功 min(i, L) 次，更高的档恒为 0，直接清零
        ll reach = need < i ? need : i;
        for (ll j = 0; j <= reach; j++)
            for (int t = 0; t < span; t++)
                ndp[j][t] = 0.0;

        for (ll j = 0; j <= reach; j++) {
            for (int t = 0; t < span; t++) {
                double cur = dp[j][t];
                if (cur == 0.0) continue;
                // 失败分支：状态原地不动
                ndp[j][t] += cur * (1.0 - p[i]);
                // 成功分支：成功数 +1（封顶在第 L 档），净余量平移
                ll nj = j + 1 < need + 1 ? j + 1 : need;
                int nt;
                if (a[i] == -1) {
                    // 残片：左移 1 格；t = -m 的格子概率恒为 0（未集齐 m 个残片前
                    // 净余量 >= 1-m），丢弃不丢概率
                    if (t > 0) nt = t - 1;
                    else continue; // t = 0 即净余量 -m，上面论证过概率必为 0
                } else {
                    // 包：右移 a_i 格，越过 +m 的部分截到顶格
                    nt = t + a[i] > top ? top : t + a[i];
                }
                ndp[nj][nt] += cur * p[i];
            }
        }
        for (ll j = 0; j <= reach; j++)
            for (int t = 0; t < span; t++)
                dp[j][t] = ndp[j][t];
    }

    // 成功数 >= L 的概率全部在第 L 档；净余量 >= 0 即残片装得下
    double ans = 0.0;
    for (int t = base; t < span; t++)
        ans += dp[need][t];
    printf("%.6f\n", ans);
    return 0;
}
