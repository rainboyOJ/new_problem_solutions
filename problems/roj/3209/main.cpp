/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1000000000000000000LL; // 不可达哨兵

int n, m, s, f;
// 邻接表：first 是边权，second 是去向
vector<pair<ll, int> > adj[1005];
ll base[1005];      // src 到每个点的最短路长度
ll ways[2005];      // 拆点 2*v+k 的路径条数
ll dist2[2005];     // 拆点状态的总长（base[v]+k）

// 第一遍 Dijkstra：求 src 到每个点的最短路 base[]
void shortest_from(int src) {
    for (int i = 1; i <= n; i++) base[i] = INF;
    base[src] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(0LL, src));
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > base[u]) continue;
        for (size_t i = 0; i < adj[u].size(); i++) {
            ll w = adj[u][i].first;
            int v = adj[u][i].second;
            ll nd = d + w;
            if (nd < base[v]) {
                base[v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }
}

// 第二遍分层 Dijkstra：统计最短路与「恰好长 1」的次短路条数之和
ll count_routes(int src, int dst) {
    shortest_from(src);
    for (int i = 0; i < 2 * n + 2; i++) {
        ways[i] = 0;
        dist2[i] = INF;
    }
    int start_node = 2 * src;           // k = 0 层
    ways[start_node] = 1;
    dist2[start_node] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(0LL, start_node));
    while (!pq.empty()) {
        ll d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        int v = node >> 1;
        ll cnt = ways[node];
        for (size_t i = 0; i < adj[v].size(); i++) {
            ll w = adj[v][i].first;
            int to = adj[v][i].second;
            ll nd = d + w;
            ll over = nd - base[to];   // 相对最短路超出的单位数
            if (over > 1) continue;    // 比最短路多 1 以上，丢弃
            int nxt = 2 * to + (int)over;
            if (ways[nxt] == 0) {      // 首次到达该状态，总长已定型
                dist2[nxt] = nd;
                pq.push(make_pair(nd, nxt));
            }
            ways[nxt] += cnt;
        }
    }
    return ways[2 * dst] + ways[2 * dst + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < m; i++) {
            int a, b;
            ll len;
            cin >> a >> b >> len;
            adj[a].push_back(make_pair(len, b));  // 平行边各自独立
        }
        cin >> s >> f;
        cout << count_routes(s, f) << "\n";
    }
    return 0;
}
