/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:41
 * update_at: 2026-10-03 10:45
 */
// brute.cpp：洛谷 P2169 的最朴素暴力解，用于理解题意并和 main.cpp 对拍。
//
// 暴力思路完全不碰“强连通分量”这个概念，只做最直白的翻译：
//   1. 用 Floyd 求传递闭包 reach[i][j]，即“i 能不能走到 j”；
//   2. 若 reach[i][j] 和 reach[j][i] 同时成立，说明 i、j 处于同一局域网，
//      它们之间的传输时间为 0，于是把 dist[i][j] 置 0；
//   3. 再用 Floyd 在带 0 权的图上求 1 到 n 的最短路。
//
// 复杂度 O(n^3)，只能用于小数据，但每一步都是对题意的直接翻译，
// 所以它是对的：它就是“局域网内部耗时 0”这句话本身。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 305;          // 暴力只用在小数据上
const ll INF = 1e18;

int n, m;
ll dist[maxn][maxn];           // dist[i][j]：i 到 j 的当前最短距离
bool reach[maxn][maxn];        // reach[i][j]：i 能否到达 j

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
            reach[i][j] = false;
        }
        dist[i][i] = 0;
        reach[i][i] = true;     // 自己一定能到自己
    }

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        if (c < dist[u][v]) dist[u][v] = c;   // 重边保留最小的一条
        reach[u][v] = true;
    }

    // 第一步：Floyd 求传递闭包
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (!reach[i][k]) continue;
            for (int j = 1; j <= n; j++) {
                if (reach[k][j]) reach[i][j] = true;
            }
        }
    }

    // 第二步：互相可达 => 同一局域网 => 传输时间 0
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (reach[i][j] && reach[j][i]) dist[i][j] = 0;
        }
    }

    // 第三步：Floyd 求最短路
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] >= INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist[k][j] >= INF) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("%lld\n", dist[1][n]);
    return 0;
}
