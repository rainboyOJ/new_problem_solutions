/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 13:00
 */
// brute.cpp：每次沿树找出每条旅游路径并直接模拟轮胎状态。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int id;
};

int n, x_code;
vector<Edge> graph[105];
bool station[105];
bool repaired[105];
vector<pair<int, int> > plans;

bool one_plan(int start, int finish) {
    vector<int> parent(n + 1, 0);
    vector<int> parent_edge(n + 1, 0);
    queue<int> que;
    que.push(start);
    parent[start] = -1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].to;
            if (parent[v] != 0) {
                continue;
            }
            parent[v] = u;
            parent_edge[v] = graph[u][i].id;
            que.push(v);
        }
    }
    vector<int> path_vertices;
    vector<int> path_edges;
    int current = finish;
    while (current != start) {
        path_vertices.push_back(current);
        path_edges.push_back(parent_edge[current]);
        current = parent[current];
    }
    path_vertices.push_back(start);
    reverse(path_vertices.begin(), path_vertices.end());
    reverse(path_edges.begin(), path_edges.end());

    int broken = 0;
    for (int i = 0; i < (int)path_edges.size(); i++) {
        if (!repaired[path_edges[i]]) {
            broken++;
        }
        if (broken > 1) {
            return false;
        }
        if (station[path_vertices[i + 1]]) {
            broken = 0;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x_code;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }
    int k;
    cin >> k;
    while (k--) {
        int u;
        cin >> u;
        station[u] = true;
    }
    int m;
    cin >> m;
    plans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> plans[i].first >> plans[i].second;
    }
    int q;
    cin >> q;
    int last_answer = 0;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            u ^= x_code * last_answer;
            v ^= x_code * last_answer;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                if (graph[u][i].to == v) {
                    repaired[graph[u][i].id] = true;
                    break;
                }
            }
        } else {
            int answer = 0;
            for (int i = 0; i < (int)plans.size(); i++) {
                if (one_plan(plans[i].first, plans[i].second)) {
                    answer++;
                }
            }
            cout << answer << '\n';
            last_answer = answer;
        }
    }
    return 0;
}
