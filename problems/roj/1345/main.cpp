/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:46
 * update_at: 2026-10-05 10:46
 */

// main.cpp：香甜的黄油。枚举糖放在哪个牧场，对每个候选跑一次堆优化 Dijkstra，
// 再按「该牧场上有几头牛」加权求和，取最小值。

#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 1005;   // 牧场数 P <= 800，留余量
const int MAXM = 3005;   // 道路数的两倍 2C <= 2900

const ll INF = 1000000000000000000LL; // 距离无穷大，求和时用不到它（不可达的候选会先被跳过）

int head[MAXN]; // head[u] 是 u 的第一条出边编号
int to[MAXM];   // to[e] 是边 e 的终点
int wei[MAXM];  // wei[e] 是边 e 的长度
int nxt[MAXM];  // nxt[e] 是 u 的下一条出边
int edge_cnt;   // 已加入的边数

ll cow_cnt[MAXN]; // cow_cnt[v] 是站在牧场 v 上的奶牛头数
ll dist[MAXN];    // dist[v] 是当前源点到 v 的最短距离

int p; // 牧场数，P <= 800
ll n;  // 奶牛数
ll c;  // 道路数

// 加一条 u 与 v 之间长 w 的无向边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    wei[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 堆优化 Dijkstra：求 src 到所有牧场的最短距离，写入 dist[]。
void dijkstra(int src) {
    for (int i = 1; i <= p; i++) dist[i] = INF;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;
    dist[src] = 0;
    heap.push(make_pair(0, src));
    while (!heap.empty()) {
        pair<ll, int> top = heap.top();
        heap.pop();
        ll d = top.first;
        int u = top.second;
        if (d > dist[u]) continue; // 堆里的过期条目，已经有更短的距离定型
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            ll nd = d + wei[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                heap.push(make_pair(nd, v));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p >> c;
    for (ll i = 1; i <= n; i++) {
        ll pos;
        cin >> pos;
        cow_cnt[pos]++;
    }
    for (ll i = 1; i <= c; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        add_edge(a, b, w);
        add_edge(b, a, w);
    }

    ll best = INF;
    // 枚举糖放在哪个牧场，每个候选跑一次单源最短路。
    for (int src = 1; src <= p; src++) {
        dijkstra(src);
        ll total = 0;
        bool ok = true;
        for (int v = 1; v <= p; v++) {
            if (cow_cnt[v] == 0) continue;
            if (dist[v] == INF) { // 有牛不可达，这个牧场不合法，跳过
                ok = false;
                break;
            }
            total += cow_cnt[v] * dist[v];
        }
        if (ok && total < best) best = total;
    }

    cout << best << "\n";
    return 0;
}
