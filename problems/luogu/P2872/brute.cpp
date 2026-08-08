#include <bits/stdc++.h>
using namespace std;

// brute.cpp：Prim 版本最小生成树，用不同实现辅助对拍。

const int MAXN = 105;
const double INF = 1e100;

int n, m;
long long x_pos[MAXN], y_pos[MAXN];
double cost[MAXN][MAXN];
double dist_to_tree[MAXN];
bool used[MAXN];

double distance_between(int i, int j) {
    double dx = (double)(x_pos[i] - x_pos[j]);
    double dy = (double)(y_pos[i] - y_pos[j]);
    return sqrt(dx * dx + dy * dy);
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] = distance_between(i, j);
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cost[u][v] = 0.0;
        cost[v][u] = 0.0;
    }
}

double prim() {
    for (int i = 1; i <= n; i++) {
        dist_to_tree[i] = INF;
        used[i] = false;
    }
    dist_to_tree[1] = 0.0;

    double answer = 0.0;
    for (int step = 1; step <= n; step++) {
        int u = 0;
        for (int i = 1; i <= n; i++) {
            if (!used[i] && (u == 0 || dist_to_tree[i] < dist_to_tree[u])) {
                u = i;
            }
        }

        used[u] = true;
        answer += dist_to_tree[u];

        for (int v = 1; v <= n; v++) {
            if (!used[v] && cost[u][v] < dist_to_tree[v]) {
                dist_to_tree[v] = cost[u][v];
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << fixed << setprecision(2) << prim() << '\n';

    return 0;
}
