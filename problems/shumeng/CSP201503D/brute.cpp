/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:55
 */
// brute.cpp：小数据基准，从每个节点做一次 BFS 求最远距离。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int total_nodes = n + m;
    vector<vector<int> > graph(total_nodes + 1);
    for (int child = 2; child <= n; child++) {
        int parent;
        cin >> parent;
        graph[parent].push_back(child);
        graph[child].push_back(parent);
    }
    for (int computer = 1; computer <= m; computer++) {
        int parent;
        cin >> parent;
        int node = n + computer;
        graph[parent].push_back(node);
        graph[node].push_back(parent);
    }

    int answer = 0;
    for (int start = 1; start <= total_nodes; start++) {
        vector<int> distance(total_nodes + 1, -1);
        queue<int> q;
        q.push(start);
        distance[start] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            answer = max(answer, distance[u]);
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i];
                if (distance[v] != -1) continue;
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }
    cout << answer << '\n';

    return 0;
}
