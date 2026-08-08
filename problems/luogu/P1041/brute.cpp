#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
vector<int> g[MAXN];
int depth_arr[MAXN];
vector<int> by_depth[MAXN];
int max_depth;
int tin[MAXN], tout[MAXN], timer_cnt;
int sub_size[MAXN];
int cut_root[MAXN];
int cut_cnt;
int best_saved;

void dfs_build(int u, int fa) {
    tin[u] = ++timer_cnt;
    sub_size[u] = 1;
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        depth_arr[v] = depth_arr[u] + 1;
        max_depth = max(max_depth, depth_arr[v]);
        by_depth[depth_arr[v]].push_back(v);
        dfs_build(v, u);
        sub_size[u] += sub_size[v];
    }
    tout[u] = timer_cnt;
}

bool in_subtree(int x, int u) {
    return tin[u] <= tin[x] && tin[x] <= tout[u];
}

bool is_alive(int u) {
    for (int i = 1; i <= cut_cnt; i++) {
        if (in_subtree(u, cut_root[i])) {
            return false;
        }
    }
    return true;
}

void dfs_search(int dep, int saved) {
    if (dep > max_depth) {
        best_saved = max(best_saved, saved);
        return;
    }

    vector<int> cand;
    for (int u : by_depth[dep]) {
        if (is_alive(u)) {
            cand.push_back(u);
        }
    }

    if (cand.empty()) {
        best_saved = max(best_saved, saved);
        return;
    }

    for (int u : cand) {
        cut_root[++cut_cnt] = u;
        dfs_search(dep + 1, saved + sub_size[u]);
        cut_cnt--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    depth_arr[1] = 0;
    max_depth = 0;
    timer_cnt = 0;
    dfs_build(1, 0);

    best_saved = 0;
    cut_cnt = 0;
    dfs_search(1, 0);

    cout << n - best_saved << '\n';
    return 0;
}
