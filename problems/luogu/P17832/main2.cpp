#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 505;
const int MAXM = 500005;

struct LineInfo {
    int id;
    ll t;
};

struct Edge {
    int to;
    ll weight;
};

int c, n, m, d, q;
ll w[MAXM];
vector<LineInfo> station_lines[MAXM];
vector<Edge> line_graph[MAXN];
ll min_edge[MAXN][MAXN];

ll dist_line[MAXN];
bool vis_line[MAXN];

// 在线路图上运行单源/多源最短路
void dijkstra(const vector<LineInfo>& start_lines) {
    for (int i = 1; i <= n; i++) {
        dist_line[i] = INF;
        vis_line[i] = false;
    }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (const auto& line : start_lines) {
        if (line.t < dist_line[line.id]) {
            dist_line[line.id] = line.t;
            pq.push({dist_line[line.id], line.id});
        }
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis_line[u]) continue;
        vis_line[u] = true;

        for (const auto& edge : line_graph[u]) {
            int v = edge.to;
            if (dist_line[u] + edge.weight < dist_line[v]) {
                dist_line[v] = dist_line[u] + edge.weight;
                pq.push({dist_line[v], v});
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
        for (int j = 1; j <= n; j++) {
            min_edge[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int station;
            ll t;
            cin >> station >> t;
            station_lines[station].push_back({i, t});
        }
    }

    // 建立线路间直接换乘图
    for (int v = 1; v <= m; v++) {
        const auto& lines = station_lines[v];
        int sz = lines.size();
        for (int i = 0; i < sz; i++) {
            int l1 = lines[i].id;
            ll t1 = lines[i].t;
            for (int j = i + 1; j < sz; j++) {
                int l2 = lines[j].id;
                ll t2 = lines[j].t;
                ll cost = t1 + t2;
                if (cost < min_edge[l1][l2]) {
                    min_edge[l1][l2] = cost;
                    min_edge[l2][l1] = cost;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && min_edge[i][j] < INF) {
                line_graph[i].push_back({j, min_edge[i][j]});
            }
        }
    }

    // 对每个询问，在线路图上进行多源 Dijkstra
    for (int r = 0; r < q; r++) {
        int x, y;
        cin >> x >> y;
        dijkstra(station_lines[x]);
        ll min_cost = INF;
        for (const auto& ly : station_lines[y]) {
            if (dist_line[ly.id] < INF) {
                ll cur = dist_line[ly.id] + ly.t;
                if (cur < min_cost) {
                    min_cost = cur;
                }
            }
        }
        cout << w[x] + min_cost + w[y] << "\n";
    }

    return 0;
}
