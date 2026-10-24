/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:38
 * update_at: 2026-10-23 23:38
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;
const int MAXM = 200005;
const int MAXK = 55;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

// 正向图与反向图的链式前向星
int head_f[MAXN], to_f[MAXM], nxt_f[MAXM], weight_f[MAXM], edge_cnt_f;
int head_b[MAXN], to_b[MAXM], nxt_b[MAXM], weight_b[MAXM], edge_cnt_b;

// 最短路相关
ll dis_from_1[MAXN]; // 正向图从 1 出发的最短距离
ll dis_to_n[MAXN];   // 反向图从 n 出发的最短距离（即各点到 n 的最短距离）
bool vis_dijk[MAXN];

// 记忆化搜索与判环标记
ll dp[MAXN][MAXK];
bool in_stack[MAXN][MAXK]; // 正在搜索栈中，用于检测 0 环引起的死循环

int n, m, k;
ll p;
bool has_zero_cycle;

void add_edge_forward(int u, int v, int w) {
    edge_cnt_f++;
    to_f[edge_cnt_f] = v;
    weight_f[edge_cnt_f] = w;
    nxt_f[edge_cnt_f] = head_f[u];
    head_f[u] = edge_cnt_f;
}

void add_edge_backward(int u, int v, int w) {
    edge_cnt_b++;
    to_b[edge_cnt_b] = v;
    weight_b[edge_cnt_b] = w;
    nxt_b[edge_cnt_b] = head_b[u];
    head_b[u] = edge_cnt_b;
}

struct Node {
    int id;
    ll d;
    bool operator>(const Node &other) const {
        return d > other.d;
    }
};

// 堆优化 Dijkstra 求正向最短路
void dijkstra_from_1() {
    for (int i = 1; i <= n; i++) {
        dis_from_1[i] = INF;
        vis_dijk[i] = false;
    }
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dis_from_1[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int u = top.id;
        if (vis_dijk[u]) continue;
        vis_dijk[u] = true;

        for (int e = head_f[u]; e; e = nxt_f[e]) {
            int v = to_f[e];
            int w = weight_f[e];
            if (dis_from_1[v] > dis_from_1[u] + w) {
                dis_from_1[v] = dis_from_1[u] + w;
                pq.push({v, dis_from_1[v]});
            }
        }
    }
}

// 堆优化 Dijkstra 求反向最短路
void dijkstra_to_n() {
    for (int i = 1; i <= n; i++) {
        dis_to_n[i] = INF;
        vis_dijk[i] = false;
    }
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dis_to_n[n] = 0;
    pq.push({n, 0});

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int u = top.id;
        if (vis_dijk[u]) continue;
        vis_dijk[u] = true;

        for (int e = head_b[u]; e; e = nxt_b[e]) {
            int v = to_b[e];
            int w = weight_b[e];
            if (dis_to_n[v] > dis_to_n[u] + w) {
                dis_to_n[v] = dis_to_n[u] + w;
                pq.push({v, dis_to_n[v]});
            }
        }
    }
}

// 记忆化搜索：dfs(u, j) 表示从 u 走向 n，额外比 dis_to_n[u] 多花 j 的合法路线数
ll dfs(int u, int j) {
    if (j < 0 || j > k) return 0;
    if (in_stack[u][j]) {
        has_zero_cycle = true;
        return 0;
    }
    if (dp[u][j] != -1) {
        return dp[u][j];
    }

    in_stack[u][j] = true;
    ll total = 0;
    if (u == n && j == 0) {
        total = 1;
    }

    for (int e = head_f[u]; e; e = nxt_f[e]) {
        int v = to_f[e];
        int w = weight_f[e];
        if (dis_to_n[v] == INF) continue; // 无法到达终点

        ll extra = dis_to_n[v] + w - dis_to_n[u];
        ll next_j = j - extra;
        if (next_j >= 0 && next_j <= k) {
            total = (total + dfs(v, next_j)) % p;
            if (has_zero_cycle) return 0;
        }
    }

    in_stack[u][j] = false;
    dp[u][j] = total;
    return total;
}

void solve() {
    cin >> n >> m >> k >> p;

    edge_cnt_f = 0;
    edge_cnt_b = 0;
    for (int i = 1; i <= n; i++) {
        head_f[i] = 0;
        head_b[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge_forward(u, v, w);
        add_edge_backward(v, u, w);
    }

    dijkstra_from_1();
    dijkstra_to_n();

    // 无法从 1 到达 n
    if (dis_from_1[n] == INF) {
        cout << 0 << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = -1;
            in_stack[i][j] = false;
        }
    }

    has_zero_cycle = false;
    ll ans = 0;
    for (int j = 0; j <= k; j++) {
        ans = (ans + dfs(1, j)) % p;
        if (has_zero_cycle) {
            cout << -1 << "\n";
            return;
        }
    }

    cout << ans << "\n";
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
