/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:28
 */
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
int far_par[MAXN];      // far_par[u]：本次搜索中 u 的父节点，用于还原直径路径

int dia_node[MAXN];     // dia_node[i]：直径上第 i 个节点，从左端点 A 到右端点 B
int dia_pos[MAXN];      // dia_pos[u]：直径节点 u 到左端点 A 的距离（即直径上的坐标）
int dia_cnt;            // 直径上的节点个数
bool on_dia[MAXN];      // on_dia[u]：节点 u 是否在直径上

int branch_max;         // 所有直径节点挂载的直径外子树的最大深度

// 从 start 出发 DFS 遍历整棵树，记录距离与父节点。
void dfs_dist(int u, int fa, int d) {
    far_dis[u] = d;
    far_par[u] = fa;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (v == fa)
            continue;
        dfs_dist(v, u, d + w);
    }
}

// 返回距离 start 最远的节点，并让 far_dis/far_par 记录本次搜索结果。
int find_farthest(int start) {
    dfs_dist(start, 0, 0);
    int far = start;
    for (int u = 1; u <= n; u++) {
        if (far_dis[u] > far_dis[far])
            far = u;
    }
    return far;
}

// 两次最远点搜索求出直径 A-B，并把直径路径与坐标存好。
void get_diameter() {
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
        int u = dia_node[i];
        on_dia[u] = true;
        dia_pos[u] = far_dis[u]; // 第二次搜索的距离数组正是各点到 A 的距离
    }
}

// 统计直径节点 u 挂载的直径外子树的最大深度，用 best 带回。
void dfs_branch(int u, int fa, int d, int& best) {
    if (d > best)
        best = d;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (v == fa || on_dia[v])
            continue;
        dfs_branch(v, u, d + w, best);
    }
}

// 对每个直径节点求其直径外子树深度，取全局最大值。
void compute_branch_max() {
    for (int i = 0; i < dia_cnt; i++) {
        int best = 0;
        dfs_branch(dia_node[i], 0, 0, best);
        if (best > branch_max)
            branch_max = best;
    }
}

void solve() {
    int diameter_len = dia_pos[dia_node[dia_cnt - 1]]; // 直径长度 = B 到 A 的距离
    int ans = diameter_len;                            // 偏心距不可能超过直径长度
    int r = 0;
    for (int l = 0; l < dia_cnt; l++) {
        if (r < l)
            r = l;
        // 固定左端点 l，右端点 r 尽量右移，保持区间长度不超过 s。
        while (r + 1 < dia_cnt &&
               dia_pos[dia_node[r + 1]] - dia_pos[dia_node[l]] <= s) {
            r++;
        }
        // 偏心距 = max(A 到左端点, 右端点到 B, 直径外子树最大深度)
        int left_dist = dia_pos[dia_node[l]];
        int right_dist = diameter_len - dia_pos[dia_node[r]];
        int ecc = max(max(left_dist, right_dist), branch_max);
        if (ecc < ans)
            ans = ecc;
    }
    cout << ans << endl;
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

    get_diameter();
    compute_branch_max();
    solve();

    return 0;
}
