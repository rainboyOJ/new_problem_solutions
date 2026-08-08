#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> g[MAXN];
int parent_arr[MAXN];
int vis[MAXN];
int ans;

bool dfs_path(int u, int fa, int target, vector<int> &path) {
    path.push_back(u);
    if (u == target) {
        return true;
    }
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        if (dfs_path(v, u, target, path)) {
            return true;
        }
    }
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举所有路径，直接统计这条路径及其相邻边带来的点数。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ans = 1;
    for (int s = 1; s <= n; s++) {
        for (int t = s; t <= n; t++) {
            vector<int> path;
            dfs_path(s, 0, t, path);

            memset(vis, 0, sizeof(vis));
            for (size_t i = 0; i < path.size(); i++) {
                int u = path[i];
                vis[u] = 1;
                for (size_t j = 0; j < g[u].size(); j++) {
                    vis[g[u][j]] = 1;
                }
            }

            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                cnt += vis[i];
            }
            ans = max(ans, cnt);
        }
    }

    cout << ans << '\n';
    return 0;
}
