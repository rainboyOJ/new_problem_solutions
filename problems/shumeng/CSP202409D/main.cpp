/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:29
 */
#include <bits/stdc++.h>
using namespace std;

struct Station {
    long long x, y, radius, delay;
    vector<int> covered;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> node_x(n), node_y(n);
    for (int i = 0; i < n; i++) cin >> node_x[i] >> node_y[i];

    vector<Station> stations(m);
    for (int i = 0; i < m; i++) {
        cin >> stations[i].x >> stations[i].y >> stations[i].radius >> stations[i].delay;
        for (int j = 0; j < n; j++) {
            if (llabs(node_x[j] - stations[i].x) <= stations[i].radius &&
                llabs(node_y[j] - stations[i].y) <= stations[i].radius) {
                stations[i].covered.push_back(j);
            }
        }
    }

    const long long INF = (1LL << 62);
    vector<long long> distance(n, INF);
    vector<char> discovered(m, 0);
    vector<long long> distance_with_station(m, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >,
                   greater<pair<long long, int> > > heap;
    distance[0] = 0;
    heap.push(make_pair(0, 0));

    while (!heap.empty()) {
        pair<long long, int> current = heap.top();
        heap.pop();
        long long current_distance = current.first;
        int vertex = current.second;
        if (vertex < n) {
            int node = vertex;
            if (current_distance != distance[node]) continue;
            // 通过节点进入基站需要付出延迟，基站状态本身只加入一次。
            for (int i = 0; i < m; i++) {
                if (discovered[i]) continue;
                if (llabs(node_x[node] - stations[i].x) > stations[i].radius ||
                    llabs(node_y[node] - stations[i].y) > stations[i].radius) {
                    continue;
                }
                discovered[i] = 1;
                distance_with_station[i] = current_distance + stations[i].delay;
                heap.push(make_pair(distance_with_station[i], n + i));
            }
        } else {
            int station_id = vertex - n;
            if (current_distance != distance_with_station[station_id]) continue;
            // 离开基站不再增加延迟，因此从基站状态向所有覆盖节点连零边。
            for (int i = 0; i < (int)stations[station_id].covered.size(); i++) {
                int next_node = stations[station_id].covered[i];
                if (current_distance < distance[next_node]) {
                    distance[next_node] = current_distance;
                    heap.push(make_pair(current_distance, next_node));
                }
            }
        }
    }

    if (distance[n - 1] == INF) cout << "Nan\n";
    else cout << distance[n - 1] << '\n';
    return 0;
}
