/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-18 20:26
 * update_at: 2026-10-18 20:48
 */
// main2.cpp：显式建分层图，再在展开后的图上跑一次普通 Dijkstra。
// 与 main.cpp 的二维 dis 写法等价：这里把「用了几次免费」变成点编号的一部分。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5;   // 城市数上限
const int MAXK = 10 + 1;      // k 上限 10，层数是 k+1
const int MAXV = MAXN * MAXK; // 分层图点数 = n * (k + 1)
const ll INF = (1LL << 60);

// 分层图上的一条有向边：终点 v（已含层号）和花费 w。
struct Edge {
    int v;
    int w;
};

int n, m, k;
int s, t;
vector<Edge> g[MAXV]; // g[u]：分层图上状态 u 的所有出边
ll dist_arr[MAXV];    // dist_arr[u]：分层图上编号 u 的状态到起点的最短花费
bool done[MAXV];      // done[u]：编号 u 的状态是否已经定稿

// 分层图上的小根堆结点：距离小的先出队。
struct HeapNode {
    ll dist;
    int u;

    bool operator<(const HeapNode &other) const {
        return dist > other.dist;
    }
};

// 第 layer 层里城市 u 的编号：城市编号 0..n-1 直接拼上层号。
int node_id(int u, int layer) {
    return u + layer * n;
}

void add_edge(int u, int v, int len) {
    g[u].push_back({v, len});
}

void build_graph() {
    cin >> n >> m >> k;
    cin >> s >> t;

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;

        for (int layer = 0; layer <= k; layer++) {
            // 同一层内部：正常付费坐一次飞机，双向。
            add_edge(node_id(u, layer), node_id(v, layer), len);
            add_edge(node_id(v, layer), node_id(u, layer), len);

            // 层与层之间：花掉一次免费机会，以 0 代价从本层降到下一层。
            // 边是单向的，只能往下走，保证免费次数只会变多。
            if (layer < k) {
                add_edge(node_id(u, layer), node_id(v, layer + 1), 0);
                add_edge(node_id(v, layer), node_id(u, layer + 1), 0);
            }
        }
    }
}

void dijkstra(int start) {
    int total = n * (k + 1);
    for (int u = 0; u < total; u++) {
        dist_arr[u] = INF;
        done[u] = false;
    }

    priority_queue<HeapNode> pq;
    dist_arr[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (done[u]) {
            continue;
        }
        done[u] = true;

        for (const auto &e : g[u]) {
            int v = e.v;
            ll nd = dist_arr[u] + e.w;
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({nd, v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_graph();

    // 从第 0 层的起点出发（此时一次免费机会都没用）。
    dijkstra(node_id(s, 0));

    // 题目说的是「最多 k 次」，所以每一层的终点都可能是答案。
    // 只取第 k 层会错：最短路可能只用了不到 k 次机会，第 k 层甚至不可达。
    ll answer = INF;
    for (int layer = 0; layer <= k; layer++) {
        ll candidate = dist_arr[node_id(t, layer)];
        if (candidate < answer) {
            answer = candidate;
        }
    }

    cout << answer << '\n';

    return 0;
}
