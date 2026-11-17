/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-07-17 01:40
 */
#include <bits/stdc++.h>
using namespace std;

// P2910 Clear And Present Danger S
// 无向图 + Floyd 全源最短路竞赛精简版，要求无负环。
// 输入 n m，接着 m 个必须按序访问的岛屿 A_1..A_m，
// 再输入 n 行 n 列的邻接矩阵（第 i 行第 i 列为 0）。
// 先 Floyd 求出任意两岛间的最小危险值，再把访问序列的相邻两项相加。
// 点编号 1..n，要求 n < N；有限距离的绝对值小于 INF，距离相加不溢出。
// 口诀：中转点 k 最外层，两段都可达才相加。
const int N = 410;
const long long INF = 1e18;
// const long long INF = LLONG_MAX;
long long d[N][N];
int n, m;
int a[10010]; // 必须按序访问的岛屿序列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = (i == j ? 0 : INF);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            long long w;
            cin >> w;
            d[i][j] = min(d[i][j], w); // 输入矩阵本身对称（无向图），读入即完成建图
        }

    for (int k = 1; k <= n; k++) // 中转点必须在最外层，内层 i、j 可以交换
        for (int i = 1; i <= n; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }

    long long ans = 0;
    for (int i = 1; i < m; i++)
        ans += d[a[i]][a[i + 1]]; // 相邻两段彼此独立，直接累加最短路

    cout << ans << '\n';
    return 0;
}
