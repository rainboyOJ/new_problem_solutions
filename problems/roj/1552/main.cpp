/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:44
 * update_at: 2026-10-05 07:44
 */

// main.cpp：树上两点距离询问。
// 做法：BFS 求深度与父节点，倍增预处理 2^k 级祖先，单次询问 O(log n) 求 LCA，
// 再用公式 dist(u, v) = depth[u] + depth[v] - 2 * depth[lca] 得到距离。

#include <cstdio>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // n <= 10^5
const int MAXLOG = 18;   // 2^17 > 10^5，步长 18 层足够覆盖全树高度

// 链式前向星存树
struct Edge {
    int to;
    int next_edge;
};

Edge e[MAXN * 2]; // 无向边，正反各存一条
int head[MAXN];
int cnt_edge = 0;

int depth[MAXN];  // depth[u]：节点 u 的深度，根节点深度为 1
int up[MAXLOG][MAXN]; // up[k][u]：节点 u 沿父节点方向向上跳 2^k 步到达的祖先
bool vis[MAXN];   // BFS 时防止走回父节点
int n, q;

// 加一条无向边
void add_edge(int x, int y) {
    cnt_edge++;
    e[cnt_edge].to = y;
    e[cnt_edge].next_edge = head[x];
    head[x] = cnt_edge;
}

// BFS 建树：求每个点的深度和父节点 up[0][u]，迭代写法避免链状树递归爆栈
void bfs_build(int root) {
    queue<int> qu;
    qu.push(root);
    vis[root] = 1;
    depth[root] = 1;
    up[0][root] = 0; // 根节点没有父节点，跳 1 步出界记为 0

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        for (int i = head[u]; i != 0; i = e[i].next_edge) {
            int v = e[i].to;
            if (vis[v])
                continue;
            vis[v] = 1;
            depth[v] = depth[u] + 1;
            up[0][v] = u;
            qu.push(v);
        }
    }
}

// 倍增预处理：up[k][u] = up[k-1][ up[k-1][u] ]，即先跳 2^(k-1) 步再跳 2^(k-1) 步
void build_up_table() {
    for (int k = 1; k < MAXLOG; k++) {
        for (int u = 1; u <= n; u++) {
            up[k][u] = up[k - 1][up[k - 1][u]];
        }
    }
}

// 倍增求 u, v 的最近公共祖先（LCA）
int get_lca(int u, int v) {
    // 保证 u 是较深的那个点
    if (depth[u] < depth[v])
        swap(u, v);

    // 1. 把 u 按二进制拆分向上跳，提升到与 v 相同深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < MAXLOG; k++) {
        if ((diff >> k) & 1)
            u = up[k][u];
    }

    // 此时 u, v 同深度；u == v 说明 v 本来就是 u 的祖先
    if (u == v)
        return u;

    // 2. 从高位往低位试跳：只有当跳完 2^k 步后两点不同才跳，
    //    循环结束后 u, v 恰好停在 LCA 的两个不同子节点上
    for (int k = MAXLOG - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u]; // 再往上一格就是 LCA
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    bfs_build(1);
    build_up_table();

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int lca = get_lca(x, y);
        // 树上两点距离公式：u 到 LCA 的边数 + v 到 LCA 的边数
        // 深度最大 10^5，两深度之和约 2*10^5，int 不会溢出
        int dist = depth[x] + depth[y] - 2 * depth[lca];
        printf("%d\n", dist);
    }
    return 0;
}
