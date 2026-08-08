// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> g[MAXN];
int indeg[MAXN], outdeg[MAXN];

int dfs(int u) {
    if (outdeg[u] == 0) {
        return 1;
    }

    int ret = 0;
    for (int i = 0; i < (int) g[u].size(); i++) {
        int v = g[u][i];
        ret += dfs(v);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0 && outdeg[i] > 0) {
            ans += dfs(i);
        }
    }

    cout << ans << '\n';
    return 0;
}
