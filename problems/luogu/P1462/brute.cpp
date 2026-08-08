// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = (1LL << 60);

int n, m;
long long blood_limit;
int fee[MAXN];
long long dist_mat[MAXN][MAXN];

bool can_with_limit(int limit) {
    if (fee[1] > limit || fee[n] > limit) {
        return false;
    }

    long long d[MAXN][MAXN];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = dist_mat[i][j];
        }
    }

    for (int k = 1; k <= n; k++) {
        if (fee[k] > limit) {
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (fee[i] > limit || d[i][k] == INF) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (fee[j] > limit || d[k][j] == INF) {
                    continue;
                }
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    return d[1][n] <= blood_limit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> blood_limit;
    vector<int> values;
    for (int i = 1; i <= n; i++) {
        cin >> fee[i];
        values.push_back(fee[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist_mat[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist_mat[u][v] = min(dist_mat[u][v], (long long)w);
        dist_mat[v][u] = min(dist_mat[v][u], (long long)w);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    for (int i = 0; i < (int)values.size(); i++) {
        if (can_with_limit(values[i])) {
            cout << values[i] << '\n';
            return 0;
        }
    }

    cout << "AFK\n";
    return 0;
}
