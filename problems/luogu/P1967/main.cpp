/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 21:38
 * update_at: 2026-10-22 12:25
 */
// 货车运输：多次询问无向带权图中两点之间「路径最小边权」的最大值（最大瓶颈路）。
// 做法：Kruskal 按边权从大到小建最大生成森林，把原图瓶颈信息压缩成树上唯一路径，
// 再用倍增 LCA 在向上跳的同时维护路径最小边权，每个询问 O(log n)。
// 图不连通：森林天然分多个连通块，跨块询问输出 -1。
//
// 为什么树路径最小边权 = 原图最大瓶颈值（证明要点）：
// 设按权从大到小加边时 x、y 首次连通于权 W，则
//   只用权 >= W 的边已能连通 x、y，故答案 >= W；
//   只用权 > W 的边还不能连通 x、y，故任何 x->y 路径必含权 <= W 的边，答案 <= W。
// 而 Kruskal 结束时 x、y 在同一棵树里，树上路径都是已加入的边（权 >= W），
// 且两端到 LCA 的两段里必有一段含权恰为 W 的关键边，最小值恰为 W。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;    // 城市数上界 n <= 1e4
const int MAXM = 50005;    // 道路数上界 m <= 5e4
const int LOG = 15;        // 2^14 = 16384 > 1e4，够覆盖树深
const int INF = 1000000000;

// 一条无向道路：连接 u 和 v，限重 w。点编号 1..n。
struct Edge {
    int u;
    int v;
    int w;
};

int n, m, q;
Edge edge[MAXM];

// Kruskal 用的并查集
int father[MAXN];

// 最大生成森林（链式前向星存树边，双向）
int head[MAXN], to[MAXM * 2], weight_edge[MAXM * 2], nxt[MAXM * 2], edge_cnt;

int depth_node[MAXN];      // 树上深度，根为 1
int component[MAXN];       // 点所在的连通块编号，跨块询问输出 -1
int up[MAXN][LOG];         // up[x][j]：x 向上跳 2^j 条边到达的祖先，根之上为 0
int min_edge[MAXN][LOG];   // min_edge[x][j]：这段 2^j 条边的路径上最小限重

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w > b.w;  // 最大生成森林：从大边开始加
}

int find_root(int x) {
    if (father[x] == x) {
        return x;
    }
    father[x] = find_root(father[x]);
    return father[x];
}

bool merge_set(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx == ry) {
        return false;  // 已在同一集合，加这条边会成环，不进森林
    }
    father[rx] = ry;
    return true;
}

void add_tree_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
}

void build_maximum_spanning_forest() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
    sort(edge + 1, edge + m + 1, cmp_edge);

    for (int i = 1; i <= m; i++) {
        if (merge_set(edge[i].u, edge[i].v)) {
            // 这条边连接了两个不同集合，进入最大生成森林
            add_tree_edge(edge[i].u, edge[i].v, edge[i].w);
            add_tree_edge(edge[i].v, edge[i].u, edge[i].w);
        }
    }
}

// 从 start 出发 BFS 遍历一个连通块，同时按层填倍增表
void bfs_component(int start, int cid) {
    queue<int> que;
    que.push(start);
    component[start] = cid;
    depth_node[start] = 1;
    up[start][0] = 0;
    min_edge[start][0] = INF;  // 根没有父边，填 INF 不影响取 min

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        // 出队时填表：此时 u 的 2^(j-1) 级祖先的表已填好
        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
            min_edge[u][j] = min(min_edge[u][j - 1], min_edge[up[u][j - 1]][j - 1]);
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;  // 不走回父节点
            }
            component[v] = cid;
            depth_node[v] = depth_node[u] + 1;
            up[v][0] = u;
            min_edge[v][0] = weight_edge[i];
            que.push(v);
        }
    }
}

void prepare_lca() {
    int cid = 0;
    for (int i = 1; i <= n; i++) {
        if (component[i] == 0) {
            cid++;
            bfs_component(i, cid);  // 每个连通块单独 BFS，根深度为 1
        }
    }
}

// 询问 x 到 y 的最大载重：同块时是树上路径的最小边权，跨块为 -1
int query(int x, int y) {
    if (component[x] != component[y]) {
        return -1;  // 不在同一连通块，货车无法到达
    }

    int answer = INF;
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);  // 让 x 是更深的那个
    }

    // 第一步：把 x 跳到与 y 同深度，沿途取最小边权
    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            answer = min(answer, min_edge[x][j]);
            x = up[x][j];
        }
    }

    if (x == y) {
        return answer;  // y 本来就是 x 的祖先
    }

    // 第二步：两个点一起向上跳，跳到 LCA 的儿子为止
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            answer = min(answer, min_edge[x][j]);
            answer = min(answer, min_edge[y][j]);
            x = up[x][j];
            y = up[y][j];
        }
    }

    // 最后一步：各自跳到 LCA，这两条父边也是路径的一部分
    answer = min(answer, min_edge[x][0]);
    answer = min(answer, min_edge[y][0]);
    return answer;
}

void solve() {
    build_maximum_spanning_forest();
    prepare_lca();

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
