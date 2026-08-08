// brute.cpp：用 Floyd 求 1 号点到所有点的最短距离。
// 只适合小数据，但逻辑最直接。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 1e9;

int n, m;
int dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        dist_arr[u][v] = 1;
        dist_arr[v][u] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    int best_id = 1;
    int best_dist = -1;
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (dist_arr[1][i] > best_dist) {
            best_dist = dist_arr[1][i];
            best_id = i;
            count = 1;
        }
        else if (dist_arr[1][i] == best_dist) {
            count++;
        }
    }

    cout << best_id << ' ' << best_dist << ' ' << count << '\n';

    return 0;
}
