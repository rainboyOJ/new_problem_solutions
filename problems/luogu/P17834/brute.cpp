/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 08:26
 * update_at: 2026-11-01 08:26
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举选点集合，用于 n<=16 的小规模验证。
// 先按内部边数统计连通块，再用多源 BFS 计算通勤半径。

const int INF = 1e9;
int n, k;
vector<int> adj[20];
int distance_to_base[20];
int pending[20];

int get_radius(int mask) {
    for (int i = 1; i <= n; i++) distance_to_base[i] = -1;
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
        if ((mask >> (i - 1)) & 1) {
            distance_to_base[i] = 0;
            pending[tail++] = i;
        }
    }
    int max_d = 0;
    while (head < tail) {
        int u = pending[head++];
        max_d = max(max_d, distance_to_base[u]);
        for (int v : adj[u]) {
            if (distance_to_base[v] == -1) {
                distance_to_base[v] = distance_to_base[u] + 1;
                pending[tail++] = v;
            }
        }
    }
    return max_d;
}

int count_components(int mask) {
    int edges = 0;
    for (int u = 1; u <= n; u++) {
        if ((mask >> (u - 1)) & 1) {
            for (int v : adj[u]) {
                if (u < v && ((mask >> (v - 1)) & 1)) {
                    edges++;
                }
            }
        }
    }
    return k - edges;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = INF;
    int total_masks = 1 << n; // 只用于小数据，不按满分规模枚举
    for (int mask = 1; mask < total_masks; mask++) {
        if (__builtin_popcount(mask) == k) {
            if (count_components(mask) <= 2) {
                ans = min(ans, get_radius(mask));
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, t;
    if (!(cin >> c >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
