/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:01
 */
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);
const int INF_CAP = 1000000000;

struct Edge {
    int to;
    int rev;
    int cap;
    int cost;
};

class MinCostFlow {
public:
    vector<vector<Edge> > graph;

    explicit MinCostFlow(int n) : graph(n) {}

    void add_edge(int from, int to, int cap, int cost) {
        Edge forward = {to, (int)graph[to].size(), cap, cost};
        Edge backward = {from, (int)graph[from].size(), 0, -cost};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    long long solve(int source, int sink, int need) {
        int node_count = (int)graph.size();
        vector<long long> potential(node_count, 0);
        vector<long long> distance(node_count);
        vector<int> previous_node(node_count);
        vector<int> previous_edge(node_count);
        long long answer = 0;
        int flow = 0;

        while (flow < need) {
            fill(distance.begin(), distance.end(), INF);
            distance[source] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int> >,
                           greater<pair<long long, int> > > queue;
            queue.push(make_pair(0, source));

            while (!queue.empty()) {
                pair<long long, int> current = queue.top();
                queue.pop();
                long long current_distance = current.first;
                int u = current.second;
                if (current_distance != distance[u]) continue;

                for (int i = 0; i < (int)graph[u].size(); i++) {
                    Edge &edge = graph[u][i];
                    if (edge.cap == 0) continue;
                    long long next_distance = current_distance + edge.cost
                                              + potential[u] - potential[edge.to];
                    if (next_distance >= distance[edge.to]) continue;
                    distance[edge.to] = next_distance;
                    previous_node[edge.to] = u;
                    previous_edge[edge.to] = i;
                    queue.push(make_pair(next_distance, edge.to));
                }
            }

            if (distance[sink] == INF) break;
            for (int i = 0; i < node_count; i++) {
                if (distance[i] != INF) potential[i] += distance[i];
            }

            int add = need - flow;
            for (int v = sink; v != source; v = previous_node[v]) {
                add = min(add, graph[previous_node[v]][previous_edge[v]].cap);
            }
            for (int v = sink; v != source; v = previous_node[v]) {
                Edge &edge = graph[previous_node[v]][previous_edge[v]];
                answer += (long long)add * edge.cost;
                edge.cap -= add;
                graph[v][edge.rev].cap += add;
            }
            flow += add;
        }
        return answer;
    }
};

int node_id(int day, int city, int n) {
    return day * n + city;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int production[100][7] = {};
    int demand[100][7] = {};
    int storage_capacity[100];
    int storage_cost[100];
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) cin >> production[city][day];
        for (int day = 0; day < 7; day++) cin >> demand[city][day];
        cin >> storage_capacity[city] >> storage_cost[city];
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

    int source = 7 * n;
    int sink = source + 1;
    MinCostFlow flow(sink + 1);
    int total_need = 0;
    for (int city = 0; city < n; city++) {
        for (int day = 0; day < 7; day++) {
            int current = node_id(day, city, n);
            if (production[city][day] > 0) {
                flow.add_edge(source, current, production[city][day], 0);
            }
            if (demand[city][day] > 0) {
                flow.add_edge(current, sink, demand[city][day], 0);
                total_need += demand[city][day];
            }

            int next_day = (day + 1) % 7;
            flow.add_edge(current, node_id(next_day, city, n),
                          storage_capacity[city], storage_cost[city]);
        }
    }

    for (int day = 0; day < 7; day++) {
        for (int i = 0; i < m; i++) {
            int u = node_id(day, roads[i].u, n);
            int v = node_id(day, roads[i].v, n);
            flow.add_edge(u, v, INF_CAP, roads[i].cost);
            flow.add_edge(v, u, INF_CAP, roads[i].cost);
        }
    }

    cout << flow.solve(source, sink, total_need) << '\n';
    return 0;
}
