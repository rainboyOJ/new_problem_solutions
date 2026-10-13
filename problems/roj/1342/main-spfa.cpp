/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-13 16:31
 * update_at: 2026-10-13 16:31
 */
// main-spfa.cpp：链式前向星存图 + SPFA 求单源最短路。
// 和 main.cpp（Floyd 全源最短路）解同一道题：本题只问 s 到 t 一条距离，
// 单源算法比全源更省（Floyd 要 O(n^3)，SPFA 平均 O(k*m)）；n ≤ 100 时两者都能过。

#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

typedef long long ll;

const int maxn = 105;      // 点数上界：n ≤ 100
const int maxm = maxn * maxn; // 连线数上界：最多 maxn 个点两两连线
const double INF = 1e100;  // 不可达哨兵：加任何有限边权后仍是它自己，不会造出假最短路

int n, m, s, t;
double px[maxn], py[maxn]; // 每个点的坐标

// 链式前向星：一条有向边记终点、权值、同起点的下一条边
struct Edge {
    int to;
    double w;
    int nxt; // 同一起点边表中的下一条边，0 表示没有了
};
Edge edge[2 * maxm]; // 每条连线是无向边，拆成两条有向边，所以开两倍
int head[maxn];      // head[u] 是 u 的边表头，0 表示空表；-1 表示没放过边
int edge_cnt;        // 已加入的边数，add_edge 用它开新边

// 加一条有向边 u -> v，边权 w
void add_edge(int u, int v, double w) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].w = w;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

// 两点间直线距离，也就是这条连线的边权
double dist(int u, int v) {
    double dx = px[u] - px[v];
    double dy = py[u] - py[v];
    return sqrt(dx * dx + dy * dy);
}

// SPFA：只有被松弛过的点才可能继续松弛别人，用队列存这些点
double spfa() {
    double dis[maxn];  // dis[i] 是当前从 s 到 i 的最短距离
    int in_queue[maxn]; // in_queue[i] 表示 i 是否正在队列里，避免重复入队

    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        in_queue[i] = 0;
    }
    dis[s] = 0;

    queue<int> q;
    q.push(s);
    in_queue[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = 0;

        // 扫 u 的整条边表，尝试用 u 松弛每个邻居 v
        for (int e = head[u]; e != 0; e = edge[e].nxt) {
            int v = edge[e].to;
            double nd = dis[u] + edge[e].w;
            if (nd < dis[v]) {
                dis[v] = nd;
                if (!in_queue[v]) { // 队列里已经有 v 就不用重复放
                    q.push(v);
                    in_queue[v] = 1;
                }
            }
        }
    }
    return dis[t];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf %lf", &px[i], &py[i]);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        double w = dist(u, v);
        add_edge(u, v, w); // 无向边：两个方向各加一条
        add_edge(v, u, w);
    }

    scanf("%d %d", &s, &t);
    printf("%.2f\n", spfa());
    return 0;
}
