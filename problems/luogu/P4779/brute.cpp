// brute.cpp：小数据朴素解，用 Bellman-Ford 松弛所有边来辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int MAXM = 2005;
const long long INF = (1LL << 62);

struct Edge {
    int u, v;
    long long w;
};

int n, m, s;
Edge e[MAXM];
long long dist_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }

    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
    }
    dist_arr[s] = 0;

    for (int round = 1; round <= n - 1; round++) {
        bool changed = false;
        for (int i = 1; i <= m; i++) {
            int u = e[i].u;
            int v = e[i].v;
            if (dist_arr[u] != INF && dist_arr[v] > dist_arr[u] + e[i].w) {
                dist_arr[v] = dist_arr[u] + e[i].w;
                changed = true;
            }
        }
        if (!changed) {
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << dist_arr[i];
    }
    cout << '\n';
    return 0;
}
