// brute.cpp：小数据暴力解，删边后枚举每个点并直接检查它是不是所在连通块重心。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
bool edge_exist[MAXN][MAXN];
pair<int, int> edges[MAXN];
vector<int> component_nodes;
bool in_component[MAXN], visited_node[MAXN];

void collect_component(int start, int ban_u, int ban_v) {
    component_nodes.clear();
    memset(in_component, 0, sizeof(in_component));
    memset(visited_node, 0, sizeof(visited_node));

    queue<int> q;
    q.push(start);
    visited_node[start] = true;
    in_component[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        component_nodes.push_back(u);
        for (int v = 1; v <= n; v++) {
            if (!edge_exist[u][v]) {
                continue;
            }
            if ((u == ban_u && v == ban_v) || (u == ban_v && v == ban_u)) {
                continue;
            }
            if (!visited_node[v]) {
                visited_node[v] = true;
                in_component[v] = true;
                q.push(v);
            }
        }
    }
}

int count_part(int start, int banned_center) {
    queue<int> q;
    bool vis[MAXN] = {false};
    q.push(start);
    vis[start] = true;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        for (int v = 1; v <= n; v++) {
            if (v == banned_center || !in_component[v] || !edge_exist[u][v] || vis[v]) {
                continue;
            }
            vis[v] = true;
            q.push(v);
        }
    }
    return cnt;
}

long long centroid_sum_of_component() {
    int total = (int)component_nodes.size();
    long long result = 0;
    for (int idx = 0; idx < total; idx++) {
        int c = component_nodes[idx];
        int max_part = 0;
        for (int v = 1; v <= n; v++) {
            if (in_component[v] && edge_exist[c][v]) {
                max_part = max(max_part, count_part(v, c));
            }
        }
        if (max_part <= total / 2) {
            result += c;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        memset(edge_exist, 0, sizeof(edge_exist));
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            edges[i] = make_pair(u, v);
            edge_exist[u][v] = edge_exist[v][u] = true;
        }

        long long answer = 0;
        for (int i = 1; i < n; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            collect_component(u, u, v);
            answer += centroid_sum_of_component();
            collect_component(v, u, v);
            answer += centroid_sum_of_component();
        }
        cout << answer << '\n';
    }

    return 0;
}
