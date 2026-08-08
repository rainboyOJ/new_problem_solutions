// brute.cpp：枚举封锁哪个点，直接数删点后的连通块大小。
// 各块之间的访问全部作废，再加上所有“和被封锁点有关”的访问，就是答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> g[MAXN];
bool vis[MAXN];

void dfs(int u, int ban, int &cnt) {
    vis[u] = true;
    cnt++;

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == ban || vis[v]) {
            continue;
        }
        dfs(v, ban, cnt);
    }
}

long long calc(int ban) {
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
    }

    vector<int> comps;
    for (int i = 1; i <= n; i++) {
        if (i == ban || vis[i]) {
            continue;
        }
        int sz = 0;
        dfs(i, ban, sz);
        comps.push_back(sz);
    }

    long long bad = 2LL * (n - 1);
    for (size_t i = 0; i < comps.size(); i++) {
        for (size_t j = i + 1; j < comps.size(); j++) {
            bad += 2LL * comps[i] * comps[j];
        }
    }
    return bad;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

    for (int i = 1; i <= n; i++) {
        cout << calc(i) << '\n';
    }

    return 0;
}
