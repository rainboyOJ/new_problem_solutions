/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:00
 */
// brute.cpp：小数据暴力解，直接模拟三种操作，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
long long w[MAXN];       // w[i] 表示节点 i 当前的权值
int parent[MAXN];        // 预处理出的父亲
vector<int> g[MAXN];     // 树的邻接表

// 以 u 为根的子树整体加 value（u 是根节点 1，fa 用来防止回头走）。
void subtree_add(int u, int fa, long long value) {
    w[u] += value;
    for (int j = 0; j < (int)g[u].size(); j++) {
        int v = g[u][j];
        if (v != fa) subtree_add(v, u, value);
    }
}

// 求从 x 走到根 1 的路径点权和：不断沿 parent 上跳累加。
long long root_path_sum(int x) {
    long long answer = 0;
    while (x != 0) {
        answer += w[x];
        x = parent[x];
    }
    return answer;
}

// 预处理 parent：从根 1 出发遍历整棵树。
void build_parent(int u, int fa) {
    parent[u] = fa;
    for (int j = 0; j < (int)g[u].size(); j++) {
        int v = g[u][j];
        if (v != fa) build_parent(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_parent(1, 0);

    while (m--) {
        int opt, x;
        long long a;
        cin >> opt >> x;
        if (opt == 1) { // 单点加
            cin >> a;
            w[x] += a;
        } else if (opt == 2) { // 子树整体加：递归访问子树所有点
            cin >> a;
            subtree_add(x, parent[x], a);
        } else { // 询问根路径和：沿 parent 一路加到根
            cout << root_path_sum(x) << '\n';
        }
    }

    return 0;
}
