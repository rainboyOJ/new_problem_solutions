#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 5;
const int MAXM = 100000 * 2 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, r;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;
long long dist1[MAXN], dist2[MAXN];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist1[i] = INF;
        dist2[i] = INF;
    }

    priority_queue<HeapNode> pq;
    dist1[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        long long d = cur.dist;

        if (d > dist2[u]) {
            continue;
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = d + w[i];

            // 如果找到了更短的最短路，原来的最短路就可能降级成次短路。
            if (nd < dist1[v]) {
                long long old_shortest = dist1[v];
                dist1[v] = nd;
                nd = old_shortest;
                pq.push({v, dist1[v]});
            }

            // 这里要求严格大于最短路，才能算次短路。
            if (dist1[v] < nd && nd < dist2[v]) {
                dist2[v] = nd;
                pq.push({v, dist2[v]});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r;
    init_graph();

    for (int i = 1; i <= r; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    dijkstra();

    cout << dist2[n] << '\n';

    return 0;
}
