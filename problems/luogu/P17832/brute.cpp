#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXM = 500005;
const int MAXN = 505;

int c, n, m, d, q;
ll w[MAXM];

// 站点-线路二部图
// 站点编号: 1 ~ m
// 线路编号: m + 1 ~ m + n
struct Edge {
    int to;
    ll weight;
};

vector<Edge> g[MAXM + MAXN];
ll dist_dijk[MAXM + MAXN];
bool vis[MAXM + MAXN];

void dijkstra(int start_node) {
    int total_nodes = m + n;
    for (int i = 1; i <= total_nodes; i++) {
        dist_dijk[i] = INF;
        vis[i] = false;
    }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist_dijk[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;

        for (const auto& edge : g[u]) {
            int v = edge.to;
            if (dist_dijk[u] + edge.weight < dist_dijk[v]) {
                dist_dijk[v] = dist_dijk[u] + edge.weight;
                pq.push({dist_dijk[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> c >> n >> m >> d >> q)) return 0;

    for (int i = 1; i <= m; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        int line_node = m + i;
        for (int j = 0; j < k; j++) {
            int station;
            ll t;
            cin >> station >> t;
            // 站点 station 到线路 line_node 的双向边，权值为 t
            g[station].push_back({line_node, t});
            g[line_node].push_back({station, t});
        }
    }

    for (int r = 0; r < q; r++) {
        int x, y;
        cin >> x >> y;
        dijkstra(x);
        ll ans = w[x] + dist_dijk[y] + w[y];
        cout << ans << "\n";
    }

    return 0;
}
