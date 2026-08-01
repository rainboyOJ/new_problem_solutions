/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 11:05
 */
// brute.cpp：每次重建根树并做树形 DP，适合小数据验证。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int> > graph;
vector<long long> weight_value;
vector<long long> down_value;
vector<long long> best_value;

void dfs(int u, int parent) {
    down_value[u] = weight_value[u];
    best_value[u] = LLONG_MIN / 4;
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (v == parent) {
            continue;
        }
        dfs(v, u);
        down_value[u] += max(0LL, down_value[v]);
        best_value[u] = max(best_value[u], best_value[v]);
    }
    best_value[u] = max(best_value[u], down_value[u]);
}

long long root_answer(int root) {
    dfs(root, 0);
    return down_value[root];
}

long long subtree_answer(int root, int target) {
    dfs(root, 0);
    return best_value[target];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    graph.assign(n + 1, vector<int>());
    weight_value.assign(n + 1, 0);
    down_value.assign(n + 1, 0);
    best_value.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> weight_value[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int current_root = 1;
    cout << root_answer(current_root) << '\n';
    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u;
            cin >> u;
            cout << subtree_answer(current_root, u) << '\n';
        } else if (type == 2) {
            int u;
            long long x;
            cin >> u >> x;
            weight_value[u] = x;
            cout << root_answer(current_root) << '\n';
        } else if (type == 3) {
            cin >> current_root;
            cout << root_answer(current_root) << '\n';
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            for (int i = 0; i < (int)graph[a].size(); i++) {
                if (graph[a][i] == b) {
                    graph[a].erase(graph[a].begin() + i);
                    break;
                }
            }
            for (int i = 0; i < (int)graph[b].size(); i++) {
                if (graph[b][i] == a) {
                    graph[b].erase(graph[b].begin() + i);
                    break;
                }
            }
            graph[c].push_back(d);
            graph[d].push_back(c);
            cout << root_answer(current_root) << '\n';
        }
    }
    return 0;
}
