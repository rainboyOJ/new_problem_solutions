/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，把同一基站覆盖的节点两两连边后跑普通 Dijkstra。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const long long INF = (1LL << 62);

int n, m;
long long node_x[MAXN], node_y[MAXN];
vector<pair<int, int> > graph[MAXN]; // 显式的节点完全图

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> node_x[i] >> node_y[i];

    // 每个基站：正方形内的任意两个节点连一条延迟边（双向）
    for (int i = 0; i < m; i++) {
        long long x, y, radius, delay;
        cin >> x >> y >> radius >> delay;
        vector<int> covered;
        for (int j = 0; j < n; j++) {
            if (llabs(node_x[j] - x) <= radius && llabs(node_y[j] - y) <= radius) {
                covered.push_back(j);
            }
        }
        // 集合内两两连边，q 个节点会建出 O(q^2) 条边
        for (int a = 0; a < (int)covered.size(); a++) {
            for (int b = 0; b < (int)covered.size(); b++) {
                if (a != b) graph[covered[a]].push_back(make_pair(covered[b], (int)delay));
            }
        }
    }

    // 标准 Dijkstra
    vector<long long> distance(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >,
                   greater<pair<long long, int> > > heap;
    distance[0] = 0;
    heap.push(make_pair(0, 0));
    while (!heap.empty()) {
        long long current_distance = heap.top().first;
        int node = heap.top().second;
        heap.pop();
        if (current_distance != distance[node]) continue;
        for (int i = 0; i < (int)graph[node].size(); i++) {
            int next_node = graph[node][i].first;
            long long next_distance = current_distance + graph[node][i].second;
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