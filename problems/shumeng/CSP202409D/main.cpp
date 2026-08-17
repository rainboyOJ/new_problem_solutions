/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MAXM = 5005;
const long long INF = (1LL << 62);

int n, m;
long long node_x[MAXN], node_y[MAXN];   // 节点坐标
long long station_x[MAXM], station_y[MAXM]; // 基站坐标
long long station_radius[MAXM], station_delay[MAXM]; // 基站覆盖半径与延迟
vector<int> covered[MAXM]; // covered[i] 保存基站 i 覆盖的节点编号
long long dist_node[MAXN]; // dist_node[u] 节点 u 的最短延迟
long long dist_station[MAXM]; // 进入基站 i 后的最短延迟
bool discovered[MAXM];     // 基站 i 是否已被某个节点发现

// 判断节点 node 是否在基站 station 的方形覆盖范围内
bool in_range(int node, int station) {
    return llabs(node_x[node] - station_x[station]) <= station_radius[station]
        && llabs(node_y[node] - station_y[station]) <= station_radius[station];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> node_x[i] >> node_y[i];
    for (int i = 0; i < m; i++) {
        cin >> station_x[i] >> station_y[i] >> station_radius[i] >> station_delay[i];
        for (int j = 0; j < n; j++) {
            if (in_range(j, i)) covered[i].push_back(j);
        }
    }

    // 顶点编号：0..n-1 为节点，n..n+m-1 为基站状态
    priority_queue<pair<long long, int>, vector<pair<long long, int> >,
                   greater<pair<long long, int> > > heap;
    for (int i = 0; i < n; i++) dist_node[i] = INF;
    for (int i = 0; i < m; i++) dist_station[i] = INF;
    dist_node[0] = 0;
    heap.push(make_pair(0, 0));

    while (!heap.empty()) {
        long long current_distance = heap.top().first;
        int vertex = heap.top().second;
        heap.pop();

        if (vertex < n) {
            // 弹出的是节点状态
            int node = vertex;
            if (current_distance != dist_node[node]) continue;
            // 扫描尚未发现的基站：若当前节点在基站范围内，则进入该基站
            for (int i = 0; i < m; i++) {
                if (discovered[i]) continue;
                if (!in_range(node, i)) continue;
                discovered[i] = true;
                dist_station[i] = current_distance + station_delay[i];
                heap.push(make_pair(dist_station[i], n + i));
            }
        } else {
            // 弹出的是基站状态：离开基站不增加延迟，零代价松弛其覆盖的所有节点
            int station_id = vertex - n;
            if (current_distance != dist_station[station_id]) continue;
            for (int i = 0; i < (int)covered[station_id].size(); i++) {
                int next_node = covered[station_id][i];
                if (current_distance < dist_node[next_node]) {
                    dist_node[next_node] = current_distance;
                    heap.push(make_pair(current_distance, next_node));
                }
            }
        }
    }

    if (dist_node[n - 1] == INF) cout << "Nan\n";
    else cout << dist_node[n - 1] << '\n';
    return 0;
}