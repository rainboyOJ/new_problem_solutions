/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:16
 * update_at: 2026-10-31 21:16
 */
// brute.cpp：站厅和线路都建点，每次询问跑 Dijkstra，用于小数据验证。
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXV = 500000 + 500 + 5;
const ll INF = 1LL << 60;

struct Edge {
    ll to;
    ll cost;
};

ll c, n, m, d, q;
ll w[MAXV]; // 各站地铁口到站厅的步行时间
vector<Edge> graph[MAXV]; // 1..m 是站厅，m+1..m+n 是线路
ll dist[MAXV]; // 起点站厅到各节点的最短距离

// 站厅和线路之间的边，可以表示上车或下车。
void add_edge(ll u, ll v, ll cost) {
    graph[u].push_back({v, cost});
    graph[v].push_back({u, cost});
}

ll dijkstra(ll start, ll target) {
    fill(dist + 1, dist + m + n + 1, INF);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> heap;
    dist[start] = 0;
    heap.push({0, start});
    while (!heap.empty()) {
        ll distance = heap.top().first;
        ll u = heap.top().second;
        heap.pop();
        if (distance != dist[u]) continue;
        if (u == target) return distance;
        for (const auto &edge : graph[u]) {
            if (dist[u] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.cost;
                heap.push({dist[edge.to], edge.to});
            }
        }
    }
    return dist[target];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> n >> m >> d >> q;
    for (ll v = 1; v <= m; v++) cin >> w[v];
    for (ll line = 1; line <= n; line++) {
        ll k;
        cin >> k;
        for (ll j = 1; j <= k; j++) {
            ll v, walk;
            cin >> v >> walk;
            add_edge(v, m + line, walk);
        }
    }
    while (q--) {
        ll x, y;
        cin >> x >> y;
        cout << w[x] + dijkstra(x, y) + w[y] << '\n';
    }
    return 0;
}
