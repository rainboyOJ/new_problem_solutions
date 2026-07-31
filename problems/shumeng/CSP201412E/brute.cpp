/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:30
 */
// brute.cpp：小数据基准，逐吨使用 SPFA 求最短增广路。
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
const int INF_CAP = 1000000000;

struct Edge { int to, rev, cap, cost; };
vector<vector<Edge> > graph;

void add_edge(int u, int v, int cap, int cost) {
    Edge a = {v, (int)graph[v].size(), cap, cost};
    Edge b = {u, (int)graph[u].size(), 0, -cost};
    graph[u].push_back(a);
    graph[v].push_back(b);
}

int id(int day, int city, int n) { return day * n + city; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int production[10][7] = {};
    int demand[10][7] = {};
    int capacity[10], hold_cost[10];
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) cin >> production[city][day];
        for (int day = 0; day < 7; day++) cin >> demand[city][day];
        cin >> capacity[city] >> hold_cost[city];
    }
    struct Road { int u, v, cost; };
    vector<Road> roads(m);
    for (int i = 0; i < m; i++) {
        cin >> roads[i].u >> roads[i].v >> roads[i].cost;
        roads[i].u--;
        roads[i].v--;
    }

    int source = 7 * n;
    int sink = source + 1;
    graph.assign(sink + 1, vector<Edge>());
    int total = 0;
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) {
            int current = id(day, city, n);
            add_edge(source, current, production[city][day], 0);
            add_edge(current, sink, demand[city][day], 0);
            add_edge(current, id((day + 1) % 7, city, n), capacity[city], hold_cost[city]);
            total += demand[city][day];
        }
    }
    for (int day = 0; day < 7; day++) {
        for (int i = 0; i < m; i++) {
            add_edge(id(day, roads[i].u, n), id(day, roads[i].v, n), INF_CAP, roads[i].cost);
            add_edge(id(day, roads[i].v, n), id(day, roads[i].u, n), INF_CAP, roads[i].cost);
        }
    }

    long long answer = 0;
    int sent = 0;
    int nodes = sink + 1;
    while (sent < total) {
        vector<int> distance(nodes, INF), in_queue(nodes, 0), pv(nodes), pe(nodes);
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
                if (e.cap == 0 || distance[e.to] <= distance[u] + e.cost) continue;
                distance[e.to] = distance[u] + e.cost;
                pv[e.to] = u;
                pe[e.to] = i;
                if (!in_queue[e.to]) {
                    in_queue[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        int add = 1;
        for (int v = sink; v != source; v = pv[v]) {
            Edge &e = graph[pv[v]][pe[v]];
            e.cap -= add;
            graph[v][e.rev].cap += add;
            answer += e.cost;
        }
        sent += add;
    }
    cout << answer << '\n';
    return 0;
}
