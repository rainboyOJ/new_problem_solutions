/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:16
 * update_at: 2026-10-31 21:16
 */
// main2.cpp：在线路图上逐次跑 Dijkstra，适合询问较少的数据。
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 505;
const int MAXM = 500005;
const ll INF = 1LL << 60;

struct Platform {
    ll line;
    ll walk; // 站厅到这条线路站台的步行时间
};
struct Edge {
    ll to;
    ll cost;
};

ll c, n, m, d, q;
ll w[MAXM]; // 地铁口到站厅的时间
vector<Platform> station_lines[MAXM]; // 每站能上的线路及进站台时间
ll transfer[MAXN][MAXN]; // 两条线路直接换乘的最小费用
vector<Edge> graph[MAXN]; // 合并重边后的线路图
ll dist[MAXN]; // 当前询问从起点站厅到各条线路的最短距离

void read_input() {
    cin >> c >> n >> m >> d >> q;
    for (ll v = 1; v <= m; v++) cin >> w[v];
    for (ll line = 1; line <= n; line++) {
        ll k;
        cin >> k;
        for (ll j = 1; j <= k; j++) {
            ll v, walk;
            cin >> v >> walk;
            station_lines[v].push_back({line, walk});
        }
    }
}

// 先取同一对线路间最便宜的换乘站，再存成邻接表。
void build_transfer_graph() {
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) transfer[i][j] = INF;
    }
    for (ll v = 1; v <= m; v++) {
        for (const auto &from : station_lines[v]) {
            for (const auto &to : station_lines[v]) {
                ll cost = from.walk + to.walk;
                transfer[from.line][to.line] = min(transfer[from.line][to.line], cost);
            }
        }
    }
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (i != j && transfer[i][j] < INF) {
                graph[i].push_back({j, transfer[i][j]});
            }
        }
    }
}

// 从 x 站厅出发，可选的第一条线路都作为起点，初始费用是上站台的时间。
void dijkstra(ll x) {
    fill(dist + 1, dist + n + 1, INF);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> heap;
    for (const auto &first : station_lines[x]) {
        dist[first.line] = first.walk;
        heap.push({first.walk, first.line});
    }
    while (!heap.empty()) {
        ll distance = heap.top().first;
        ll u = heap.top().second;
        heap.pop();
        if (distance != dist[u]) continue; // 这条旧记录已被更短的路线替代
        for (const auto &edge : graph[u]) {
            if (dist[u] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.cost;
                heap.push({dist[edge.to], edge.to});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_transfer_graph();
    while (q--) {
        ll x, y;
        cin >> x >> y;
        dijkstra(x);
        ll answer = INF;
        for (const auto &last : station_lines[y]) {
            answer = min(answer, dist[last.line] + last.walk);
        }
        cout << w[x] + answer + w[y] << '\n';
    }
    return 0;
}
