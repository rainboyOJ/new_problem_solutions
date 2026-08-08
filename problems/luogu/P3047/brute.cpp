#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n, k_limit;
vector<int> g[MAXN];
int cows[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 对每个点都做一次 BFS，统计距离不超过 K 的所有牛数。
    cin >> n >> k_limit;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        cin >> cows[i];
    }

    for (int start = 1; start <= n; start++) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (size_t i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (dist[v] != -1) {
                    continue;
                }
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] != -1 && dist[i] <= k_limit) {
                sum += cows[i];
            }
        }
        cout << sum << '\n';
    }

    return 0;
}
