/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * update_at: 2026-10-17 15:33
 */
// brute.cpp：Bellman-Ford，直接对全部边做 n-1 轮松弛。
// 和 SPFA 的队列优化无关，只用来在小数据上对拍 main.cpp。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100000 + 5;
const long long INF = (1LL << 62);
const long long UNREACH = 2147483647LL;

struct edge {
    int u, v;
    long long w;
};

edge es[MAXM];
long long dis[10000 + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 1; i <= m; ++i) {
        cin >> es[i].u >> es[i].v >> es[i].w;
    }

    fill(dis + 1, dis + n + 1, INF);
    dis[s] = 0;

    for (int round = 1; round <= n - 1; ++round) {
        bool changed = false;
        for (int i = 1; i <= m; ++i) {
            int u = es[i].u, v = es[i].v;
            if (dis[u] == INF) continue;
            long long candidate = dis[u] + es[i].w;
            if (candidate < dis[v]) {
                dis[v] = candidate;
                changed = true;
            }
        }
        if (!changed) break; // 整轮没有更新，之后再扫也不会有
    }

    for (int v = 1; v <= n; ++v) {
        if (v > 1) cout << ' ';
        if (dis[v] == INF) cout << UNREACH;
        else cout << dis[v];
    }
    cout << '\n';

    return 0;
}
