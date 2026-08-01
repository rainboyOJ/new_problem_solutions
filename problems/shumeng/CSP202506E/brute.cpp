/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:45
 */
// brute.cpp：枚举施工点并 BFS 每个连通块，适合小图验证。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int> > graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    while (q--) {
        int c;
        cin >> c;
        vector<int> weight(n + 1, 0);
        for (int i = 0; i < c; i++) {
            int x;
            cin >> x;
            weight[x] = 1;
        }
        long long answer = 0;
        for (int removed = 1; removed <= n; removed++) {
            vector<int> visited(n + 1, 0);
            int best = 0;
            for (int start = 1; start <= n; start++) {
                if (start == removed || visited[start]) {
                    continue;
                }
                int current = 0;
                queue<int> que;
                que.push(start);
                visited[start] = 1;
                while (!que.empty()) {
                    int u = que.front();
                    que.pop();
                    current += weight[u];
                    for (int i = 0; i < (int)graph[u].size(); i++) {
                        int v = graph[u][i];
                        if (v != removed && !visited[v]) {
                            visited[v] = 1;
                            que.push(v);
                        }
                    }
                }
                best = max(best, current);
            }
            answer += best;
        }
        cout << answer << '\n';
    }
    return 0;
}
