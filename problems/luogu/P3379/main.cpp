/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-20 10:38
 */
#include <bits/stdc++.h>
using namespace std;

// main.cpp：P3379 最近公共祖先（LCA）正式解，直接使用 rbook 模板 lca-binary-lifting。
// 与模板的唯一差别：模板用递归 dfs 预处理，本题 n 最大 5e5，递归可能爆栈，
// 预处理改用 BFS 迭代，depth / up / kth_ancestor / lca 接口与模板保持一致。

const int MAXN = 500005;
const int LOG = 20; // 2^20 > 5e5，覆盖最大深度差

using Graph = vector<int>;
Graph tree[MAXN]; // 全局邻接表数组：直接向 tree[u] 加无权边

// 倍增算法求最近公共祖先（LCA），接口与 rbook 模板 lca-binary-lifting 一致。
struct BinaryLCA {
    int depth[MAXN];       // depth[u] 表示节点 u 的深度（根深度为 1）
    int up[MAXN][LOG + 1]; // up[u][j] 表示节点 u 的 2^j 级祖先

    // BFS 从根出发，预处理每个节点的深度和 2^j 级祖先表。
    // 模板用递归 dfs，这里换 BFS 避免 5e5 链形树递归爆栈。
    void build(int root) {
        queue<int> que;
        que.push(root);
        depth[root] = 1;
        up[root][0] = 0; // 根的祖先视为 0 号虚点

        while (!que.empty()) {
            int u = que.front();
            que.pop();

            // 倍增转移：先跳 2^(j-1)，再从那里继续跳 2^(j-1)。
            for (int j = 1; j <= LOG; j++) {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }

            for (int v : tree[u]) {
                if (v == up[u][0]) {
                    continue; // v 是父亲，跳过
                }
                up[v][0] = u;
                depth[v] = depth[u] + 1;
                que.push(v);
            }
        }
    }

    // 查询节点 u 的第 k 级祖先（向上跳 k 步），k 拆成二进制位逐层跳。
    int kth_ancestor(int u, int k) {
        for (int j = 0; j <= LOG; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
            }
        }
        return u;
    }

    // 查询节点 a 和节点 b 的最近公共祖先。
    int lca(int a, int b) {
        if (depth[a] < depth[b]) {
            swap(a, b); // 保证 a 是较深节点
        }

        a = kth_ancestor(a, depth[a] - depth[b]);
        if (a == b) {
            return a; // b 本来就是 a 的祖先
        }

        // 从大到小一起跳，跳到 LCA 下面一层。
        for (int j = LOG; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
};

BinaryLCA solver;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, root;
    cin >> n >> m >> root; // 注意输入顺序：n m root(s)

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    solver.build(root);

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        cout << solver.lca(a, b) << '\n';
    }

    return 0;
}
