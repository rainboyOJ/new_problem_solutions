/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:27
 * update_at: 2026-08-12 22:27
 */
// brute.cpp：小数据暴力解，让每只企鹅从自己出发 DFS 找 1 号点，数走过的边数。
// 树中两个点之间的路径唯一，所以一次 DFS 找到 1 号点的步数就是真实距离。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, d;
vector<int> g[MAXN]; // g[u] 保存与 u 相邻的所有点（邻接表）
int vis[MAXN];       // vis[u] 表示当前这次 DFS 是否已经访问过 u，防止往回走

// 从 u 出发找 1 号点，返回找到 1 号点经过的最少边数。
int dist_to_root(int u) {
    vis[u] = 1;
    if (u == 1) return 0;

    int best = MAXN; // 很大的数，表示这个方向没找到 1 号点
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (vis[v]) continue;
        int t = dist_to_root(v);
        if (t + 1 < best) best = t + 1;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 0;
    // 每只企鹅分别从自己出发找一次 1 号点，O(n) 次 DFS 只适合小数据。
    for (int i = 2; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dist_to_root(i) <= d) ans++;
    }
    cout << ans << endl;

    return 0;
}
