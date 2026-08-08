#include <bits/stdc++.h>
using namespace std;

// brute.cpp：每个点都 BFS 计算距离和，只适合小数据。

const int MAXN = 505;

int n;
vector<int> graph_edges[MAXN];

long long distance_sum_from(int start) {
    int dist[MAXN];
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    queue<int> que;
    que.push(start);
    dist[start] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < (int)graph_edges[u].size(); i++) {
            int v = graph_edges[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += dist[i];
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }

    int best_node = 1;
    long long best_value = distance_sum_from(1);
    for (int i = 2; i <= n; i++) {
        long long value = distance_sum_from(i);
        if (value > best_value) {
            best_value = value;
            best_node = i;
        }
    }

    cout << best_node << '\n';

    return 0;
}
