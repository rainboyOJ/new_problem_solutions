#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;
const long long INF = (1LL << 62);

int n, m, s;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
long long weight_edge[MAXM];
long long dist_arr[MAXN]; // dist_arr[u] 表示从源点 s 到 u 的当前最短路
bool done[MAXN];

struct Node {
    long long dist;
    int u;
    bool operator<(const Node &other) const {
        return dist > other.dist;
    }
};

void add_edge(int u, int v, long long w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
        done[i] = false;
    }

    priority_queue<Node> q;
    dist_arr[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        Node cur = q.top();
        q.pop();
        int u = cur.u;
        if (done[u]) {
            continue;
        }
        done[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long w = weight_edge[i];
            if (dist_arr[v] > dist_arr[u] + w) {
                dist_arr[v] = dist_arr[u] + w;
                q.push({dist_arr[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    dijkstra();

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << dist_arr[i];
    }
    cout << '\n';
    return 0;
}
