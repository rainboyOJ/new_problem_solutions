// Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
// rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
// rainboy的学习导航网站: https://idx.roj.ac.cn
// create_at: 2026-10-08 00:39
// update_at: 2026-10-08 00:39
//
// 一本通 1766《成绩单》（= 洛谷 P5336 [THUSC2016] 成绩单）—— 区间 DP
//
// 【模型】一批成绩单不要求是原序列上的连续区间：中间的元素先被取走后，其左右两侧
// 在剩下的那一叠里就相邻了，可以并进同一批。因此只按「原序列连续区间划分」做线性 DP
// 是错的（题面样例会得到 21，正确答案是 15）。
//
// 【合法性刻画（只看位置，不看分数）】给每张成绩单赋一个批次时间 t（同批相同，
// 不同批不同）。设某批 B 的元素在原序列中最左 / 最右位置为 L、R，则 B 在被取走的
// 那一刻合法 <=> 所有满足 L < p < R 且 p 不属于 B 的位置 p 都已经先被取走。
//
// 【递归结构】对区间 [l,r]，设 S 为其中最后被取走的那批（S 非空）。S 取走时 [l,r] 内
// 其余元素已全部取走，所以 S 必然合法；反过来，任何 S 也都能充当最后一批。并且 S 在
// [l,r] 内相邻两个位置之间的「空隙」（极大连续段）是互相独立的子问题 —— 若某个批次的
// 元素跨过 S 的某个元素，就与该批次的合法性矛盾。于是
//     dp[l][r] = min over 最后一批 S 的 ( a + b*(maxS-minS)^2 + Σ_空隙 dp[空隙] )
//
// 【状态】把分数离散化成 1..V 的排名（V <= n <= 50）：
//   dp[l][r]        : 把区间 [l,r] 当成独立一叠全部发完的最小代价（空区间为 0）
//   g[l][r][x][y]   : 把 [l,r] 中「不属于最后一批」的元素全部消掉的最小代价；要求
//                     最后一批含位置 l，且其中所有分数的排名落在 [x,y] 内。
//                     不含最后一批自身的代价 a + b*(val[y]-val[x])^2
//   hh[s][r]        : [s,r] 中 s 作为最后一批最左元素时的最优总代价（含最后一批代价）
//                     = min_{x<=rank[s]<=y} ( g[s][r][x][y] + a + b*(val[y]-val[x])^2 )
//
// 【转移】按区间长度递增：
//   g[l][r][x][y] = min_{k=l}^{r-1} ( g[l][k][x][y] + min( dp[k+1][r],
//                                    g[k+1][r][x][y] 若 rank[k+1] 落在 [x,y] ) )
//       （[l,k] 留下含 l 的一批，[k+1,r] 要么整段先取空、要么也留下含 k+1 的一批并入）
//   基态 g[l][l][x][y] = 0（当且仅当 x <= rank[l] <= y，否则 INF）
//   dp[l][r] = min_{s=l}^{r} ( dp[l][s-1] + hh[s][r] )   （[l,s-1] 是 s 左边的空隙）
//   答案 dp[1][n]
//
// 【复杂度】时间 O(n^3 * V^2 / 4)，n=V=50 实测 < 0.5s（限时 3000 ms）；
//           空间 g[55][55][51][51] ≈ 31 MB（限时 256 MB）。
// 【取值上界】k <= n <= 50，每批代价 <= a + b*999^2，总和 < 5.0e8，int 足够；
//           INF = 1e9，两两相加不溢出 int。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 55;  // n <= 50
const int MAXV = 51;  // 不同分数个数 <= n <= 50
const int INF = 1000000000;  // 1e9：合法答案 < 5e8，INF + 合法值也不会溢出 int

int n;            // 成绩单数量
int a, b;         // 评估参数
int w[MAXN];      // w[i] : 第 i 张成绩单的原始分数（1 起）
int rankv[MAXN];  // rankv[i] : 第 i 张成绩单分数压缩后的排名（0 起）
int val[MAXV];    // val[x] : 排名 x 对应的原始分数
int V;            // 不同分数的个数

int dp[MAXN][MAXN];  // dp[l][r] : 把区间 [l,r] 当成独立一叠全部发完的最小代价
int hh[MAXN][MAXN];  // hh[s][r] : s 作为最后一批最左元素时 [s,r] 的最优总代价
// g[l][r][x][y] : 消掉 [l,r] 中不属于最后一批的元素，最后一批含 l 且排名落在 [x,y]
static int g[MAXN][MAXN][MAXV][MAXV];

int main() {
    if (scanf("%d %d %d", &n, &a, &b) != 3) return 0;
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

    // ---------- 离散化：分数 -> 排名 ----------
    vector<int> vs(w + 1, w + n + 1);
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    V = (int)vs.size();
    for (int x = 0; x < V; ++x) val[x] = vs[x];
    for (int i = 1; i <= n; ++i)
        rankv[i] = (int)(lower_bound(vs.begin(), vs.end(), w[i]) - vs.begin());

    // ---------- 初始化 ----------
    // 非法状态一律 INF：排名不在 [x,y] 内的位置不可能属于最后一批
    for (int l = 1; l <= n; ++l)
        for (int r = l; r <= n; ++r)
            for (int x = 0; x <= rankv[l]; ++x)
                for (int y = rankv[l]; y < V; ++y)
                    g[l][r][x][y] = INF;
    for (int i = 1; i <= n + 1; ++i) dp[i][i - 1] = 0;  // 空区间

    for (int l = 1; l <= n; ++l) {  // 长度 1 的基态：只留下 l 本身，无需先消任何元素
        for (int x = 0; x <= rankv[l]; ++x)
            for (int y = rankv[l]; y < V; ++y)
                g[l][l][x][y] = 0;
    }

    // ---------- 按区间长度递增递推 ----------
    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            // (1) g[l][r][x][y]：枚举分割点 k，左半留下含 l 的一批，右半二选一
            if (len > 1) {
                for (int x = 0; x <= rankv[l]; ++x) {
                    for (int y = rankv[l]; y < V; ++y) {
                        int best = INF;
                        for (int k = l; k < r; ++k) {
                            int left = g[l][k][x][y];
                            if (left >= INF) continue;
                            int right = dp[k + 1][r];  // 右半整段先取空
                            if (x <= rankv[k + 1] && rankv[k + 1] <= y) {
                                // 右半也留下含 k+1 的一批，并入同一个最后一批
                                int gv = g[k + 1][r][x][y];
                                if (gv < right) right = gv;
                            }
                            int cand = left + right;
                            if (cand < best) best = cand;
                        }
                        g[l][r][x][y] = best;
                    }
                }
            }

            // (2) hh[l][r]：把最后一批结算掉（枚举它的排名上下界，取最小的极差代价）
            int hbest = INF;
            for (int x = 0; x <= rankv[l]; ++x) {
                for (int y = rankv[l]; y < V; ++y) {
                    int gv = g[l][r][x][y];
                    if (gv >= INF) continue;
                    int d = val[y] - val[x];
                    int cand = gv + a + b * d * d;
                    if (cand < hbest) hbest = cand;
                }
            }
            hh[l][r] = hbest;

            // (3) dp[l][r]：枚举最后一批的最左位置 s，[l,s-1] 是它左边的空隙
            int dbest = INF;
            for (int s = l; s <= r; ++s) {
                int cand = dp[l][s - 1] + hh[s][r];
                if (cand < dbest) dbest = cand;
            }
            dp[l][r] = dbest;
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}
