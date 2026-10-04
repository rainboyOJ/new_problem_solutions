/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:33
 * update_at: 2026-10-05 04:33
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;    // 农场数上限（N <= 1000）
const int MAXM = 100005;  // 每个图的边数上限（M <= 100000）
const ll INF = 1e18;

int n, m, x; // n 头牛、m 条有向道路、派对农场编号 x

// 正向图：链式前向星，用来求 x 到各点的最短路（回程）
int head[MAXN], nxt[MAXM], to[MAXM];
ll w[MAXM];
int edge_cnt;

// 反向图：把每条边 u->v 倒过来存成 v->u，用来求各点到 x 的最短路（去程）
// 因为原图中 i 到 x 的最短路，等于反向图中 x 到 i 的最短路。
int rev_head[MAXN], rev_nxt[MAXM], rev_to[MAXM];
ll rev_w[MAXM];
int rev_edge_cnt;

ll dist_from_x[MAXN]; // dist_from_x[i]：原图中 x -> i 的最短路长度
ll dist_to_x[MAXN];   // dist_to_x[i]：反向图中 x -> i 的最短路长度，即原图 i -> x

// 向正向图加一条 u -> v、长度 c 的边。
void add_edge(int u, int v, ll c) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = c;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 向反向图加一条 u -> v、长度 c 的边（存的是原图 v -> u 的反向边）。
void add_rev_edge(int u, int v, ll c) {
    rev_edge_cnt++;
    rev_to[rev_edge_cnt] = v;
    rev_w[rev_edge_cnt] = c;
    rev_nxt[rev_edge_cnt] = rev_head[u];
    rev_head[u] = rev_edge_cnt;
}

// 堆优化 Dijkstra：在给定的图上求源点 start 到所有点的最短路，结果写入 dist。
// 传入一组链式前向星数组，让正向图与反向图共用同一份松弛逻辑。
void dijkstra(int start, int *g_head, int *g_nxt, int *g_to, ll *g_w, ll *dist) {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;

    // 小根堆，元素为 (当前最短路长度, 顶点编号)
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d > dist[u]) continue; // 堆里过期的旧记录，直接跳过

        for (int i = g_head[u]; i; i = g_nxt[i]) {
            int v = g_to[i];
            if (dist[u] + g_w[i] < dist[v]) {
                dist[v] = dist[u] + g_w[i];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void read_input() {
    cin >> n >> m >> x;
    for (int i = 1; i <= m; i++) {
        int a, b;
        ll t;
        cin >> a >> b >> t;
        add_edge(a, b, t);     // 原图 a -> b
        add_rev_edge(b, a, t); // 反向图 b -> a，等价于把原边倒过来
    }
}

void solve() {
    // 回程：在原图上以 x 为源点做一次 Dijkstra
    dijkstra(x, head, nxt, to, w, dist_from_x);
    // 去程：在反向图上以 x 为源点做一次 Dijkstra
    dijkstra(x, rev_head, rev_nxt, rev_to, rev_w, dist_to_x);

    // 每头牛的花费是去程加回程，答案取其中最大的一条
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll round_trip = dist_to_x[i] + dist_from_x[i];
        if (round_trip > ans) ans = round_trip;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
