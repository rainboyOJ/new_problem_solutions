/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:23
 * update_at: 2026-10-06 00:23
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 305;
const ll INF = 1e18;

int n;
ll v[MAXN];           // 各矿井建发电站的费用
ll p[MAXN][MAXN];     // 电网费用矩阵
ll edge[MAXN][MAXN];  // 拼成 (n+1) 个点的邻接矩阵，下标 0~n，点 n 为超级源点
bool used[MAXN];      // 是否已加入生成树
ll best[MAXN];        // 未选点连到已选点集的最便宜边权

// 稠密图最小生成树：朴素 Prim，返回总边权
ll prim(int tot) {
    for (int i = 0; i < tot; ++i) {
        used[i] = false;
        best[i] = INF;
    }
    best[n] = 0; // 从超级源点（编号 n）出发
    ll total = 0;
    for (int _ = 0; _ < tot; ++_) {
        int u = -1;
        for (int i = 0; i < tot; ++i)
            if (!used[i] && (u == -1 || best[i] < best[u]))
                u = i;
        used[u] = true;
        total += best[u];
        for (int i = 0; i < tot; ++i)
            if (!used[i] && edge[u][i] < best[i])
                best[i] = edge[u][i];
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> p[i][j];

    // 把超级源点放在下标 n，对应 edge 的第 n 行/列
    // edge[i][j] = p[i][j]（0<=i,j<n），edge[i][n] = edge[n][i] = v[i]
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            edge[i][j] = p[i][j];
    for (int i = 0; i < n; ++i) {
        edge[i][n] = v[i];
        edge[n][i] = v[i];
    }
    edge[n][n] = 0;

    cout << prim(n + 1) << "\n";
    return 0;
}
