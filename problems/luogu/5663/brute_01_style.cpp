// brute_01_style.cpp：另一种小数据暴力写法，用递归枚举每一步走向哪个相邻点。
#include <bits/stdc++.h>
using namespace std;

int n, m, q;
int max_l;
vector<vector<int> > g;
vector<pair<int, int> > query_list;
vector<vector<unsigned char> > can_reach; // can_reach[step][u] 表示恰好 step 步能到 u
vector<vector<unsigned char> > expanded;  // expanded[step][u] 表示这个状态已经向后扩展过

void dfs_walk(int step, int u) {
    can_reach[step][u] = 1;
    if (step == max_l) {
        return;
    }
    if (expanded[step][u]) {
        return;
    }
    expanded[step][u] = 1;

    // 下一步可以选择走向任意一个相邻工人。
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        dfs_walk(step + 1, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    g.assign(n + 1, vector<int>());

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    query_list.resize(q);
    max_l = 0;
    for (int i = 0; i < q; i++) {
        int a, l;
        cin >> a >> l;
        query_list[i] = make_pair(a, l);
        max_l = max(max_l, l);
    }

    can_reach.assign(max_l + 1, vector<unsigned char>(n + 1, 0));
    expanded.assign(max_l + 1, vector<unsigned char>(n + 1, 0));
    dfs_walk(0, 1);

    for (int i = 0; i < q; i++) {
        int a = query_list[i].first;
        int l = query_list[i].second;
        if (can_reach[l][a]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
