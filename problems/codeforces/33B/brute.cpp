/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 08:54
 * update_at: 2026-11-13 08:54
 */
// brute.cpp：基于 26 次独立单源 Dijkstra 的对照解法，用于对拍验证
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e15;
struct Edge {
    int to;
    long long w;
};

vector<Edge> adj[26];
long long dist_matrix[26][26];

void dijkstra(int start_node) {
    for (int i = 0; i < 26; ++i) {
        dist_matrix[start_node][i] = INF;
    }
    dist_matrix[start_node][start_node] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start_node});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist_matrix[start_node][u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist_matrix[start_node][u] + edge.w < dist_matrix[start_node][edge.to]) {
                dist_matrix[start_node][edge.to] = dist_matrix[start_node][u] + edge.w;
                pq.push({dist_matrix[start_node][edge.to], edge.to});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    if (!(cin >> s >> t)) return 0;
    if (s.length() != t.length()) {
        cout << -1 << "\n";
        return 0;
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char u_ch, v_ch;
        long long w;
        cin >> u_ch >> v_ch >> w;
        adj[u_ch - 'a'].push_back({v_ch - 'a', w});
    }

    for (int i = 0; i < 26; ++i) {
        dijkstra(i);
    }

    long long total_cost = 0;
    string res = "";

    for (size_t i = 0; i < s.length(); ++i) {
        int u = s[i] - 'a';
        int v = t[i] - 'a';

        long long min_cost = INF;
        int best_ch = -1;

        for (int to = 0; to < 26; ++to) {
            long long cur = dist_matrix[u][to] + dist_matrix[v][to];
            if (cur < min_cost) {
                min_cost = cur;
                best_ch = to;
            }
        }

        if (min_cost >= INF) {
            cout << -1 << "\n";
            return 0;
        }

        total_cost += min_cost;
        res.push_back((char)('a' + best_ch));
    }

    cout << total_cost << "\n";
    cout << res << "\n";
    return 0;
}
