/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:30
 * update_at: 2026-10-05 12:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;           // 数据默认 long long
const ll INF = 1e18;            // 不可达标记
const int MAXN = 2005;          // 最多 n 个点

int n, m;
ll dist_arr[MAXN];              // dist_arr[i] 表示 1 到 i 的当前最短距离

// 邻接表：g[i] 存 (邻居, 边权)
vector<pair<int, int> > g[MAXN];

// 堆优化 Dijkstra：第一次弹出 n 即可返回最短距离，不可达返回 INF
ll dijkstra() {
    for (int i = 1; i <= n; i++) dist_arr[i] = INF;
    dist_arr[1] = 0;

    // 小根堆：按当前距离排序
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    q.push(make_pair(0, 1));

    while (!q.empty()) {
        pair<ll, int> cur = q.top();
        q.pop();
        ll d = cur.first;
        int u = cur.second;

        if (d > dist_arr[u]) continue;          // 过期记录，跳过
        if (u == n) return d;                   // 第一次弹出 n，已确定最短

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i].first;
            int w = g[u][i].second;
            if (dist_arr[u] + w < dist_arr[v]) {
                dist_arr[v] = dist_arr[u] + w;
                q.push(make_pair(dist_arr[v], v));
            }
        }
    }
    return INF;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));        // 无向图存反向边
    }

    ll ans = dijkstra();
    if (ans == INF) printf("-1\n");
    else printf("%lld\n", ans);
    return 0;
}
