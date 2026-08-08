#include <bits/stdc++.h>
using namespace std;

const int MAXP = 100000 + 5;
const int MAXC = 200000 * 2 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int c, p, pb, pa1, pa2;
int head[MAXP], to[MAXC], nxt[MAXC], w[MAXC], edge_cnt;
long long dist_arr[MAXP];
bool vis[MAXP];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= p; i++) {
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

void dijkstra(int start) {
    for (int i = 1; i <= p; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;
    dist_arr[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = dist_arr[u] + w[i];
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

    cin >> c >> p >> pb >> pa1 >> pa2;
    init_graph();

    for (int i = 1; i <= c; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    dijkstra(pb);
    long long d_pb_a1 = dist_arr[pa1];
    long long d_pb_a2 = dist_arr[pa2];

    dijkstra(pa1);
    long long d_a1_a2 = dist_arr[pa2];

    // 只有两种顺序：
    // 1. PB -> PA1 -> PA2
    // 2. PB -> PA2 -> PA1
    long long ans1 = d_pb_a1 + d_a1_a2;
    long long ans2 = d_pb_a2 + d_a1_a2;

    cout << min(ans1, ans2) << '\n';

    return 0;
}
