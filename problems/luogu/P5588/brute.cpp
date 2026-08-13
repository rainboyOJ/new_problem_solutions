/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:32
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接枚举所有点对 (u,v)，收集路径上的节点集合（注意端点 u、v 本身也在路径
// 上），再检查某种颜色的全部节点是否都在这条路径上。
// 复杂度 O(n^4) 量级，只适合 n <= 30 的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int color[MAXN];          // color[i]：节点 i 的颜色
vector<int> g[MAXN];      // 邻接表存树
int parent[MAXN];         // 树上父亲（根 1 的父亲为 0）
vector<int> color_nodes[MAXN]; // color_nodes[c]：颜色 c 的全部节点

int probe[MAXN]; // probe[x]：找 LCA 时的临时探针标记（用递增 token，免清空）
int mark[MAXN];  // mark[x]：x 是否在当前的路径 u-v 上

// 从根 1 出发 BFS 求父亲。
void bfs_parent() {
    int q[MAXN], head = 0, tail = 0;
    q[tail++] = 1;
    parent[1] = 0;
    while (head < tail) {
        int u = q[head++];
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v != parent[u]) {
                parent[v] = u;
                q[tail++] = v;
            }
        }
    }
}

// 找 u、v 的最近公共祖先：u 一路爬到根并打探针，v 向上爬，
// 撞到的第一个探针节点就是 LCA。
int find_lca(int u, int v, int token) {
    int x = u;
    while (x != 0) {
        probe[x] = token;
        x = parent[x];
    }
    int y = v;
    while (probe[y] != token) {
        y = parent[y];
    }
    return y;
}

// 把路径 u-lca-v 上的全部节点（含两端点与 LCA）打上标记。
void mark_path(int u, int v, int l, int token) {
    int x = u;
    while (x != l) {
        mark[x] = token;
        x = parent[x];
    }
    mark[l] = token;
    int y = v;
    while (y != l) {
        mark[y] = token;
        y = parent[y];
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
        color_nodes[color[i]].push_back(i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs_parent();

    int ans[MAXN] = {0};
    int token = 0;
    // 枚举所有点对 (u,v)，u < v。
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            token++;
            int l = find_lca(u, v, token);
            mark_path(u, v, l, token);
            // 对每种颜色检查：该颜色的全部节点是否都在这条路径上。
            for (int c = 1; c <= n; c++) {
                bool ok = true;
                for (int i = 0; i < (int)color_nodes[c].size(); i++) {
                    if (mark[color_nodes[c][i]] != token) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    ans[c]++;
                }
            }
        }
    }

    for (int c = 1; c <= n; c++) {
        cout << ans[c] << '\n';
    }

    return 0;
}
