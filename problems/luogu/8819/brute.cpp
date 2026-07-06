// brute.cpp：小数据暴力解，直接维护每条边是否可用并检查每个点当前出度。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m, q;
bool exist_edge[MAXN][MAXN];
bool active_edge[MAXN][MAXN];

bool can_counterattack() {
    for (int u = 1; u <= n; u++) {
        int out_degree = 0;
        for (int v = 1; v <= n; v++) {
            if (active_edge[u][v]) {
                out_degree++;
            }
        }
        if (out_degree != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        exist_edge[u][v] = true;
        active_edge[u][v] = true;
    }

    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            active_edge[u][v] = false;
        } else if (type == 2) {
            int v;
            cin >> v;
            for (int u = 1; u <= n; u++) {
                if (exist_edge[u][v]) {
                    active_edge[u][v] = false;
                }
            }
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            if (exist_edge[u][v]) {
                active_edge[u][v] = true;
            }
        } else {
            int v;
            cin >> v;
            for (int u = 1; u <= n; u++) {
                if (exist_edge[u][v]) {
                    active_edge[u][v] = true;
                }
            }
        }

        cout << (can_counterattack() ? "YES" : "NO") << '\n';
    }

    return 0;
}
