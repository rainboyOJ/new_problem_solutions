#include <bits/stdc++.h>
using namespace std;

// brute.cpp：逐条路径 BFS 找出路径点并加一，只适合小数据。

const int MAXN = 505;

int n, k;
vector<int> graph_edges[MAXN];
int parent_node[MAXN];
long long count_node[MAXN];

void mark_path(int start, int target) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = -1;
    }
    queue<int> que;
    que.push(start);
    parent_node[start] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == target) {
            break;
        }
        for (int i = 0; i < (int)graph_edges[u].size(); i++) {
            int v = graph_edges[u][i];
            if (parent_node[v] == -1) {
                parent_node[v] = u;
                que.push(v);
            }
        }
    }

    int x = target;
    while (x != 0) {
        count_node[x]++;
        if (x == start) {
            break;
        }
        x = parent_node[x];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }
    for (int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        mark_path(u, v);
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, count_node[i]);
    }
    cout << answer << '\n';

    return 0;
}
