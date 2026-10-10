/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 城堡：Dijkstra 求最短路，再数每个点的“紧边”条数，方案数是紧边条数之积
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const ll MOD = (1LL << 31) - 1; // 答案要模的数 2^31 - 1
const ll INF = 1LL << 60;

struct Arc { // 邻接表里的一条出边
    int v;
    ll w;
};

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    vector<vector<Arc> > adj(n);
    vector<int> ex(m), ey(m);
    vector<ll> ew(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        ll w;
        scanf("%d %d %lld", &x, &y, &w);
        ex[i] = x - 1;
        ey[i] = y - 1;
        ew[i] = w;
        Arc a1 = {y - 1, w}, a2 = {x - 1, w};
        adj[x - 1].push_back(a1); // 通道双向
        adj[y - 1].push_back(a2);
    }

    // 堆里放 (距离, 编号) 的对，距离小的先出队
    vector<ll> dist(n, INF);
    dist[0] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(0LL, 0));
    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int u = top.second;
        if (d > dist[u]) {
            continue; // 已被更短的距离取代
        }
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].v;
            ll nd = d + adj[u][i].w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }

    // 紧边：D[另一端] + w 恰好等于 D[自己]；它只会算到距离更远的那一端
    vector<ll> tight(n, 0);
    for (int i = 0; i < m; i++) {
        if (dist[ex[i]] + ew[i] == dist[ey[i]]) {
            tight[ey[i]]++;
        } else if (dist[ey[i]] + ew[i] == dist[ex[i]]) {
            tight[ex[i]]++;
        }
    }

    ll ans = 1; // 每个房间 2..N 独立挑一条紧边当树边
    for (int v = 1; v < n; v++) {
        ans = ans * tight[v] % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
