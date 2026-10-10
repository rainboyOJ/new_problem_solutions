/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:43
 * update_at: 2026-10-07 18:43
 */
// 一本通 1723《交通》：期望意义下的最短路。
// 拥堵系数 a ~ U[0,1]，边 e 在 a 下的耗时 w_e(a) = a*x_e + (1-a)*y_e，
// 求 ∫_0^1 d(a) da，其中 d(a) 是 a 固定时 S->T 的最短路。
//
// 关键性质：一条路径 P 的代价是 a 的直线 cost_P(a) = Y_P + a*(X_P - Y_P)
// （X_P = Σx_e，Y_P = Σy_e），d(a) 是这些直线的下包络，因此 d(a) 在 [0,1] 上
// 凹且分段线性。凹函数在区间中点的函数值若等于两端点的弦值，则该区间上 d 就是
// 这条弦（凹函数在区间内一旦低于弦，中点必然被凸组合抬高），于是可以递归细分：
// 中点弦值相等就整段按梯形积分，否则说明区间内还有折点，二分继续。
// 直线斜率 X_P - Y_P 是整数，折点很少，实际只做几百次 Dijkstra。
//
// 来源说明：本题素材源带自造数据生成脚本，题面为网络重建版本，与官方原题可能有偏差；
// 随仓 std.cpp 只作算法参考，本文件按题面独立重写（链式前向星 + 同样的细分判定）。

#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 205;      // 顶点数上限（题面 n <= 200）
const int MAXM = 810;      // 有向边数上限（题面双向边 m <= 400，成对存）
const double INF = 1e300;  // 不可达的哨兵距离

struct Edge {
    int to;      // 边指向的点
    double x;    // 最拥堵时的耗时
    double y;    // 完全空闲时的耗时
};

Edge edge[MAXM];      // 链式前向星：所有有向边
int head[MAXN];       // head[u] 是 u 的第一条出边编号，0 表示没有
int nxt[MAXM];        // nxt[i] 是 i 的下一条同起点边编号
int edge_cnt;         // 已加入的有向边条数

int n, m, S, T;             // 点数、双向边数、起点、终点
double dist_arr[MAXN];      // 固定 a 时的单源最短路长度

// 加一条 u->v 的有向边
void add_edge(int u, int v, double x, double y) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].x = x;
    edge[edge_cnt].y = y;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 拥堵系数为 a 时从 S 到 T 的最短路（堆优化 Dijkstra），返回 dist[T]
double shortest_path(double a) {
    typedef pair<double, int> Node;
    priority_queue<Node, vector<Node>, greater<Node> > pq;
    for (int i = 1; i <= n; ++i) dist_arr[i] = INF;
    dist_arr[S] = 0.0;
    pq.push(Node(0.0, S));
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int u = top.second;
        double d = top.first;
        if (u == T) return d;          // 终点出堆时距离已确定
        if (d > dist_arr[u]) continue; // 堆里的过时记录
        for (int i = head[u]; i; i = nxt[i]) {
            double w = a * edge[i].x + (1.0 - a) * edge[i].y;
            double nd = d + w;
            if (nd < dist_arr[edge[i].to]) {
                dist_arr[edge[i].to] = nd;
                pq.push(Node(nd, edge[i].to));
            }
        }
    }
    return dist_arr[T];
}

// 在 [lo,hi] 上积分 d(a)，已知 flo = d(lo)、fhi = d(hi)
double integrate(double lo, double hi, double flo, double fhi, int depth) {
    double mid = (lo + hi) * 0.5;
    double fm = shortest_path(mid);
    double chord = (flo + fhi) * 0.5;   // 两端点连线在中点的高度
    // 容差：绝对项扛小量级噪声，相对项按距离量级放大
    // （Dijkstra 沿不超过 n 条边累加，相对舍入误差不超过 n*2^-52 量级）
    double scale = flo > fhi ? flo : fhi;
    if (scale < 1.0) scale = 1.0;
    double eps = 1e-8 + 1e-11 * scale;
    if (depth >= 50 || fm <= chord + eps) return chord * (hi - lo);
    return integrate(lo, mid, flo, fm, depth + 1) +
           integrate(mid, hi, fm, fhi, depth + 1);
}

int main() {
    if (scanf("%d %d %d %d", &n, &m, &S, &T) != 4) return 0;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        double x, y;
        scanf("%d %d %lf %lf", &u, &v, &x, &y);
        add_edge(u, v, x, y);
        add_edge(v, u, x, y);
    }

    double f0 = shortest_path(0.0);   // a=0 时每条边取空闲耗时 y
    double f1 = shortest_path(1.0);   // a=1 时每条边取最拥堵耗时 x
    double ans = integrate(0.0, 1.0, f0, f1, 0);

    // 输出：题面未规定精度，样例是 "2.5" / "13.0"。按 10 位小数打印后去掉多余
    // 尾零（至少保留一位小数），既与样例逐字符一致，又保留足够有效位。
    char buf[64];
    snprintf(buf, sizeof(buf), "%.10f", ans);
    int dot = -1, last = 0;
    for (int i = 0; buf[i]; ++i) {
        if (buf[i] == '.') dot = i;
        last = i;
    }
    if (dot >= 0) {
        while (last > dot + 1 && buf[last] == '0') {
            buf[last] = '\0';
            last--;
        }
    }
    printf("%s\n", buf);
    return 0;
}
