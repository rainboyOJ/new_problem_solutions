/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:05
 * update_at: 2026-10-05 04:05
 */

// 严格次小生成树（换边法）：
// 1. Kruskal 求出 MST，记录总权 w_mst、树的邻接表、每条原始边是否在树上；
// 2. 枚举每条非树边 (x,y,z)，在树上 BFS 求 x->y 路径上的最大边权 maxw；
// 3. 候选权值 = w_mst + z - maxw，要求 z > maxw（严格第二小，等权换边不算），
//    在全部候选中取最小。
// 本题 n <= 500, m <= 1e4，每条非树边 BFS 一次 O(n)，总 O(nm) 即可，无需倍增 LCA。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 505;
const int MAXM = 10005;

int n, m;
int fa[MAXN]; // Kruskal 并查集

// 边表：同时保存原始输入顺序，tree_edge[] 标记该边是否被 Kruskal 选中
struct Edge {
    int x, y;
    ll z;
};
Edge edges[MAXM];
bool tree_edge[MAXM];

// MST 的邻接表（树题规模小，用 vector 邻接表更直观）
vector<pair<int, ll> > g[MAXN];

// BFS 求树上路径最大边权用的数组
int parent[MAXN];        // BFS 树上的前驱节点，0 表示未访问
ll parent_w[MAXN];       // 前驱边（parent[v] -> v）的边权
int que[MAXN];           // 手写队列

// 并查集查找（路径压缩）。
int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

// Kruskal 排序用的比较函数：按下标比较边权。
bool cmp_edge(int a, int b) {
    return edges[a].z < edges[b].z;
}

// Kruskal 求最小生成树，返回 MST 总权值。
ll kruskal() {
    // 按边权从小到大排序；用下标排序，保留原始边编号以便标记 tree_edge
    int order[MAXM];
    for (int i = 1; i <= m; i++) order[i] = i;
    sort(order + 1, order + m + 1, cmp_edge);

    for (int i = 1; i <= n; i++) fa[i] = i;

    ll total = 0;
    int cnt = 0;
    for (int k = 1; k <= m; k++) {
        int i = order[k];
        int rx = find(edges[i].x), ry = find(edges[i].y);
        if (rx == ry) continue;
        fa[rx] = ry;
        total += edges[i].z;
        tree_edge[i] = true;
        cnt++;
        // 建树的邻接表
        g[edges[i].x].push_back(make_pair(edges[i].y, edges[i].z));
        g[edges[i].y].push_back(make_pair(edges[i].x, edges[i].z));
        if (cnt == n - 1) break;
    }
    return total;
}

// 在树上 BFS 求 u 到 target 的路径，返回路径上的最大边权。
// parent[v] 记录前驱，找到 target 后回溯取最大。
ll max_on_path(int u, int target) {
    for (int i = 1; i <= n; i++) parent[i] = 0;
    parent[u] = u;
    int head = 1, tail = 1;
    que[tail] = u;
    while (head <= tail) {
        int cur = que[head];
        head++;
        if (cur == target) break;
        for (int j = 0; j < (int)g[cur].size(); j++) {
            int nxt = g[cur][j].first;
            ll w = g[cur][j].second;
            if (parent[nxt] == 0) {
                parent[nxt] = cur;
                parent_w[nxt] = w;
                tail++;
                que[tail] = nxt;
            }
        }
    }
    // 从 target 沿前驱回溯到 u，取路径上最大边权
    ll best = 0;
    int cur = target;
    while (cur != u) {
        best = max(best, parent_w[cur]);
        cur = parent[cur];
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].x >> edges[i].y >> edges[i].z;
    }

    ll mst = kruskal();

    // 枚举每条非树边，换掉环上最大边得到候选生成树。
    // 必须要求 z > maxw：z == maxw 时换边后权值不变（等权换边，重边场景常见），
    // 候选值等于 MST 权值，不是严格第二小。
    ll ans = -1; // -1 表示还没有合法候选
    for (int i = 1; i <= m; i++) {
        if (tree_edge[i]) continue;
        ll maxw = max_on_path(edges[i].x, edges[i].y);
        if (edges[i].z <= maxw) continue;
        ll candidate = mst + edges[i].z - maxw;
        if (ans == -1 || candidate < ans) ans = candidate;
    }

    cout << ans << endl;
    return 0;
}
