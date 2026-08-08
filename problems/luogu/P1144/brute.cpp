#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据用 Floyd 求最短距离，再按距离层统计最短路条数。

const int MAXN = 55;
const int INF = 1000000000;
const int MOD = 100003;

int n, m;
int edge_count[MAXN][MAXN];
int dist_node[MAXN][MAXN];
int ways[MAXN];

bool cmp_by_dist_from_one(int a, int b) {
    return dist_node[1][a] < dist_node[1][b];
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist_node[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edge_count[u][v]++;
        edge_count[v][u]++;
        dist_node[u][v] = 1;
        dist_node[v][u] = 1;
    }
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist_node[i][k] + dist_node[k][j] < dist_node[i][j]) {
                    dist_node[i][j] = dist_node[i][k] + dist_node[k][j];
                }
            }
        }
    }
}

void count_paths() {
    vector<int> order;
    for (int i = 1; i <= n; i++) {
        order.push_back(i);
        ways[i] = 0;
    }
    sort(order.begin(), order.end(), cmp_by_dist_from_one);

    ways[1] = 1;
    for (int idx = 0; idx < (int)order.size(); idx++) {
        int u = order[idx];
        if (dist_node[1][u] >= INF) {
            continue;
        }
        for (int v = 1; v <= n; v++) {
            if (edge_count[u][v] > 0 && dist_node[1][v] == dist_node[1][u] + 1) {
                ways[v] = (ways[v] + (long long)ways[u] * edge_count[u][v]) % MOD;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    floyd();
    count_paths();

    for (int i = 1; i <= n; i++) {
        cout << ways[i] << '\n';
    }

    return 0;
}
