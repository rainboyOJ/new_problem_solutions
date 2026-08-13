/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:28
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int LOG = 20;  // 2^20 > 5e5，覆盖最大深度差

// 仿照 rbook 模板 lca-binary-lifting 的 up/depth 结构与查询接口。
// 与模板的差别：本题 n 最大 5e5，递归 DFS 可能爆栈，预处理改用 BFS。
struct BinaryLCA {
    vector<int> g[MAXN];  // 邻接表
    int depth[MAXN];      // depth[u] 表示 u 的深度，根深度为 1
    int up[MAXN][LOG + 1]; // up[u][j] 表示 u 的 2^j 级祖先，根祖先为 0

    // 加一条无向边 u - v。
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // BFS 从根出发，求每个点的深度和 2^j 级祖先。
    void build(int root) {
        queue<int> que;
        que.push(root);
        depth[root] = 1;
        up[root][0] = 0;  // 根的祖先视为 0 号虚点

        while (!que.empty()) {
            int u = que.front();
            que.pop();

            // 倍增转移：先跳 2^(j-1)，再从那里继续跳 2^(j-1)。
            for (int j = 1; j <= LOG; j++) {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }

            for (int i = 0; i < (int)g[u].size(); i++) {
                int v = g[u][i];
                if (v == up[u][0]) {
                    continue;  // v 是父亲，跳过
                }
                up[v][0] = u;
                depth[v] = depth[u] + 1;
                que.push(v);
            }
        }
    }

    // 把 u 向上跳 k 步，k 拆成二进制位逐层跳。
    int kth_ancestor(int u, int k) {
        for (int j = 0; j <= LOG; j++) {
            if ((k & (1 << j)) != 0) {
                u = up[u][j];
            }
        }
        return u;
    }

    // 查询 u, v 的最近公共祖先。
    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);  // 保证 u 更深
        }

        // 第一步：把 u 提到和 v 同一深度。
        u = kth_ancestor(u, depth[u] - depth[v]);
        if (u == v) {
            return u;  // v 本来就是 u 的祖先
        }

        // 第二步：从高位到低位试跳，只有跳完后两点的祖先不同才跳。
        for (int j = LOG; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        // 此时 u, v 停在 LCA 的两个不同儿子上，父亲就是答案。
        return up[u][0];
    }
};

BinaryLCA solver;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, root;
    cin >> n >> m >> root;  // 注意输入顺序：n m root(s)

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        solver.add_edge(u, v);
    }

    solver.build(root);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cout << solver.lca(u, v) << '\n';
    }

    return 0;
}
