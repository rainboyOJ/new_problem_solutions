/**
 * P1364 医院设置
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;

// 邻接表建无向树
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int w[MAXN]; // 各结点人口数
int n;

void add_edge(int u, int v) {
    ++edge_cnt;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// BFS 求从 start 出发到所有点的距离总和
int bfs(int start) {
    int dist[MAXN];
    memset(dist, -1, sizeof(dist));
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    int sum = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        sum += w[u] * dist[u]; // 人口 × 距离
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return sum;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int l, r;
        scanf("%d%d%d", &w[i], &l, &r);
        if (l) { add_edge(i, l); add_edge(l, i); }
        if (r) { add_edge(i, r); add_edge(r, i); }
    }
    int ans = INF;
    for (int i = 1; i <= n; ++i) ans = min(ans, bfs(i));
    printf("%d\n", ans);
    return 0;
}
