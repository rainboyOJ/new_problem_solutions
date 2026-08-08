// brute.cpp：对每个源点跑一次 Dijkstra，求所有点对最短路和最短路条数。
// 再按定义公式累计每个点的重要程度。只适合小数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = (1LL << 60);

struct Edge {
    int to;
    long long w;
};

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m;
vector<Edge> g[MAXN];
long long dist_all[MAXN][MAXN];
long long cnt_all[MAXN][MAXN];
long double answer[MAXN];

void dijkstra(int start) {
    static long long dist_arr[MAXN];
    static long long cnt_arr[MAXN];
    static bool vis[MAXN];

    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
        cnt_arr[i] = 0;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;
    dist_arr[start] = 0;
    cnt_arr[start] = 1;
    pq.push({start, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            long long nd = dist_arr[u] + g[u][i].w;

            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                cnt_arr[v] = cnt_arr[u];
                pq.push({v, nd});
            }
            else if (nd == dist_arr[v]) {
                cnt_arr[v] += cnt_arr[u];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dist_all[start][i] = dist_arr[i];
        cnt_all[start][i] = cnt_arr[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        g[i].clear();
        answer[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for (int s = 1; s <= n; s++) {
        dijkstra(s);
    }

    for (int v = 1; v <= n; v++) {
        for (int s = 1; s <= n; s++) {
            if (s == v) {
                continue;
            }
            for (int t = 1; t <= n; t++) {
                if (t == v || t == s) {
                    continue;
                }
                if (dist_all[s][v] + dist_all[v][t] == dist_all[s][t]) {
                    answer[v] += (long double) cnt_all[s][v] * cnt_all[v][t] / cnt_all[s][t];
                }
            }
        }
    }

    cout << fixed << setprecision(3);
    for (int i = 1; i <= n; i++) {
        cout << (double) answer[i] << '\n';
    }

    return 0;
}
