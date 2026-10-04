/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:37
 */
// 排队布局：差分约束 + SPFA
// 设 x[i] 为第 i 头牛的坐标，三类约束统一写成 x[v] - x[u] <= w，从 u 向 v 连一条权为 w 的有向边：
//   顺序约束：x[i] <= x[i+1]，即 x[i] - x[i+1] <= 0，从 i+1 向 i 连权 0；
//   好感约束：x[b] - x[a] <= d，从 a 向 b 连权 d；
//   反感约束：x[b] - x[a] >= d，即 x[a] - x[b] <= -d，从 b 向 a 连权 -d。
// 先让所有点初值为 0 全部入队跑一次 SPFA 判全局负环：有负环则无解，输出 -1；
// 再以 1 号牛为源跑最短路：到不了 n 号牛说明距离可任意大，输出 -2，否则 dist[n] 就是最大距离。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;   // 节点数上限 N <= 1000
const int MAXM = 30005;  // 边数上限 (N-1) + M_L + M_D <= 20999
const ll INF = 1000000000000000000LL;  // 无穷大，不用 LLONG_MAX 以免加法溢出

// 链式前向星存图，边的含义是 x[to] - x[u] <= weight
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
ll weight[MAXM];  // 边权可能为负，必须用 ll

ll dist[MAXN];        // 单源最短路距离
bool in_queue[MAXN];  // 节点当前是否在队列中
int push_cnt[MAXN];   // 节点因松弛而入队的次数，达到 n 次说明存在负环

int n, ml, md;

// 加一条 u -> v、权 w 的有向边。
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// SPFA：source == 0 表示全局判负环（所有点初值 0 并一起入队，等价于建超级源点），
// 否则以 source 为源点求最短路。返回 true 表示图中存在负环。
bool spfa(int source) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        in_queue[i] = false;
        push_cnt[i] = 0;
        if (source == 0) {
            dist[i] = 0;  // 全局判环时所有点都是源点
            in_queue[i] = true;
            q.push(i);
        } else {
            dist[i] = INF;
        }
    }
    if (source != 0) {
        dist[source] = 0;
        in_queue[source] = true;
        q.push(source);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (dist[u] + weight[e] < dist[v]) {
                dist[v] = dist[u] + weight[e];
                if (!in_queue[v]) {
                    push_cnt[v]++;
                    if (push_cnt[v] >= n) return true;  // 同一节点入队 n 次，必有负环
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &ml, &md);

    for (int i = 1; i < n; i++) {
        add_edge(i + 1, i, 0);
    }
    for (int i = 0; i < ml; i++) {
        int a, b;
        ll d;
        scanf("%d%d%lld", &a, &b, &d);
        if (a > b) swap(a, b);
        add_edge(a, b, d);
    }
    for (int i = 0; i < md; i++) {
        int a, b;
        ll d;
        scanf("%d%d%lld", &a, &b, &d);
        if (a > b) swap(a, b);
        add_edge(b, a, -d);
    }

    if (spfa(0)) {
        printf("-1\n");
        return 0;
    }
    spfa(1);
    if (dist[n] == INF) {
        printf("-2\n");
    } else {
        printf("%lld\n", dist[n]);
    }
    return 0;
}
