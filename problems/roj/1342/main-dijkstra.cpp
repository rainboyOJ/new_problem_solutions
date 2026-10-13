/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-13 16:31
 * update_at: 2026-10-13 16:31
 */
// main-dijkstra.cpp：链式前向星存图 + 二叉堆优化 Dijkstra 求单源最短路。
// 和 main-spfa.cpp 同为单源解法，区别在正确性依据：本题边权是欧氏距离，
// 恒为非负，所以可以用 Dijkstra——每个点出堆时它的最短路已经确定，不再更新。

#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int maxn = 105;      // 点数上界：n ≤ 100
const int maxm = maxn * maxn; // 连线数上界：最多 maxn 个点两两连线
const double INF = 1e100;  // 不可达哨兵

int n, m, s, t;
double px[maxn], py[maxn]; // 每个点的坐标

// 链式前向星：一条有向边记终点、权值、同起点的下一条边
struct Edge {
    int to;
    double w;
    int nxt; // 同一起点边表中的下一条边，0 表示没有了
};
Edge edge[2 * maxm]; // 无向边拆两条有向边
int head[maxn];      // head[u] 是 u 的边表头，0 表示空表
int edge_cnt;        // 已加入的边数

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

// 小根堆的元素：first 是当前距离，second 是点编号；
// greater 让距离小的先出堆，first 相同时比较编号，不影响结果
typedef pair<double, int> Node;

// 堆优化 Dijkstra：每次取出当前距离最小的点，用它松弛邻居
double dijkstra() {
    double dis[maxn]; // dis[i] 是当前从 s 到 i 的最短距离
    int done[maxn];   // done[i] = 1 表示 i 已经出堆，最短路已确定

    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        done[i] = 0;
    }
    dis[s] = 0;

    priority_queue<Node, vector<Node>, greater<Node> > heap;
    heap.push(make_pair(0.0, s));
    while (!heap.empty()) {
        int u = heap.top().second; // 堆顶是还没确定的点里距离最小的
        heap.pop();
        if (done[u]) continue; // 同一个点可能进堆多次，只有第一次有用
        done[u] = 1;
        if (u == t) break;     // 只问 s 到 t，t 确定了就可以停

        // 扫 u 的整条边表，尝试用 u 松弛每个邻居 v
        for (int e = head[u]; e != 0; e = edge[e].nxt) {
            int v = edge[e].to;
            double nd = dis[u] + edge[e].w;
            if (nd < dis[v]) {
                dis[v] = nd;
                heap.push(make_pair(nd, v)); // 旧的 (dis, v) 留在堆里，靠 done 跳过
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
    printf("%.2f\n", dijkstra());
    return 0;
}
