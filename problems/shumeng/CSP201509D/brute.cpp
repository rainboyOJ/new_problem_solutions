/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:36
 */
// brute.cpp：对每个城市做 BFS，直接检查互相可达的城市对。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    vector<vector<int> > reach(n + 1, vector<int>(n + 1));
    for (int start = 1; start <= n; start++) {
        queue<int> q;
        q.push(start);
        reach[start][start] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i];
                if (!reach[start][v]) {
                    reach[start][v] = 1;
                    q.push(v);
                }
            }
        }
    }
    long long answer = 0;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) answer += reach[i][j] && reach[j][i];
    cout << answer << '\n';
    return 0;
}
