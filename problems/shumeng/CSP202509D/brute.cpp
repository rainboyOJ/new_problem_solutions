/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> value(n + 1);
    for (int i = 1; i <= n; i++) cin >> value[i];
    vector<vector<int> > graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    while (m--) {
        int x, y;
        cin >> x >> y;
        vector<int> parent(n + 1, 0);
        vector<int> stack;
        stack.push_back(x);
        parent[x] = -1;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            if (u == y) break;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i];
                if (parent[v] != 0) continue;
                parent[v] = u;
                stack.push_back(v);
            }
        }
        vector<int> present(n, 0);
        int current = y;
        while (current != -1) {
            present[value[current]] = 1;
            current = parent[current];
        }
        int answer = 0;
        while (answer < n && present[answer]) answer++;
        cout << answer << '\n';
    }
    return 0;
}
