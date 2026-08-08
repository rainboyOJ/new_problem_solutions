#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2500 + 5;
const int MAXM = 6200 * 2 + 5;
const long long INF = (1LL << 60);

struct Node {
    int u;
    long long dist;

    bool operator < (const Node &other) const {
        return dist > other.dist;
    }
};

int n, m, s, t;
int head[MAXN], to[MAXM], nxt[MAXM], weight_arr[MAXM], edge_cnt;
long long dist_arr[MAXN];
bool vis[MAXN];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
}

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_arr[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<Node> pq;
    dist_arr[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = dist_arr[u] + weight_arr[i];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({v, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(s);
    cout << dist_arr[t] << '\n';

    return 0;
}
