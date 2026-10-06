/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:40
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;          // 行数上限
const int MAXM = 1005;          // 列数上限
const int MAXV = MAXN * MAXM;   // 一维总格子数上限

int n, m;                       // 矩阵行列
char g[MAXN][MAXM];             // 输入的 01 矩阵
int dist[MAXV];                 // 一维下标到最近 1 的曼哈顿距离，-1 表示未访问
int q[MAXV];                    // 手写队列

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", g[i]);

    int total = n * m;
    for (int i = 0; i < total; ++i) dist[i] = -1;

    int head = 0, tail = 0;
    // 把所有 1 作为多源 BFS 的源点，距离为 0，一起入队
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '1') {
                int u = i * m + j;
                dist[u] = 0;
                q[tail++] = u;
            }
        }
    }

    // 多源 BFS：每轮扩展一层，第一次到达某格时的层数即最近距离
    while (head < tail) {
        int u = q[head++];
        int r = u / m;          // 行号
        int c = u % m;          // 列号
        int d = dist[u] + 1;    // 邻居距离
        // 上
        if (r > 0) {
            int v = u - m;
            if (dist[v] < 0) {
                dist[v] = d;
                q[tail++] = v;
            }
        }
        // 下
        if (r + 1 < n) {
            int v = u + m;
            if (dist[v] < 0) {
                dist[v] = d;
                q[tail++] = v;
            }
        }
        // 左
        if (c > 0) {
            int v = u - 1;
            if (dist[v] < 0) {
                dist[v] = d;
                q[tail++] = v;
            }
        }
        // 右
        if (c + 1 < m) {
            int v = u + 1;
            if (dist[v] < 0) {
                dist[v] = d;
                q[tail++] = v;
            }
        }
    }

    // 按原矩阵形状输出距离
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) putchar(' ');
            printf("%d", dist[i * m + j]);
        }
        putchar('\n');
    }
    return 0;
}
