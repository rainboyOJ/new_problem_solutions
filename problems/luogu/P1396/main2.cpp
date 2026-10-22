/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 16:59
 * update_at: 2026-10-21 17:30
 */
// 营救的第二种解法：瓶颈 Dijkstra。
// 把普通最短路 dist[v] = min(dist[u] + w) 里的「加法」换成「取 max」，
//   dist[v] = min over 路径 ( 路径上最大边权 )
// 转移写成 nd = max(dist[u], w)，其余结构与 Dijkstra 完全相同。
// 因为 max 对边权是单调不减的，非负边权下依然满足「弹出即定型」。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5;  // 区数上界 n <= 1e4
const ll INF = (1LL << 60);

struct Edge {
    int to;
    ll w;
};

int n, m, start_node, target_node;
vector<Edge> g[MAXN];  // g[u]：从 u 出发的全部边
ll dist_bottleneck[MAXN];  // dist_bottleneck[v]：s 到 v 的最小瓶颈值

void dijkstra() {
    for (int i = 1; i <= n; i++) dist_bottleneck[i] = INF;
    dist_bottleneck[start_node] = 0;

    // (当前瓶颈值, 点) 的小根堆
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> heap;
    heap.push({0, start_node});

    while (!heap.empty()) {
        ll current = heap.top().first;
        int u = heap.top().second;
        heap.pop();

        if (current > dist_bottleneck[u]) continue;  // 堆里的过期记录

        for (const Edge &e : g[u]) {
            // 唯一的改动：路径代价从「累加」变成「取已走部分的最大值」
            ll candidate = max(current, e.w);
            if (candidate < dist_bottleneck[e.to]) {
                dist_bottleneck[e.to] = candidate;
                heap.push({candidate, e.to});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_node >> target_node;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // 两个区之间可能有多条大道，都保留即可，Dijkstra 会取更优的那条
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dijkstra();
    cout << dist_bottleneck[target_node] << '\n';
    return 0;
}
