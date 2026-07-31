/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:45
 */
// brute.cpp：小数据暴力解，递归枚举从 1 到 n 的所有简单路径。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Edge {
    int to, cost;
};

vector<Edge> graph[MAXN];
int visited[MAXN];
int n;
int answer = INT_MAX;

void dfs(int x, int current_maximum) {
    if (current_maximum >= answer) {
        return;
    }
    if (x == n) {
        answer = current_maximum;
        return;
    }

    for (int i = 0; i < (int)graph[x].size(); i++) {
        int y = graph[x][i].to;
        if (visited[y]) {
            continue;
        }
        visited[y] = 1;
        dfs(y, max(current_maximum, graph[x][i].cost));
        visited[y] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        Edge first = {v, cost};
        Edge second = {u, cost};
        graph[u].push_back(first);
        graph[v].push_back(second);
    }

    visited[1] = 1;
    dfs(1, 0);
    cout << answer << '\n';

    return 0;
}
