/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:47
 */
// brute.cpp：小数据暴力解，建出完整网络后用 Dinic 求最大流。
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

struct Edge {
    int to, reverse;
    long long capacity;
};

struct Dinic {
    vector<vector<Edge> > graph;
    vector<int> level, current;

    Dinic(int node_count) : graph(node_count), level(node_count), current(node_count) {}

    void add_edge(int from, int to, long long capacity) {
        Edge forward = {to, (int)graph[to].size(), capacity};
        Edge backward = {from, (int)graph[from].size(), 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < (int)graph[x].size(); i++) {
                Edge &edge = graph[x][i];
                if (edge.capacity > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[x] + 1;
                    que.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    long long dfs(int x, int sink, long long flow) {
        if (x == sink) {
            return flow;
        }
        for (int &i = current[x]; i < (int)graph[x].size(); i++) {
            Edge &edge = graph[x][i];
            if (edge.capacity == 0 || level[edge.to] != level[x] + 1) {
                continue;
            }
            long long pushed = dfs(edge.to, sink, min(flow, edge.capacity));
            if (pushed == 0) {
                continue;
            }
            edge.capacity -= pushed;
            graph[edge.to][edge.reverse].capacity += pushed;
            return pushed;
        }
        return 0;
    }

    long long max_flow(int source, int sink) {
        long long answer = 0;
        while (bfs(source, sink)) {
            fill(current.begin(), current.end(), 0);
            while (true) {
                long long pushed = dfs(source, sink, INF);
                if (pushed == 0) {
                    break;
                }
                answer += pushed;
            }
        }
        return answer;
    }
};

long long next_value(long long &x, long long a, long long b, long long q) {
    x = (a * x + b) % q;
    return x;
}

int get_id(int row, int column, int m) {
    return (row - 1) * m + column - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long a, b, q, x;
    cin >> n >> m >> a >> b >> q >> x;

    int source = n * m;
    int sink = source + 1;
    Dinic dinic(sink + 1);
    for (int column = 1; column <= m; column++) {
        dinic.add_edge(source, get_id(1, column, m), INF);
        dinic.add_edge(get_id(n, column, m), sink, INF);
    }
    for (int row = 1; row <= n - 1; row++) {
        for (int column = 1; column <= m; column++) {
            long long capacity = next_value(x, a, b, q);
            int upper = get_id(row, column, m);
            int lower = get_id(row + 1, column, m);
            dinic.add_edge(upper, lower, capacity);
            dinic.add_edge(lower, upper, INF);
        }
    }
    for (int row = 2; row <= n - 1; row++) {
        for (int column = 1; column <= m - 1; column++) {
            long long capacity = next_value(x, a, b, q);
            int left = get_id(row, column, m);
            int right = get_id(row, column + 1, m);
            dinic.add_edge(left, right, capacity);
            dinic.add_edge(right, left, capacity);
        }
    }

    cout << dinic.max_flow(source, sink) << '\n';

    return 0;
}
