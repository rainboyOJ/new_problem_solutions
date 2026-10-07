/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:28
 * update_at: 2026-10-06 10:28
 */
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXP = 805;
const ll INF = (1LL << 60);

int n, p, c;
int cnt[MAXP]; // cnt[u] 表示牧场 u 上的牛的数量

struct Edge {
    int to;
    int w;
    int next;
} e[MAXP * 4]; // 无向图，边数开两倍多一点
int head[MAXP], tot;

void add_edge(int u, int v, int w) {
    e[++tot].to = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}

// 从 src 出发的堆优化 Dijkstra，返回 dist 数组（下标 1..p）
void dijkstra(int src, ll dist[]) {
    for (int i = 1; i <= p; ++i) dist[i] = INF;
    dist[src] = 0;
    // pair<距离, 节点>，priority_queue 默认大根堆，用 greater 转小根堆
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    q.push(make_pair(0LL, src));
    while (!q.empty()) {
        pair<ll, int> cur = q.top();
        q.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d > dist[u]) continue; // 过期堆项
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            ll nd = d + e[i].w;
            if (nd < dist[v]) {
                dist[v] = nd;
                q.push(make_pair(nd, v));
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &p, &c);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++cnt[x];
    }
    for (int i = 1; i <= c; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        add_edge(a, b, w);
        add_edge(b, a, w);
    }

    ll ans = INF;
    ll dist[MAXP];
    for (int src = 1; src <= p; ++src) {
        dijkstra(src, dist);
        ll sum = 0;
        for (int u = 1; u <= p; ++u) {
            if (cnt[u] > 0) {
                sum += (ll)cnt[u] * dist[u];
            }
        }
        if (sum < ans) ans = sum;
    }

    printf("%lld\n", ans);
    return 0;
}
