/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:56
 * update_at: 2026-10-07 18:56
 */
// 一本通 1725 账本核算：前缀和 + 差分约束，Bellman-Ford 判负环。
// 记 s[i] = A[1] + ... + A[i]，则「第 x..y 月总收入 = w」就是 s[y] - s[x-1] = w。
// 只要这组等式有整数解，就能反推出一个合法账本；有负环说明等式组自相矛盾。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXV = 105;  // 结点 0..n 表示前缀和 s[0..n]，另有虚源，n < 100
const int MAXE = 512;  // 每条信息拆成 2 条有向边，再加 n+1 条虚源边，总数 < 300

struct Edge {
    int to;    // 终点
    ll w;      // 边权
    int nxt;   // 链式前向星里的下一条出边编号
};

int head[MAXV];   // head[u] = u 的第一条出边编号，0 表示没有出边
Edge edge[MAXE];  // 边表，1 号边开始使用
int edge_cnt;     // 已加入的边数
ll dist[MAXV];    // dist[v] = 当前求得的 s[v] 上界（虚源到 v 的最短路）

// 加入一条 u -> v、权为 w 的有向边
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].w = w;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

void solve() {
    int T;
    scanf("%d", &T);

    while (T-- > 0) {
        int n, m;
        scanf("%d %d", &n, &m);

        int src = n + 1;  // 虚源：向所有前缀和结点连 0 权边，保证全图可达
        int V = n + 2;    // 结点 0..n 加上虚源，共 V 个

        edge_cnt = 0;
        for (int i = 0; i < V; i++) head[i] = 0;

        for (int i = 0; i < m; i++) {
            int x, y;
            ll w;
            scanf("%d %d %lld", &x, &y, &w);
            // s[y] - s[x-1] = w 拆成两条三角不等式：
            //   s[y] <= s[x-1] + w 与 s[x-1] <= s[y] - w
            add_edge(x - 1, y, w);
            add_edge(y, x - 1, -w);
        }
        for (int i = 0; i <= n; i++) add_edge(src, i, 0);

        // 全 0 初值等价于「虚源的 0 权入边已经松弛过一轮」
        for (int i = 0; i < V; i++) dist[i] = 0;

        bool has_negative_cycle = false;
        for (int it = 0; it < V; it++) {
            bool changed = false;
            for (int u = 0; u < V; u++) {
                for (int e = head[u]; e; e = edge[e].nxt) {
                    int v = edge[e].to;
                    if (dist[u] + edge[e].w < dist[v]) {
                        dist[v] = dist[u] + edge[e].w;
                        changed = true;
                    }
                }
            }
            if (!changed) break;              // 已经收敛，说明无负环
            if (it == V - 1) has_negative_cycle = true;  // 第 V 轮仍能松弛 => 有负环
        }

        printf(has_negative_cycle ? "false\n" : "true\n");
    }
}

int main() {
    solve();
    return 0;
}
