/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:29
 */
// brute.cpp：小数据暴力解，显式建立同一基站覆盖节点之间的完全图。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> node_x(n), node_y(n);
    for (int i = 0; i < n; i++) cin >> node_x[i] >> node_y[i];
    vector<vector<pair<int, int> > > graph(n);
    for (int i = 0; i < m; i++) {
        long long x, y, radius, delay;
        cin >> x >> y >> radius >> delay;
        vector<int> covered;
        for (int j = 0; j < n; j++) {
            if (llabs(node_x[j] - x) <= radius && llabs(node_y[j] - y) <= radius) {
                covered.push_back(j);
            }
        }
        for (int a = 0; a < (int)covered.size(); a++) {
            for (int b = 0; b < (int)covered.size(); b++) {
                if (a != b) graph[covered[a]].push_back(make_pair(covered[b], (int)delay));
            }
        }
    }

    const long long INF = (1LL << 62);
    vector<long long> distance(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >,
                   greater<pair<long long, int> > > heap;
    distance[0] = 0;
    heap.push(make_pair(0, 0));
    while (!heap.empty()) {
        pair<long long, int> current = heap.top();
        heap.pop();
        if (current.first != distance[current.second]) continue;
        int node = current.second;
        for (int i = 0; i < (int)graph[node].size(); i++) {
            int next_node = graph[node][i].first;
            long long next_distance = current.first + graph[node][i].second;
            if (next_distance < distance[next_node]) {
                distance[next_node] = next_distance;
                heap.push(make_pair(next_distance, next_node));
            }
        }
    }
    if (distance[n - 1] == INF) cout << "Nan\n";
    else cout << distance[n - 1] << '\n';
    return 0;
}
