/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:30
 *
 * P9716 [EC Final 2022] Coloring
 *
 * 模型：把操作 c_i <- c_{a_i} 看成"把 i 的父亲 a_i 的颜色复制给 i"。
 * 对每个点 u 记 c_u = 它被操作(改色)的次数，则：
 *   - u 最终颜色 = (c_u + [u == s]) % 2，因为初始只有 s 是 1；
 *   - 要第 k 次改色 u，必须先有颜色从 a_u 流过来，所以 c_u 与 c_{a_u} 满足
 *     c_u <= c_{a_u} + [a_u == s]（u != s），根 s 不受这条约束；
 *   - 总代价 = sum c_u * p_u（同一颜色连续写两次无意义，所以总次数就是 c_u）。
 * 于是题目变成：在基环树上按上面的约束选 c_u，最大化
 *   sum_{u: 最终颜色=1} w_u - sum c_u * p_u
 *
 * 做法：先找 s 所在的环。
 *   - s 不在环上：把 a_i -> i 看成以 s 为根的外向树，树形 DP
 *     f[u][i] = u 被改色 i 次时 u 子树的最大收益，转移用前缀 max 优化。
 *     答案 = max(f[s][0], f[s][1])（改色超过 1 次不会更优）。
 *   - s 在环上（环长 k）：环上点的子树各自树形 DP，环上再套一层 DP。
 *     k == 2 时只有三种合法组合，直接取 max。
 *     k > 2 时枚举 c_s = r，用 g[i][j] (j = 0/1/2) 表示走到环上第 i 个点时
 *     它的改色次数是 r - j。相邻两点的次数最多相差 1（循环一次）。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 5005;
const ll NEG = -(ll)4e18;      // 负无穷，注意别让它参加加法后溢出

int n, s;                      // 点数，初始颜色为 1 的点（输入 1 下标，代码里转 0 下标）
ll w[MAXN], p[MAXN];           // 价值、单次改色代价
int a[MAXN];                   // a[i] 指向的元素
vector<int> g[MAXN];           // 反图 a_i -> i，即以 i 为父亲的儿子集合

int on_cycle[MAXN];            // 是否属于 s 所在的环
vector<int> cyc;               // s 所在的环（rot 成以 s 开头）

ll f[MAXN][MAXN];              // f[u][i]: u 被改色 i 次时，u 子树的最大收益

// 计算 u 子树（u 在环上或树上，环上结点的环上儿子被跳过）
void dfs(int u) {
    // 基础值：u 最终颜色 = (i + [u == s]) % 2，产生价值 w[u]；代价 i * p[u]
    for (int i = 0; i <= n; i++) {
        int color = (i + (u == s)) & 1;
        f[u][i] = (color ? w[u] : 0) - (ll)i * p[u];
    }
    f[u][n + 1] = NEG;

    for (int v : g[u]) {
        if (on_cycle[v]) continue;      // 环上的儿子由环 DP 负责
        dfs(v);
        ll best = NEG;                  // 前缀 max：max_{0 <= j <= i} f[v][j]
        for (int i = 0; i <= n; i++) {
            best = max(best, f[v][i]);
            ll add = best;
            // 父亲是 s 时，儿子可以多用一次：j <= i + 1
            if (u == s) add = max(add, f[v][i + 1]);
            f[u][i] += add;
        }
    }
}

// 找到 s 所在环上的所有点
void find_cycle() {
    int x = s;
    vector<char> vis(n, 0);
    while (!vis[x]) { vis[x] = 1; x = a[x]; }
    vector<char> used(n, 0);
    int y = x;
    while (!used[y]) { cyc.push_back(y); used[y] = 1; y = a[y]; }
    reverse(cyc.begin(), cyc.end());
    for (int u : cyc) on_cycle[u] = 1;
    // 旋转成以 s 开头
    int pos = 0;
    for (int i = 0; i < (int)cyc.size(); i++) if (cyc[i] == s) pos = i;
    rotate(cyc.begin(), cyc.begin() + pos, cyc.end());
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    s--;                                    // 转成 0 下标
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) { cin >> a[i]; a[i]--; }

    for (int i = 0; i < n; i++) g[a[i]].push_back(i);

    find_cycle();

    if (!on_cycle[s]) {
        // s 不在环上：s 为根的树，直接树形 DP
        dfs(s);
        cout << max(f[s][0], f[s][1]) << "\n";
        return 0;
    }

    // s 在环上：环上每个点跑一遍子树 DP
    for (int u : cyc) dfs(u);

    int k = (int)cyc.size();
    if (k == 2) {
        // 只有 s 和 t 两个点，枚举它们的改色次数组合
        int t = cyc[1];
        ll ans = max(f[s][0] + f[t][0], f[s][0] + f[t][1]);
        ans = max(ans, f[s][1] + f[t][0]);
        cout << ans << "\n";
        return 0;
    }

    // k > 2：枚举 c_s = r（把 s 的初始颜色 1 也算进去，所以 r >= 1）
    ll ans = NEG;
    for (int r = 1; r <= n + 1; r++) {
        // g[j]: 当前环上点改色次数为 r - j 时的最大收益
        ll g[3] = {f[s][r - 1], NEG, NEG};
        for (int i = 1; i < k; i++) {
            ll ng[3] = {NEG, NEG, NEG};
            // 本点次数 = r：前一个点次数只能也是 r
            if (g[0] > NEG / 2) ng[0] = max(ng[0], g[0] + f[cyc[i]][r]);
            // 本点次数 = r-1：前一个点是 r 或 r-1
            {
                ll pre = max(g[0], g[1]);
                if (pre > NEG / 2) ng[1] = max(ng[1], pre + f[cyc[i]][r - 1]);
            }
            // 本点次数 = r-2：前一个点可以是 r / r-1 / r-2
            if (r > 1) {
                ll pre = max(max(g[0], g[1]), g[2]);
                if (pre > NEG / 2) ng[2] = max(ng[2], pre + f[cyc[i]][r - 2]);
            }
            g[0] = ng[0]; g[1] = ng[1]; g[2] = ng[2];
        }
        ans = max(ans, max(max(g[0], g[1]), g[2]));
    }
    cout << ans << "\n";
    return 0;
}
