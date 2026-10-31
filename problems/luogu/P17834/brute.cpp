#include <bits/stdc++.h>
using namespace std;

// brute.cpp: 暴力基线与小规模验证 (n <= 10)
// 枚举所有大小为 k 的子集 S，验证连通块数 <= 2，并多源 BFS 算通勤半径

const int INF = 1e9;
int n, k;
vector<int> adj[20];
int dist_u[20];
int q_arr[20];

int get_radius(int mask) {
    for (int i = 1; i <= n; i++) dist_u[i] = -1;
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
        if ((mask >> (i - 1)) & 1) {
            dist_u[i] = 0;
            q_arr[tail++] = i;
        }
    }
    int max_d = 0;
    while (head < tail) {
        int u = q_arr[head++];
        max_d = max(max_d, dist_u[u]);
        for (int v : adj[u]) {
            if (dist_u[v] == -1) {
                dist_u[v] = dist_u[u] + 1;
                q_arr[tail++] = v;
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
    int total_masks = 1 << n;
    for (int mask = 0; mask < total_masks; mask++) {
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
