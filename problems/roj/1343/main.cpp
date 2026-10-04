/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:58
 * update_at: 2026-10-05 00:00
 */
// main.cpp：Floyd 全源最短路 + 枚举连接两个牧场的新边。
// 答案 = max(原最大直径 D, min_{a,b 跨牧场} R(a)+|p_a p_b|+R(b))，
// 其中 R(i) 是 i 到本牧场内最远点的最短距离。

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 155;        // 牧区数上限
const double INF = 1e18;     // 表示两点不在同一个牧场

int n;                       // 牧区数
double x[MAXN], y[MAXN];     // 每个牧区的坐标
double d[MAXN][MAXN];        // d[i][j]：i 到 j 的最短距离，INF 表示不在同一牧场
double far[MAXN];            // far[i] = R(i)：i 到本牧场内最远点的距离

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &x[i], &y[i]);

    // 邻接矩阵必须逐个字符读：'1' 表示有边，边权就是两点间的欧氏距离。
    // 注意对角线 d[i][i] 必须置 0，否则 Floyd 后它会被自己绕一圈的路径填上。
    for (int i = 0; i < n; i++) {
        char row[MAXN + 5];
        scanf("%s", row);
        for (int j = 0; j < n; j++) {
            d[i][j] = INF;
            if (row[j] == '1')
                d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
        d[i][i] = 0;
    }

    // Floyd 求全源最短路。
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < INF && d[k][j] < INF && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    // R(i)：i 到本牧场内最远点的距离（对角线为 0，一定可达）。
    double diameter = 0;     // D：所有牧场直径的最大值，是答案的下界，不能丢
    for (int i = 0; i < n; i++) {
        far[i] = 0;
        for (int j = 0; j < n; j++)
            if (d[i][j] < INF && d[i][j] > far[i])
                far[i] = d[i][j];
        if (far[i] > diameter)
            diameter = far[i];
    }

    // 枚举新边 (a, b)：a、b 必须分属两个牧场（d[a][b] == INF）。
    // 跨牧场点对的路径必经新边，新牧场直径 = max(D, R(a)+|p_a p_b|+R(b))。
    double bridge = INF;     // 所有候选新边中最小的 R(a)+|p_a p_b|+R(b)
    for (int a = 0; a < n; a++)
        for (int b = 0; b < n; b++)
            if (d[a][b] >= INF) {
                double len = sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
                bridge = min(bridge, far[a] + len + far[b]);
            }

    printf("%.6f\n", max(diameter, bridge));
    return 0;
}
