/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:09
 * update_at: 2026-10-08 01:09
 */

// ROJ 1769《景中人》
// 平面上 n 个点，用最少的矩形覆盖所有点：矩形形如 [a,b] x [0,h]（底边贴在 y=0），
// 面积 (b-a)*h <= S。多组数据。
//
// 做法（区间 DP，按高度分层）：
//   1. 同一横坐标只需保留最高的那个点（矩形覆盖 (x,y) 当且仅当 x 落在底边区间内且 y <= h）。
//      于是压缩成 nn 列：第 t 列的横坐标 colX[t]、最高点的高度排名 colY[t]（1 最小，m 最大）。
//   2. 关键性质：存在一组最优解，任意两个矩形的底边区间"相离或包含"。
//      证明：两区间相交但不包含时（a1 < a2 <= b1 < b2），设两矩形高度 h1、h2。
//      若 h1 >= h2，把矩形 2 截短成 [b1,b2]：它原来在 [a2,b1] 里盖住的点都满足 y <= h2 <= h1
//      且横坐标落在 [a1,b1] 内，已被矩形 1 覆盖；反之 h1 < h2 时把矩形 1 截短成 [a1,a2]，
//      它原来在 [a2,b1] 里盖住的点都满足 y <= h1 < h2 且横坐标落在 [a2,b2] 内，被矩形 2 覆盖。
//      两种情形都不增加矩形数，反复操作即得"相离或包含"的解。
//   3. 层叠结构下按"最左列"分解：设 dp[k][i][j] 表示覆盖列 i..j 中高度排名 >= k 的点
//      所需的最少矩形数。取最左的待覆盖列 i，覆盖它最高点的那个"最外层"矩形
//      （它不可能被别的矩形包含）底边必是 [colX[i], colX[q]]，q 越大宽度越大、允许高度越低，
//      所以高度取允许的最大值 ymx[i][q] = max{h : h*(colX[q]-colX[i]) <= S}。
//      该矩形把列 i..q 中高度 <= ymx 的点全部覆盖，剩余的点只能是列 i..q 中高度 > ymx 的点
//      （由嵌在它内部的矩形处理）和列 q+1..j 的点（与它相离）：
//          dp[k][i][j] = min_{q} ( g[i][q] + dp[k][q+1][j] ),   g[i][q] = 1 + dp[ymx+1][i][q]
//      其中 q 必须满足 ymx[i][q] >= colY[i]（否则矩形盖不住第 i 列最高点，它就不该是最外层），
//      这类 q 构成前缀 [i, limQ[i]]；又因为 xs[q]-xs[i] <= xs[j]-xs[i] 时 g[i][q] 不会更优，
//      只需 q <= j。colY[i] < k（第 i 列没有待覆盖的点）时 dp[k][i][j] = dp[k][i+1][j]。
//   4. k 从 m 降到 1 逐层计算（转移里 ymx+1 > k，上一层已算好），同层内区间长度递增。
//      答案 = dp[1][1][nn]。
// 复杂度：区间状态 O(nn^2 * m) 个，每个转移 O(nn)，总 O(nn^3 * m)；
//        nn,m <= 100、T <= 10，实测最坏测试点 < 0.5 s。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;      // 题面上限 n <= 100，留少量安全余量
const int INF = 1000000000;

struct Point {
    int x;
    int y;
};
Point pt[MAXN];            // 输入的点（先按 x 升序、x 相同时按 y 降序排好）

