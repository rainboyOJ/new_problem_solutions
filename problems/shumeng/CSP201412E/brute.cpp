/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:43
 */
// brute.cpp：小数据基准，逐吨使用 SPFA 求最短增广路。
// 与 main.cpp 的最小费用最大流算法结论一致，只适合小数据验证。
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
const int INF_CAP = 1000000000;

// 一条网络流边：to 为终点，rev 为反向边在终点邻接表中的下标，cap 为剩余容量
struct Edge {
    int to;
    int rev;
    int cap;
    int cost;
};

vector<vector<Edge> > graph;

// 加一条容量 cap、单位费用 cost 的边，并同时加入反向边。
void add_edge(int u, int v, int cap, int cost) {
    Edge forward = {v, (int)graph[v].size(), cap, cost};
    Edge backward = {u, (int)graph[u].size(), 0, -cost};
    graph[u].push_back(forward);
    graph[v].push_back(backward);
}

// 节点编号：城市 city 在第 day 天对应的节点下标。
int node_id(int day, int city, int n) {
    return day * n + city;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int production[10][7] = {};
    int demand[10][7] = {};
    int capacity[10], hold_cost[10];
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) {
            cin >> production[city][day];
        }
        for (int day = 0; day < 7; day++) {
            cin >> demand[city][day];
        }
        cin >> capacity[city] >> hold_cost[city];
    }

    struct Road {
        int u;
        int v;
        int cost;
    };
    vector<Road> roads(m);
    for (int i = 0; i < m; i++) {
        cin >> roads[i].u >> roads[i].v >> roads[i].cost;
        roads[i].u--;
        roads[i].v--;
    }

    // 建时间扩展网络：源点 S 提供产量，汇点 T 消耗需求，
    // 仓库边负责从当天流入下一天，道路边在同一天内双向运输。
    int source = 7 * n;
    int sink = source + 1;
    graph.assign(sink + 1, vector<Edge>());
    int total = 0;
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) {
            int current = node_id(day, city, n);
            add_edge(source, current, production[city][day], 0);
            add_edge(current, sink, demand[city][day], 0);
            add_edge(current, node_id((day + 1) % 7, city, n), capacity[city], hold_cost[city]);
            total += demand[city][day];
        }
    }
    for (int day = 0; day < 7; day++) {
        for (int i = 0; i < m; i++) {
            add_edge(node_id(day, roads[i].u, n), node_id(day, roads[i].v, n), INF_CAP, roads[i].cost);
            add_edge(node_id(day, roads[i].v, n), node_id(day, roads[i].u, n), INF_CAP, roads[i].cost);
        }
    }

    // 每轮用 SPFA 在残量网络中找最短增广路，只增广 1 吨货物。
    long long answer = 0;
    int sent = 0;
    int nodes = sink + 1;
    while (sent < total) {
        vector<int> distance(nodes, INF);
        vector<int> in_queue(nodes, 0);
        vector<int> previous_node(nodes);
        vector<int> previous_edge(nodes);
        queue<int> q;
        distance[source] = 0;
        q.push(source);
        in_queue[source] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = 0;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                Edge &e = graph[u][i];
                if (e.cap == 0 || distance[e.to] <= distance[u] + e.cost) {
                    continue;
                }
                distance[e.to] = distance[u] + e.cost;
                previous_node[e.to] = u;
                previous_edge[e.to] = i;
                if (!in_queue[e.to]) {
                    in_queue[e.to] = 1;
                    q.push(e.to);
                }
            }
        }

        // 沿记录的前驱边回退，更新残量并累加本次增广的费用。
        int add = 1;
        for (int v = sink; v != source; v = previous_node[v]) {
            Edge &e = graph[previous_node[v]][previous_edge[v]];
            e.cap -= add;
            graph[v][e.rev].cap += add;
            answer += e.cost;
        }
        sent += add;
    }

    cout << answer << '\n';
    return 0;
}