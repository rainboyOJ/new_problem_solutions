/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:47
 * update_at: 2026-10-05 10:47
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;           // n <= 100
const double INF = 1e100;       // 不可达哨兵

int n, m, s, t;
double x[MAXN], y[MAXN];        // 点坐标
double d[MAXN][MAXN];           // 邻接矩阵，d[i][j] 表示 i 到 j 的最短距离

// 计算两点间欧氏距离，即连线的边权
double dist(int u, int v) {
    double dx = x[u] - x[v];
    double dy = y[u] - y[v];
    return sqrt(dx * dx + dy * dy);
}

// Floyd：原地松弛邻接矩阵，使 d[i][j] 成为任意两点最短路长度
void floyd() {
    for (int k = 1; k <= n; k++)          // 中转点放在最外层
        for (int i = 1; i <= n; i++)      // 起点
            for (int j = 1; j <= n; j++)  // 终点
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf %lf", &x[i], &y[i]);

    // 初始化邻接矩阵：自己到自己是 0，其余先记为不可达
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = (i == j) ? 0.0 : INF;

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        double w = dist(u, v);
        d[u][v] = d[v][u] = w;  // 无向边，登记两个方向
    }

    scanf("%d %d", &s, &t);
    floyd();
    printf("%.2f\n", d[s][t]);
    return 0;
}
