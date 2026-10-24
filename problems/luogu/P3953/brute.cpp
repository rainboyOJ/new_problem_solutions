/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:38
 * update_at: 2026-10-23 23:38
 */
// brute.cpp：小数据暴力解（带严格状态环检测的 DFS，用于对拍验证，仅适用于极小图）
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100;
const int MAXM = 200;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

int head[MAXN], to_node[MAXM], nxt_edge[MAXM], edge_weight[MAXM], edge_cnt;
ll dis[MAXN];
bool vis_dijk[MAXN];
ll n, m, k, p;
ll ans_cnt;
bool infinite_paths;
bool in_stack_node[MAXN][500]; // 记录 (u, cur_len) 是否在搜索栈中

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to_node[edge_cnt] = v;
    edge_weight[edge_cnt] = w;
    nxt_edge[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 堆优化 Dijkstra 求 1 到各点的最短路
struct Node {
    int id;
    ll d;
    bool operator>(const Node &other) const { return d > other.d; }
};

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        vis_dijk[i] = false;
    }
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dis[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int u = top.id;
        if (vis_dijk[u]) continue;
        vis_dijk[u] = true;

        for (int e = head[u]; e; e = nxt_edge[e]) {
            int v = to_node[e];
            int w = edge_weight[e];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({v, dis[v]});
            }
        }
    }
}

// 检查从 u 能否走到达 n 且距离 <= dis[n] + k
bool can_reach(int start_u, ll cur_dist) {
    queue<pair<int, ll>> q;
    q.push({start_u, cur_dist});
    bool visited[MAXN];
    for (int i = 1; i <= n; i++) visited[i] = false;
    visited[start_u] = true;
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();
        if (u == n) return true;
        for (int e = head[u]; e; e = nxt_edge[e]) {
            int v = to_node[e];
            int w = edge_weight[e];
            if (!visited[v] && d + w <= dis[n] + k) {
                visited[v] = true;
                q.push({v, d + w});
            }
        }
    }
    return false;
}

// 暴力 DFS 搜索所有从 1 出发、长度不超过 dis[n] + k 的路径
void dfs(int u, ll cur_len) {
    if (infinite_paths) return;
    if (cur_len > dis[n] + k) return;

    if (in_stack_node[u][cur_len]) {
        // 在同样累计长度下再次到达同一个点 u，说明走了一个 0 环！
        // 且只要从 u 出发能够到达终点 n，就意味着有无穷多条合法路线
        if (can_reach(u, cur_len)) {
            infinite_paths = true;
        }
        return;
    }

    in_stack_node[u][cur_len] = true;

    if (u == n) {
        ans_cnt = (ans_cnt + 1) % p;
    }

    for (int e = head[u]; e; e = nxt_edge[e]) {
        int v = to_node[e];
        int w = edge_weight[e];
        dfs(v, cur_len + w);
        if (infinite_paths) return;
    }

    in_stack_node[u][cur_len] = false;
}

void solve() {
    cin >> n >> m >> k >> p;
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) head[i] = 0;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    dijkstra();
    if (dis[n] == INF) {
        cout << 0 << "\n";
        return;
    }

    ans_cnt = 0;
    infinite_paths = false;
    memset(in_stack_node, 0, sizeof(in_stack_node));

    dfs(1, 0);

    if (infinite_paths) {
        cout << -1 << "\n";
    } else {
        cout << ans_cnt % p << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
