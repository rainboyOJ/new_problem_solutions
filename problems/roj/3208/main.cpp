/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 方格取数：拆点建网络，最小费用最大流（k 次单位流，费用取负）
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const ll INF = 1000000000000000000LL;

int size_v;
vector<vector<int> > graph;
vector<int> to;
vector<ll> cap, cost;

// 连一条 u->v 容量 c 费用 w 的弧，紧跟一条残量 0、费用相反的弧
void link(int u, int v, ll c, ll w) {
    graph[u].push_back((int)to.size());
    to.push_back(v);
    cap.push_back(c);
    cost.push_back(w);
    graph[v].push_back((int)to.size());
    to.push_back(u);
    cap.push_back(0);
    cost.push_back(-w);
}

// 源点到各点的最短路当初始势：拆点编号本身就是一个拓扑序
void dag_potential(vector<ll>& h, int s) {
    h.assign(size_v, INF);
    h[s] = 0;
    for (int u = 0; u < size_v; u++) {
        if (h[u] == INF) {
            continue;
        }
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int e = graph[u][i];
            if (cap[e] > 0 && h[u] + cost[e] < h[to[e]]) {
                h[to[e]] = h[u] + cost[e];
            }
        }
    }
}

// 从 s 往 t 送 need 次单位流，返回最小费用
ll min_cost_flow(int s, int t, int need) {
    vector<ll> h;
    dag_potential(h, s);
    ll total = 0;
    for (int it = 0; it < need; it++) {
        vector<ll> dist(size_v, INF);
        vector<int> prev(size_v, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
        dist[s] = 0;
        pq.push(make_pair(0LL, s));
        while (!pq.empty()) {
            pair<ll, int> top = pq.top();
            pq.pop();
            ll d = top.first;
            int u = top.second;
            if (d > dist[u]) {
                continue;
            }
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int e = graph[u][i];
                int v = to[e];
                if (cap[e] > 0) {
                    ll nd = d + cost[e] + h[u] - h[v]; // 约化费用
                    if (nd < dist[v]) {
                        dist[v] = nd;
                        prev[v] = e;
                        pq.push(make_pair(nd, v));
                    }
                }
            }
        }
        if (prev[t] < 0) {
            break; // 送不动了
        }
        for (int v = 0; v < size_v; v++) {
            h[v] += (dist[v] < INF ? dist[v] : 0);
        }
        vector<int> path;
        int v = t;
        while (v != s) {
            path.push_back(prev[v]);
            v = to[prev[v] ^ 1];
        }
        for (int i = 0; i < (int)path.size(); i++) {
            int e = path[i];
            cap[e] -= 1;
            cap[e ^ 1] += 1;
            total += cost[e];
        }
    }
    return total;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return 0;
    }
    vector<vector<ll> > grid(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &grid[i][j]);
        }
    }
    if (k == 0) {
        printf("0\n");
        return 0;
    }
    size_v = 2 * n * n; // 格子 i 拆成 入点 2i 与 出点 2i+1
    graph.assign(size_v, vector<int>());
    const int STEP[2][2] = {{0, 1}, {1, 0}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int u = 2 * (i * n + j);
            if (grid[i][j]) { // 第一条穿过它的路径拿走格子里的数
                link(u, u + 1, 1, -grid[i][j]);
            }
            link(u, u + 1, k, 0); // 之后的路径只借道
            for (int s = 0; s < 2; s++) {
                int ni = i + STEP[s][0], nj = j + STEP[s][1];
                if (ni < n && nj < n) {
                    link(u + 1, 2 * (ni * n + nj), k, 0);
                }
            }
        }
    }
    printf("%lld\n", -min_cost_flow(0, size_v - 1, k));
    return 0;
}
