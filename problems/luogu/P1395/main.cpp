/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:27
 * update_at: 2026-08-16 00:10
 */
// main.cpp：距离和最小的点 = 树的重心（P1395 会议）。
// 用 rbook 模板 tree-centroid2 求出所有重心，取编号最小者（多重心时距离和相同），
// 再一遍 BFS 求它的距离和。
#include <bits/stdc++.h>
using namespace std;

using Graph = std::vector<std::vector<int>>;
Graph tree;  // 全局邻接表：使用前先 resize(n+1) 并加边

// 求树的所有重心。
// 重心：删除该点后，剩下的每个连通块大小都不超过 n/2。
// 与 tree_centroid.cpp 不同：不维护全局最小值，直接按"最大连通块 ≤ n/2"判定重心。
struct TreeCentroid2 {
    int n;
    std::vector<int> sz;   // sz[u] = u 的子树大小
    std::vector<int> ans;  // 答案：所有重心，按编号升序

    explicit TreeCentroid2(int n) : n(n), sz(n + 1) {}

    // 返回所有重心（编号升序）
    std::vector<int> find_centroids(int root = 1) {
        ans.clear();
        dfs(root, 0);
        std::sort(ans.begin(), ans.end());
        return ans;
    }

    // 统计子树大小；若 B(u) = 删除 u 后最大的连通块大小 ≤ n/2，u 就是重心
    void dfs(int u, int parent) {
        sz[u] = 1;
        int mx = 0;  // B(u)：先看各儿子子树

        for (int v : tree[u]) {
            if (v == parent) continue;
            dfs(v, u);
            sz[u] += sz[v];
            mx = std::max(mx, sz[v]);
        }

        // 父亲方向也是一块：整棵树减去 u 的子树
        mx = std::max(mx, n - sz[u]);

        // 等价判定：B(u) ≤ n/2 ⟺ u 是重心
        if (mx <= n / 2) ans.push_back(u);
    }
};

// 从 s 出发 BFS，返回所有点到 s 的距离和（s 本身的深度 0 不计入）。
long long dist_sum_from(int s) {
    queue<int> q;
    vector<int> dist(tree.size(), -1);
    dist[s] = 0;
    q.push(s);
    long long total = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : tree[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            total += dist[v];
            q.push(v);
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    tree.resize(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // 距离和最小的点 = 重心；重心至多两个且相邻、距离和相同，取编号最小的。
    TreeCentroid2 tc(n);
    vector<int> cs = tc.find_centroids();
    int meeting = cs[0];

    cout << meeting << ' ' << dist_sum_from(meeting) << '\n';
    return 0;
}
