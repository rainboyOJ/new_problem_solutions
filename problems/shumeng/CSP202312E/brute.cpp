/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
// brute.cpp：小数据暴力解，DFS 枚举所有长度不超过 l 的彩色路径。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, weight;
};

int n, m, limit, color_count;
vector<int> color;
vector<vector<Edge> > graph;
long long answer;

void dfs(int node, int depth, int mask, long long length) {
    if (node == n - 1) answer = max(answer, length);
    if (depth == limit) return;
    for (int i = 0; i < (int)graph[node].size(); i++) {
        Edge edge = graph[node][i];
        int bit = 1 << color[edge.to];
        if (mask & bit) continue;
        dfs(edge.to, depth + 1, mask | bit, length + edge.weight);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> limit >> color_count;
    color.resize(n);
    for (int i = 0; i < n; i++) cin >> color[i];
    graph.resize(n);
    vector<int> from(m), to(m), length(m);
    for (int i = 0; i < m; i++) cin >> from[i];
    for (int i = 0; i < m; i++) cin >> to[i];
    for (int i = 0; i < m; i++) cin >> length[i];
    for (int i = 0; i < m; i++) graph[from[i]].push_back({to[i], length[i]});

    answer = 0;
    dfs(0, 1, 1 << color[0], 0);
    cout << answer << '\n';

    return 0;
}
