/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:28
 * update_at: 2026-10-08 02:28
 */
// main.cpp：一本通 1786《01背包》
//
// 题意：n 个物品（体积 s、价值 v），对每个容量 j = 1..m **各自独立**做一次 0/1 背包，
//       输出 m 个最大价值。范围 1<=n<=1e6, 1<=m<=1e5, 1<=s<=300, 1<=v<=1e9。
//
// 朴素 01 背包是 O(n*m) = 1e11，超时。突破口是体积只有 300 种：
//   把物品按体积 s 分组，组内按价值降序取前 K 个（K = min(组内物品数, m/s)），
//   记前缀和 pre[k] = 该组价值最大的 k 个之和；取 k 个必然取价值最大的 k 个。
//   于是 dp[j] = 容量不超过 j 的最大价值，按组递推：
//       new_dp[j] = max{ dp[j-k*s] + pre[k] : 0 <= k <= j/s }
//   注：这里 k 允许超过组内物品数 cnt —— pre[k] = pre[cnt]（取价值 0 的幽灵物品），
//   因为 dp 单调不减，取幽灵物品永不更优，故把 pre 常数延拓是**无损**的，可省掉窗口约束。
//   固定余数 r = j mod s 后，链上下标 i（j = r + i*s）互相独立：
//       new[i] = max{ f[t] + pre[i-t] : 0 <= t <= i }
//   pre 是凹函数（增量 v[k] 单调不增），故任意两个决策点 t1 < t2 的优劣只会反转一次，
//   argmax 关于 i 单调不减 —— 用分治优化（决策单调性）把一条链降到 O(L log L)。
//   总复杂度 sum_{s=1..300} O(m log(m/s)) ≈ 3e8 次简单运算（限时 7000 ms）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXS = 300;         // 题面给出的体积上界
const int MAXM = 100000;      // 题面给出的容量上界

ll dp[MAXM + 1];              // dp[j]：容量不超过 j 时的最大价值，题面答案即 dp[1..m]
ll f[MAXM + 1];               // 当前同余链上转移前的旧值 f[i] = dp[r + i*s]
ll g[MAXM + 1];               // 当前同余链上转移后的新值
ll pre[MAXM + 1];             // pre[k]：当前体积组内价值最大的 k 个物品的价值之和
int cnt[MAXS + 1];            // cnt[s]：体积为 s 的物品个数
vector<int> buck[MAXS + 1];   // buck[s]：体积为 s 的所有物品价值

// 分治优化：求解链上区间 [l, r] 的 g[]，已知 opt(i)（最优决策 t）落在 [optl, optr] 内。
// 决策 t 的含义是"从旧链的下标 t 转移过来"，即本组取了 i - t 个物品。
void solve(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int lo = optl;                 // 下界：opt 单调不减
    int hi = min(optr, mid);       // 上界：t 不能超过 mid
    ll best = LLONG_MIN;
    int bestt = lo;
    for (int t = lo; t <= hi; t++) {
        ll cand = f[t] + pre[mid - t];
        if (cand > best) { best = cand; bestt = t; }
    }
    g[mid] = best;
    solve(l, mid - 1, optl, bestt);
    solve(mid + 1, r, bestt, optr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int s, v;
        cin >> s >> v;
        if (s > m) continue;       // 任何容量都装不下，直接丢弃
        if (s < 1) continue;
        buck[s].push_back(v);      // s <= 300 由题面保证
    }

    for (int s = 1; s <= min(MAXS, m); s++) {
        if (buck[s].empty()) continue;
        sort(buck[s].begin(), buck[s].end(), greater<int>());  // 组内价值降序
        int c = (int)buck[s].size();
        int K = m / s;                                        // 链上最多取 K 个（i-t <= K）
        pre[0] = 0;
        for (int k = 1; k <= K; k++)                          // k>c 时常数延拓
            pre[k] = pre[k - 1] + (k <= c ? buck[s][k - 1] : 0);
        for (int r = 0; r < s; r++) {                         // 按余数拆成 s 条链
            if (r > m) break;
            int L = (m - r) / s;                              // 链长：i = 0..L
            for (int i = 0; i <= L; i++) f[i] = dp[r + i * s];
            solve(0, L, 0, L);
            for (int i = 0; i <= L; i++) dp[r + i * s] = g[i];
        }
    }

    for (int j = 1; j <= m; j++) {
        if (j > 1) cout << ' ';
        cout << dp[j];
    }
    cout << '\n';
    return 0;
}
