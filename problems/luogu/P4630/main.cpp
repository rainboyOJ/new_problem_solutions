/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 12:51
 * update_at: 2026-10-23 13:26
 */
// P4630 [APIO2018] 铁人两项
// 圆方树 + 树上路径贡献计数
// 核心：点双性质 → 方点赋权 BCC 大小，圆点 -1 → 树 DP 统计每点被 (s,f) 路径经过次数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 400010;  // n + bcc 约 2n ~ 3n 安全

int n, m;
vector<int> g[MAXN];      // 原图邻接表，1..n

// Tarjan 求 BCC + 同时建圆方树
int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
int tot;                  // 当前节点编号，初始 = n，方点从 n+1 开始
vector<int> e[MAXN];      // 圆方树邻接表（复用 1..tot）
int w[MAXN];              // 权值：圆点 -1，方点 = BCC 内圆点数
int f[MAXN];              // 树 DP：子树圆点数
ll ans;
int sz;                   // 当前连通分量内圆点总数（每次新分量重置）

void tarjan(int u) {
    ++sz;
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                // 找到一个以 u 为根的 BCC
                ++tot;
                w[tot] = 0;
                int x;
                do {
                    x = stk[top--];
                    e[tot].push_back(x);
                    e[x].push_back(tot);
                    ++w[tot];
                } while (x != v);
                // 割点 u 也要连到这个方点
                e[tot].push_back(u);
                e[u].push_back(tot);
                ++w[tot];
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u, int fa) {
    f[u] = (u <= n ? 1 : 0);  // 只统计圆点作为 s/f
    for (int v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        // 两端都在不同子树的贡献（经过 u）
        ans += 2LL * w[u] * f[u] * f[v];
        f[u] += f[v];
    }
    // 一端在子树、一端在子树外的贡献
    ans += 2LL * w[u] * f[u] * (sz - f[u]);
}

void solve() {
    // 初始化
    timer = 0;
    tot = n;
    top = 0;
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        dfn[i] = low[i] = 0;
        w[i] = -1;          // 圆点初始 -1
        g[i].clear();
        e[i].clear();
    }
    for (int i = n+1; i < MAXN; ++i) {
        e[i].clear();
        w[i] = 0;
        dfn[i] = low[i] = 0;
    }

    // 读边
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // 对每个连通分量做 Tarjan + DP
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            sz = 0;
            tarjan(i);
            if (top > 0) --top;
            dfs(i, 0);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    solve();
    return 0;
}
