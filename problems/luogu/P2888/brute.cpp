// brute.cpp：对每个询问单独跑一次“最小化最大边权”的 Dijkstra。
// 只适合小数据，但很适合帮助理解瓶颈路定义并做对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 4005;
const int INF = 1e9;

struct HeapNode {
    int u;
    int cost;

    bool operator < (const HeapNode &other) const {
        return cost > other.cost;
    }
};

int n, m, t;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;
int dist_arr[MAXN];
bool vis[MAXN];

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// dist[v] 表示：从 start 到 v 的所有路径里，
// “路径上最大边权”这个值的最小可能值。
void dijkstra_minimax(int start) {
    for (int i = 1; i <= n; i++) {
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
            int nd = max(dist_arr[u], w[i]);
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

    cin >> n >> m >> t;

    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
    edge_cnt = 0;

    for (int i = 1; i <= m; i++) {
        int u, v, h;
        cin >> u >> v >> h;
        add_edge(u, v, h);
    }

    while (t--) {
        int a, b;
        cin >> a >> b;
        dijkstra_minimax(a);

        if (dist_arr[b] == INF) {
            cout << -1 << '\n';
        }
        else {
            cout << dist_arr[b] << '\n';
        }
    }

    return 0;
}
