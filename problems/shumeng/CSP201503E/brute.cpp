/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:54
 */
// brute.cpp：小数据基准，BFS 找出每条旅行的唯一树路径后逐边模拟购买。
#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, length; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; i++) cin >> price[i];
    vector<vector<Edge> > graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, length;
        cin >> u >> v >> length;
        graph[u].push_back({v, length});
        graph[v].push_back({u, length});
    }
    while (m--) {
        int start, target;
        cin >> start >> target;
        vector<int> parent(n + 1, -1), parent_edge(n + 1);
        queue<int> q;
        q.push(start);
        parent[start] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i].to;
                if (parent[v] != -1) continue;
                parent[v] = u;
                parent_edge[v] = graph[u][i].length;
                q.push(v);
            }
        }
        vector<int> path;
        for (int u = target; u != 0; u = parent[u]) path.push_back(u);
        reverse(path.begin(), path.end());
        long long answer = 0;
        // 沿路径逐边模拟：每走一条边都用当前已知的最低价格买粮。
        int lowest_price = price[start];
        for (int i = 1; i < (int)path.size(); i++) {
            answer += 1LL * lowest_price * parent_edge[path[i]];
            lowest_price = min(lowest_price, price[path[i]]);
        }
        cout << answer << '\n';
    }
    return 0;
}
