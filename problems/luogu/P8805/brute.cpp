// brute.cpp：每次查询直接在树上找唯一路径，把路径上的点度数加起来。
// 这个做法复杂度较高，只适合小数据理解题意和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> g[MAXN];
int deg[MAXN];
int parent_arr[MAXN];
bool vis[MAXN];

bool dfs_find(int u, int target, int fa) {
    if (u == target) {
        return true;
    }

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        parent_arr[v] = u;
        if (dfs_find(v, target, u)) {
            return true;
        }
    }
    return false;
}

long long query_path_sum(int u, int v) {
    for (int i = 1; i <= n; i++) {
        parent_arr[i] = 0;
    }

    dfs_find(u, v, 0);

    long long ans = 0;
    int x = v;
    while (x != u) {
        ans += deg[x];
        x = parent_arr[x];
    }
    ans += deg[u];

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        deg[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << query_path_sum(u, v) << '\n';
    }

    return 0;
}