bool cmpPoint(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

ll S;                      // 单个矩形的面积上限
int colX[MAXN];            // 压缩后第 t 列的横坐标（1-based）
int colY[MAXN];            // 第 t 列最高点的高度排名（1-based，越大越高）
int hVal[MAXN];            // 高度排名 -> 实际高度
int ymxTab[MAXN][MAXN];    // ymxTab[i][q]：底边横跨列 i..q 时允许的最大高度排名
int limQ[MAXN];            // limQ[i]：仍能盖住第 i 列最高点的最大 q（q 再大允许高度就不够）
int g[MAXN][MAXN];         // g[i][q] = 1 + dp[ymx+1][i][q]：一条横跨 i..q 的矩形 + 它内部剩余
int dp[MAXN][MAXN][MAXN];  // dp[k][i][j]：覆盖列 i..j 中高度排名 >= k 的点所需最少矩形数

void solve() {
    int T;
    if (scanf("%d", &T) != 1) return;
    while (T--) {
        int n;
        if (scanf("%d %lld", &n, &S) != 2) return;
        for (int i = 1; i <= n; i++) scanf("%d %d", &pt[i].x, &pt[i].y);
        if (n <= 0) {
            printf("0\n");
            continue;
        }

        sort(pt + 1, pt + n + 1, cmpPoint);

        // 多组数据必须清空记忆化数组：上一组的 nn / m 可能更大，残留值会污染这一组
        memset(dp, 0, sizeof(dp));
        memset(g, 0, sizeof(g));

        // 列压缩：同一横坐标只保留最高点；再对高度排名离散化
        int nn = 0;
        int rawY[MAXN];                    // 每列最高点的实际高度
        for (int i = 1; i <= n; i++) {
            if (i == 1 || pt[i].x != pt[i - 1].x) {
                nn++;
                colX[nn] = pt[i].x;
                rawY[nn] = pt[i].y;        // 同 x 已按 y 降序，第一条就是最高点
            }
        }
        int m = 0;
        for (int i = 1; i <= nn; i++) hVal[i] = rawY[i];
        sort(hVal + 1, hVal + nn + 1);
        for (int i = 1; i <= nn; i++)
            if (i == 1 || hVal[i] != hVal[m]) hVal[++m] = hVal[i];
        for (int i = 1; i <= nn; i++)
            colY[i] = lower_bound(hVal + 1, hVal + m + 1, rawY[i]) - hVal;

        // ymxTab 随宽度单调不增，用双指针一次扫完；宽度 0 时高度不受限制，取最高档 m
        for (int i = 1; i <= nn; i++) {
            ymxTab[i][i] = m;
            int h = m;
            for (int q = i + 1; q <= nn; q++) {
                ll width = (ll)colX[q] - colX[i];
                while (h > 0 && (ll)hVal[h] * width > S) h--;   // 宽度变大，允许高度只降不升
                ymxTab[i][q] = h;
            }
        }
        for (int i = 1; i <= nn; i++) {
            limQ[i] = i;
            for (int q = i + 1; q <= nn; q++) {
                if (ymxTab[i][q] < colY[i]) break;
                limQ[i] = q;
            }
        }

        // dp[m+1][*][*] 保持全 0（全局数组初值）：高度排名超过 m 就没有点需要覆盖
        for (int k = m; k >= 1; k--) {
            // 补齐 ymx == k 的 g：它用到 dp[k+1]，此刻已算好
            for (int i = 1; i <= nn; i++)
                for (int q = i; q <= limQ[i]; q++)
                    if (ymxTab[i][q] == k) g[i][q] = dp[k + 1][i][q] + 1;
            for (int i = nn; i >= 1; i--) {
                if (colY[i] < k) {
                    // 第 i 列没有待覆盖的点：整列跳过
                    for (int j = i; j <= nn; j++) dp[k][i][j] = dp[k][i + 1][j];
                    continue;
                }
                for (int j = i; j <= nn; j++) {
                    int best = INF;
                    int qm = limQ[i] < j ? limQ[i] : j;
                    for (int q = i; q <= qm; q++) {
                        int v = g[i][q] + dp[k][q + 1][j];   // q+1 > j 时后一项为 0
                        if (v < best) best = v;
                    }
                    dp[k][i][j] = best;
                }
            }
        }
        printf("%d\n", dp[1][1][nn]);
    }
}

int main() {
    solve();
    return 0;
}
