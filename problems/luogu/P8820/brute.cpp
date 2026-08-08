// brute.cpp：小数据暴力解，先 Floyd 求树上距离，再在可直接传输图上 Floyd 求最短路。
#include <bits/stdc++.h>
using namespace std;

const long long INF = (long long)4e18;
const int MAXN = 55;

int n, q, K;
long long value_cost[MAXN];
long long tree_dist[MAXN][MAXN];
long long answer_dist[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> K;
    for (int i = 1; i <= n; i++) {
        cin >> value_cost[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            tree_dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree_dist[u][v] = tree_dist[v][u] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (tree_dist[i][j] > tree_dist[i][k] + tree_dist[k][j]) {
                    tree_dist[i][j] = tree_dist[i][k] + tree_dist[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            answer_dist[i][j] = INF;
        }
        answer_dist[i][i] = value_cost[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && tree_dist[i][j] <= K) {
                answer_dist[i][j] = value_cost[i] + value_cost[j];
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (answer_dist[i][j] > answer_dist[i][k] + answer_dist[k][j] - value_cost[k]) {
                    answer_dist[i][j] = answer_dist[i][k] + answer_dist[k][j] - value_cost[k];
                }
            }
        }
    }

    while (q--) {
        int s, t;
        cin >> s >> t;
        cout << answer_dist[s][t] << '\n';
    }

    return 0;
}
