/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 20:37
 * update_at: 2026-10-26 20:37
 */
// main2.cpp：换根 DP（二次扫描与换根）解法
// 核心思路：枚举三叉臂的汇合中心点 m，在 m 处向不同子树拉出前三长链 l1 >= l2 >= l3
// 最大路程为一条主干道(走一次)加一条支链折返(走两次)：l1 + 2 * l2 + l3
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 200005;

struct Edge {
    int to;
    ll w;
};

int n, m;
vector<Edge> g[MAXN];

// down[u][0..2]：节点 u 在其以 1 为根的子树内，向不同子树走出的最长、次长、第三长链长度
ll down[MAXN][3];
// best_child[u][0..2]：对应链走入的具体子节点编号
int best_child[MAXN][3];
// up[u]：从 u 沿着父亲方向向外能走的最长链长度
ll up_chain[MAXN];

ll ans = 0;

void insert_down(int u, ll val, int child) {
    if (val > down[u][0]) {
        down[u][2] = down[u][1];
        best_child[u][2] = best_child[u][1];
        down[u][1] = down[u][0];
        best_child[u][1] = best_child[u][0];
        down[u][0] = val;
        best_child[u][0] = child;
    } else if (val > down[u][1]) {
        down[u][2] = down[u][1];
        best_child[u][2] = best_child[u][1];
        down[u][1] = val;
        best_child[u][1] = child;
    } else if (val > down[u][2]) {
        down[u][2] = val;
        best_child[u][2] = child;
    }
}

// 第一次 DFS：自底向上统计子树内的最长、次长、第三长链
void dfs1(int u, int fa) {
    for (auto &e : g[u]) {
        int v = e.to;
        if (v == fa) continue;
        dfs1(v, u);
        insert_down(u, down[v][0] + e.w, v);
    }
}

// 第二次 DFS：自顶向下传递 up 链，并在每个点汇聚所有方向的前三长链更新全局答案
void dfs2(int u, int fa) {
    // 收集节点 u 向外延伸的所有独立分支（向下最多 3 条，向上 1 条）
    vector<ll> chains;
    for (int i = 0; i < 3; i++) {
        if (down[u][i] > 0) chains.push_back(down[u][i]);
    }
    if (up_chain[u] > 0) chains.push_back(up_chain[u]);
    sort(chains.begin(), chains.end(), greater<ll>());

    // 若至少有三条分支，第二长链翻倍：l1 + 2*l2 + l3
    // 若只有两条分支，第三条视作长度 0：l1 + 2*l2
    // 若只有一条分支，翻倍也是合法的退化情况
    if (chains.size() >= 3) {
        ans = max(ans, chains[0] + 2 * chains[1] + chains[2]);
    } else if (chains.size() == 2) {
        ans = max(ans, chains[0] + 2 * chains[1]);
    } else if (chains.size() == 1) {
        ans = max(ans, chains[0]);
    }

    for (auto &e : g[u]) {
        int v = e.to;
        if (v == fa) continue;
        // 计算给子节点 v 传递的 up 链：u 的除 v 以外的最长分支 + e.w
        ll max_other = up_chain[u];
        if (best_child[u][0] != v) {
            max_other = max(max_other, down[u][0]);
        } else {
            max_other = max(max_other, down[u][1]);
        }
        up_chain[v] = max_other + e.w;
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs1(1, 0);
    dfs2(1, 0);

    cout << ans << "\n";
    return 0;
}
