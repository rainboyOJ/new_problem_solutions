/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:20
 * update_at: 2026-10-23 23:34
 */
// main.cpp：P1070 道路游戏 正解（决策优化，O(n*m)）。
//
// 状态定义：
//   f[t] = 前 t 个时间单位全部走完（各段步数之和恰为 t）的最大净收益，f[0] = 0。
//
// 关键观察（对角线不变量）：
//   时间 s 在工厂 i 买入、走 k 步，第 l 步过马路 (i+l-1) mod n，
//   收集 w[(i+l-1) mod n][s+l]。令 u ≡ (road - time) (mod n)，
//   则「马路下标 - 时间下标」≡ u 恒定，收益沿对角线 u 连续：
//       Σ_l w[...][s+l] = D[u][s+k] - D[u][s]
//   其中 D[u][t] = 对角线 u 上「时间 <= t」的金币前缀和。
//   反过来给定 (u, s) 时 i = (u + s + 1) mod n 唯一确定，所以购买花费可写成 cost[(u+s+1) mod n]。
//
// 转移：
//   f[t] = max_{s ∈ [t-p, t-1]} ( f[s] + max_u ( D[u][t] - D[u][s] - cost[(u+s+1) mod n] ) )
//        = max_u ( D[u][t] + max_{s ∈ [t-p, t-1]} h_u(s) )
//   其中 h_u(s) = f[s] - D[u][s] - cost[(u+s+1) mod n] 只依赖 (u, s)、与 t 无关。
//
//   ⚠ 交换 max 合法性：max_s max_u == max_u max_s 是逐点（对每个 t）成立的，
//     因此外层枚举 t、内层枚举 u；不能把 u 放外层，否则 h_u(s) 用到的 f[s]
//     可能还没算完（s < t 但 f[s] 还会被后面的 u' 更新）。
//
//   窗口 [t-p, t-1] 随 t 单调右移，对每条对角线 u 维护一个单调队列做
//   滑动窗口最大值。求完 f[t] 后再把 h_u(t) 入队（因为 h_u(t) 影响的是 t'>t）。
//   总复杂度 O(n*m)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1005;         // 工厂 / 马路上限
const int MAXM = 1005;         // 时间上限
const int DIAG_SHIFT = MAXM;   // u 平移量，保证下标非负
const int MAXU = DIAG_SHIFT + MAXN + 5; // 对角线截距 u 平移后的数组上界

int n, m, p;
ll cost[MAXN];        // cost[i]：在第 i 个工厂购买机器人的花费（0-based，与时间无关）
ll w[MAXN][MAXM];     // w[road][tm]：第 tm 个单位时间第 road 段马路上的金币
ll diag[MAXU][MAXM];  // diag[u][t]：对角线 u 上「时间 <= t」的金币前缀和
ll f[MAXM];           // f[t]：前 t 个时间单位的最大净收益

// 对角线编号：u ≡ (road - time) (mod n)，取代表元后平移 DIAG_SHIFT
inline int diag_id(int road, int tm) {
    int u = ((road - tm) % n + n) % n;
    return u + DIAG_SHIFT;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p;
    for (int road = 0; road < n; road++) {
        for (int tm = 1; tm <= m; tm++) {
            cin >> w[road][tm];
        }
    }
    for (int i = 0; i < n; i++) cin >> cost[i];

    // 1) 对角线前缀和：diag[u][tm] = diag[u][tm-1] + 该时间落在对角线 u 上的金币
    //    每个时间 tm 恰好有 n 个马路各贡献 1 个金币，分别落在 n 条对角线上（互不重复）。
    for (int u = 0; u < MAXU; u++) diag[u][0] = 0;
    for (int tm = 1; tm <= m; tm++) {
        for (int u = 0; u < MAXU; u++) diag[u][tm] = diag[u][tm - 1];
        for (int road = 0; road < n; road++) {
            int u = diag_id(road, tm);
            diag[u][tm] += w[road][tm];
        }
    }

    // 2) DP：f[0] = 0；f[t] 初值取 -inf，表示「还没算出来」
    f[0] = 0;
    for (int t = 1; t <= m; t++) f[t] = -(1LL << 60);

    // 3) 逐 t 求 f[t]；内层枚举对角线 u，外层枚举 t。
    //    对每个 u 一个单调队列，队列内容只增不减（下标单调递增，hval 递减）。
    //    ⚠ 顺序关键：先把 s = t-1 入队（f[t-1] 已知），再用当前队列算 f[t]。
    static int qidx[MAXN][MAXM]; // qidx[u][k]：对角线 u 的队列第 k 个候选的下标 s
    static int qhead[MAXN], qtail[MAXN]; // 队列头尾（左闭右开）
    static ll hval[MAXN][MAXM]; // hval[u][s]：对角线 u 在 s 处的候选值

    for (int t = 1; t <= m; t++) {
        // 3.1) 把 s = t-1 加入候选（f[t-1] 已知）；t=1 时即 f[0]=0 的基线
        for (int u = 0; u < n; u++) {
            int s = t - 1;
            int i = (u + s + 1) % n; // i = (u + s + 1) mod n
            hval[u][s] = f[s] - diag[u + DIAG_SHIFT][s] - cost[i];
            while (qtail[u] > qhead[u] && hval[u][qidx[u][qtail[u] - 1]] <= hval[u][s]) qtail[u]--;
            qidx[u][qtail[u]] = s;
            qtail[u]++;
        }
        // 3.2) 用已知 f[s] (s < t) 更新 f[t]：对每个 u 求滑动窗口最大值，取全局最大
        for (int u = 0; u < n; u++) {
            while (qhead[u] < qtail[u] && qidx[u][qhead[u]] < t - p) qhead[u]++;
            if (qhead[u] < qtail[u]) {
                int s = qidx[u][qhead[u]];
                ll cand = diag[u + DIAG_SHIFT][t] + hval[u][s];
                if (cand > f[t]) f[t] = cand;
            }
        }
    }

    cout << f[m] << "\n";
    return 0;
}
