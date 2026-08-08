#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const long double INF = 1e100L;

int n, w;
long double limit_len;
long long x[MAXN], y[MAXN];
bool has_wire[MAXN][MAXN];
long double cost[MAXN][MAXN];
long double dist_arr[MAXN];
bool vis[MAXN];

long double get_dist(int i, int j) {
    long double dx = x[i] - x[j];
    long double dy = y[i] - y[j];
    return sqrtl(dx * dx + dy * dy);
}

void build_graph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cost[i][j] = 0;
            }
            else {
                cost[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (has_wire[i][j]) {
                cost[i][j] = 0;
                cost[j][i] = 0;
                continue;
            }

            long double d = get_dist(i, j);
            if (d <= limit_len + 1e-12L) {
                cost[i][j] = d;
                cost[j][i] = d;
            }
        }
    }
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    dist_arr[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_arr[j] < dist_arr[u]) {
                u = j;
            }
        }

        if (u == 0 || dist_arr[u] >= INF / 2) {
            break;
        }

        vis[u] = true;

        for (int v = 1; v <= n; v++) {
            if (vis[v] || cost[u][v] >= INF / 2) {
                continue;
            }
            long double nd = dist_arr[u] + cost[u][v];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    cin >> limit_len;

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= w; i++) {
        int u, v;
        cin >> u >> v;
        has_wire[u][v] = true;
        has_wire[v][u] = true;
    }

    build_graph();
    dijkstra(1);

    if (dist_arr[n] >= INF / 2) {
        cout << -1 << '\n';
        return 0;
    }

    // 题目要求输出答案乘 1000 后的整数部分。
    cout << (long long) floor(dist_arr[n] * 1000.0L + 1e-9L) << '\n';

    return 0;
}
