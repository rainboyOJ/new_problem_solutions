/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:58
 * update_at: 2026-10-06 18:58
 */

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2005;   // 课程数
const int MAXV = 305;    // 教室数
const double INF = 1e18; // DP 不可达哨兵
const int INF_DIST = 1000000000; // 最短路里“没有路”的哨兵

int n, m, v, e;
int c[MAXN], d[MAXN];    // 每门课的两个候选教室
double k[MAXN];          // 每门课申请通过的概率
int dist[MAXV][MAXV];    // 任意两教室间的最少体力

double dp0[MAXN], dp1[MAXN]; // dp0[j] / dp1[j]：到当前课、用 j 次申请、当前课不申请/申请时的最小期望

double tmp0[MAXN], tmp1[MAXN];

int main() {
    scanf("%d %d %d %d", &n, &m, &v, &e);
    if (m > n) m = n; // 申请次数不会超过课程数

    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= n; i++) scanf("%lf", &k[i]);

    // 初始化最短路
    for (int i = 1; i <= v; i++) {
        for (int j = 1; j <= v; j++) {
            dist[i][j] = (i == j) ? 0 : INF_DIST;
        }
    }

    for (int i = 1; i <= e; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        if (w < dist[a][b]) {
            dist[a][b] = dist[b][a] = w;
        }
    }

    // Floyd–Warshall 求全源最短路
    for (int kk = 1; kk <= v; kk++) {
        for (int i = 1; i <= v; i++) {
            if (dist[i][kk] >= INF_DIST) continue;
            for (int j = 1; j <= v; j++) {
                int alt = dist[i][kk] + dist[kk][j];
                if (alt < dist[i][j]) dist[i][j] = alt;
            }
        }
    }

    // 初始化第 1 门课的状态
    for (int j = 0; j <= m; j++) {
        dp0[j] = INF;
        dp1[j] = INF;
    }
    dp0[0] = 0.0; // 第 1 门不申请，用 0 次
    if (m >= 1) dp1[1] = 0.0; // 第 1 门申请，用 1 次

    // 从第 2 门课开始，逐段合并 n-1 段
    for (int i = 2; i <= n; i++) {
        int cc = dist[c[i - 1]][c[i]]; // 上、下都不申请
        int cd = dist[c[i - 1]][d[i]]; // 下申请通过
        int dc = dist[d[i - 1]][c[i]]; // 上申请通过
        int dd = dist[d[i - 1]][d[i]]; // 两门都申请通过

        double win = k[i];       // 第 i 门申请通过的概率
        double lose = 1 - k[i - 1]; // 第 i-1 门申请被拒的概率

        double cost01 = (1 - win) * cc + win * cd; // 第 i-1 门不申请，第 i 门申请
        double cost10 = lose * cc + (1 - lose) * dc; // 第 i-1 门申请，第 i 门不申请
        double cost11 = lose * cost01 + (1 - lose) * ((1 - win) * dc + win * dd); // 都申请

        // 当前课 i 不申请：从 dp0[j] / dp1[j] 同位转移
        for (int j = 0; j <= m; j++) {
            tmp0[j] = min(dp0[j] + cc, dp1[j] + cost10);
        }

        // 当前课 i 申请：申请数 +1，从 dp0[j-1] / dp1[j-1] 转移
        tmp1[0] = INF;
        for (int j = 1; j <= m; j++) {
            tmp1[j] = min(dp0[j - 1] + cost01, dp1[j - 1] + cost11);
        }

        for (int j = 0; j <= m; j++) {
            dp0[j] = tmp0[j];
            dp1[j] = tmp1[j];
        }
    }

    double ans = INF;
    for (int j = 0; j <= m; j++) {
        ans = min(ans, dp0[j]);
        ans = min(ans, dp1[j]);
    }

    // 四舍五入到两位小数，先转整数分避免银行家舍入与浮点噪声
    int cents = (int)(ans * 100.0 + 0.5 + 1e-9);
    printf("%.2f\n", cents / 100.0);

    return 0;
}
