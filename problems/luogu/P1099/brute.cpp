/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:28
 */
// brute.cpp：小数据暴力解，枚举直径上的所有核区间，直接按定义计算偏心距。
// 教学点：不套任何偏心距公式，把"区间上每个节点都试一遍"当作距离定义，
// 用来验证 main.cpp 中 max(左距离, 右距离, 分支深度) 公式的正确性。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

struct Edge {
    int v; // 邻居节点
    int w; // 边权
};

int n, s;               // n 个节点，核的长度上界 s
vector<Edge> g[MAXN];   // 邻接表存树

int far_dis[MAXN];      // far_dis[u]：本次搜索中 u 到起点的距离
int far_par[MAXN];      // far_par[u]：本次搜索中 u 的父节点

int dia_node[MAXN];     // 直径节点序列：左端点 -> 右端点
int dia_pos[MAXN];      // dia_pos[u]：直径节点 u 到左端点的距离
int dia_cnt;            // 直径节点个数

int dist_all[MAXN][MAXN]; // dist_all[u][v]：u 到 v 的树上距离（全源距离）

// 从 start 出发 DFS，记录每个点到 start 的距离以及父节点。
void dfs_trace(int u, int fa, int start, int d) {
    far_dis[u] = d;
    far_par[u] = fa;
    dist_all[start][u] = d;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (v == fa)
            continue;
        dfs_trace(v, u, start, d + w);
    }
}

// 返回距离 start 最远的节点，同时准备好该次搜索的距离与父节点数组。
int find_farthest(int start) {
    dfs_trace(start, 0, start, 0);
    int far = start;
    for (int u = 1; u <= n; u++) {
        if (far_dis[u] > far_dis[far])
            far = u;
    }
    return far;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // 求直径：两次最远点搜索，第二次的父节点数组用于还原直径路径。
    int A = find_farthest(1);
    int B = find_farthest(A);
    // 从 B 沿着父节点一路回到 A，得到直径上的节点序列。
    for (int u = B; u != 0; u = far_par[u]) {
        dia_node[dia_cnt++] = u;
        if (u == A)
            break;
    }
    reverse(dia_node, dia_node + dia_cnt); // 现在是 A -> ... -> B 的顺序
    for (int i = 0; i < dia_cnt; i++) {
        dia_pos[dia_node[i]] = far_dis[dia_node[i]]; // 各直径节点到 A 的距离
    }

    // 以每个节点为起点做一次 DFS，得到全源距离 dist_all。
    for (int u = 1; u <= n; u++) {
        dfs_trace(u, 0, u, 0);
    }

    // 枚举所有核区间 [l, r]：直径上的连续一段，长度不超过 s。
    int ans = INT_MAX;
    for (int l = 0; l < dia_cnt; l++) {
        for (int r = l; r < dia_cnt; r++) {
            int len = dia_pos[dia_node[r]] - dia_pos[dia_node[l]];
            if (len > s)
                continue;
            // 按定义计算偏心距：所有节点到核区间的最小距离，取最大值。
            int ecc = 0;
            for (int x = 1; x <= n; x++) {
                int best = INT_MAX;
                for (int k = l; k <= r; k++) {
                    best = min(best, dist_all[x][dia_node[k]]);
                }
                if (best > ecc)
                    ecc = best;
            }
            if (ecc < ans)
                ans = ecc;
        }
    }
    cout << ans << endl;

    return 0;
}
