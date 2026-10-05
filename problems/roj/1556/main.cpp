/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:03
 * update_at: 2026-10-05 08:03
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;
const int LOGN = 16; // 2^15 = 32768 > 10^4，15 级祖先足够

int n, m;
// 链式前向星存树：边是双向的，所以边数组开两倍
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], edge_cnt;
ll edge_w[2 * MAXN]; // 每条边的权值

int depth[MAXN]; // depth[u] 表示节点 u 的深度（根为 1，深度 0）
ll dist_root[MAXN]; // dist_root[u] 表示节点 u 到根节点的路径权值和
int up[MAXN][LOGN]; // up[u][k] 表示节点 u 的第 2^k 级祖先
bool visited[MAXN]; // BFS 时防止往父节点方向走回头路

int que[MAXN]; // BFS 用手写队列

// 加一条 u -> v、权值为 w 的无向边。
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_w[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 从根节点 1 开始 BFS，预处理深度、到根距离和倍增祖先数组。
void bfs_init() {
    int qhead = 1, qtail = 1;
    que[qtail] = 1;
    visited[1] = true;
    depth[1] = 0;
    dist_root[1] = 0;

    while (qhead <= qtail) {
        int u = que[qhead];
        qhead++;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (visited[v]) continue; // 树上只有父节点被访问过
            visited[v] = true;
            depth[v] = depth[u] + 1;
            dist_root[v] = dist_root[u] + edge_w[i];
            up[v][0] = u; // 第 2^0 = 1 级祖先就是父节点
            // 倍增转移：先跳 2^(k-1) 步，再跳 2^(k-1) 步
            for (int k = 1; k < LOGN; k++) {
                up[v][k] = up[up[v][k - 1]][k - 1];
            }
            qtail++;
            que[qtail] = v;
        }
    }
}

// 求节点 u 和 v 的最近公共祖先 (LCA)。
int query_lca(int u, int v) {
    // 保证 u 是较深的节点
    if (depth[u] < depth[v]) {
        int t = u; u = v; v = t;
    }
    // 第一步：把 u 跳升到与 v 相同的深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOGN; k++) {
        if ((diff >> k) & 1) {
            u = up[u][k];
        }
    }
    if (u == v) return u; // 较浅节点本身就是 LCA
    // 第二步：两点同步从大到小试跳，祖先相同的层不跳
    for (int k = LOGN - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    // 此时 u、v 的父节点就是 LCA
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edge_cnt = 0;
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        ll k;
        cin >> x >> y >> k;
        add_edge(x, y, k);
        add_edge(y, x, k);
    }

    bfs_init();

    // dist[u] + dist[v] - 2 * dist[lca]：两条到根的路径减去重叠部分的两倍
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        int lca = query_lca(x, y);
        cout << dist_root[x] + dist_root[y] - 2 * dist_root[lca] << "\n";
    }

    return 0;
}
