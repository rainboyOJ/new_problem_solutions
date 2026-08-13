/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:30
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;
const int LOG = 16; // 2^16 = 65536 > 5*10^4，按题目规模调整

// 仿照 rbook 模板 lca-binary-lifting：倍增预处理祖先表，O(log n) 查询 LCA，
// 再叠加树上点差分，统计 k 条路径 u -> v 经过每个点的次数。
struct BinaryLCA {
    int n;
    vector<int> g[MAXN];
    int depth[MAXN];
    int up[MAXN][LOG + 1]; // up[u][j] 表示 u 的 2^j 级祖先，up[u][0] 是 u 的父亲
    int diff[MAXN];        // 树上点差分：先只记端点标记，最后自底向上汇总成真实经过次数
    int order[MAXN];       // dfs 进入顺序，倒序即"先子后父"的汇总顺序
    int order_cnt;

    void init(int n_) {
        n = n_;
        order_cnt = 0;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            depth[i] = 0;
            diff[i] = 0;
            for (int j = 0; j <= LOG; j++) up[i][j] = 0;
        }
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 求每个点的深度与倍增祖先表，同时记录进入顺序。
    void dfs(int u, int fa) {
        up[u][0] = fa;
        depth[u] = depth[fa] + 1;
        for (int j = 1; j <= LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
        order[++order_cnt] = u;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa) continue;
            dfs(v, u);
        }
    }

    void build(int root = 1) {
        depth[0] = 0;
        dfs(root, 0);
    }

    int kth_ancestor(int u, int k) const {
        for (int j = 0; j <= LOG; j++) {
            if (k & (1 << j)) u = up[u][j];
        }
        return u;
    }

    int lca(int a, int b) const {
        if (depth[a] < depth[b]) swap(a, b);

        a = kth_ancestor(a, depth[a] - depth[b]);
        if (a == b) return a;

        for (int j = LOG; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }

    // 树上点差分：给路径 u -> v 上每个点 +1。
    // 端点 u、v 各 +1；lca 会被两条"到根"的链算两次，-1 减回一次；
    // fa[lca] -1 用来抵消 lca 以上所有祖先被算两次的多余贡献。
    void path_add(int u, int v) {
        int g = lca(u, v);
        diff[u]++;
        diff[v]++;
        diff[g]--;
        if (up[g][0] != 0) diff[up[g][0]]--;
    }

    // 自底向上汇总子树差分，返回被经过次数最多的点的次数。
    int collect_max() {
        int answer = 0;
        for (int i = order_cnt; i >= 1; i--) {
            int u = order[i];
            if (answer < diff[u]) answer = diff[u];
            if (up[u][0] != 0) diff[up[u][0]] += diff[u];
        }
        return answer;
    }
};

BinaryLCA tree; // 全局实例：内部数组较大，避免占用栈空间

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    tree.init(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build(1);

    for (int i = 1; i <= k; i++) {
        int s, t;
        cin >> s >> t;
        tree.path_add(s, t);
    }

    cout << tree.collect_max() << '\n';
    return 0;
}
