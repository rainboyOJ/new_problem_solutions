#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000 + 5;
const int MAXM = 50000 * 2 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    int used;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m, k;
int s, t;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;
long long dist_arr[MAXN][15];
bool vis[MAXN][15];

void init_graph() {
    edge_cnt = 0;
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dist_arr[i][j] = INF;
            vis[i][j] = false;
        }
    }

    priority_queue<HeapNode> pq;
    dist_arr[s][0] = 0;
    pq.push({s, 0, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        int used = cur.used;
        if (vis[u][used]) {
            continue;
        }
        vis[u][used] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];

            long long nd = dist_arr[u][used] + w[i];
            if (nd < dist_arr[v][used]) {
                dist_arr[v][used] = nd;
                pq.push({v, used, nd});
            }

            // 这条航线可以免费坐一次，相当于跳到下一层且不增加代价。
            if (used < k && dist_arr[u][used] < dist_arr[v][used + 1]) {
                dist_arr[v][used + 1] = dist_arr[u][used];
                pq.push({v, used + 1, dist_arr[v][used + 1]});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    cin >> s >> t;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    dijkstra();

    long long answer = INF;
    for (int used = 0; used <= k; used++) {
        if (dist_arr[t][used] < answer) {
            answer = dist_arr[t][used];
        }
    }

    cout << answer << '\n';

    return 0;
}
