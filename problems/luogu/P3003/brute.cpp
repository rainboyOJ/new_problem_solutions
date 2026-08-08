// brute.cpp：用 Floyd 求任意两点最短路，再直接枚举两种送货顺序。
// 只适合小数据，但最贴近题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXP = 105;
const long long INF = (1LL << 60);

int c, p, pb, pa1, pa2;
long long dist_arr[MAXP][MAXP];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> p >> pb >> pa1 >> pa2;

    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= p; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= c; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        if (len < dist_arr[u][v]) {
            dist_arr[u][v] = len;
            dist_arr[v][u] = len;
        }
    }

    for (int k = 1; k <= p; k++) {
        for (int i = 1; i <= p; i++) {
            for (int j = 1; j <= p; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    long long ans1 = dist_arr[pb][pa1] + dist_arr[pa1][pa2];
    long long ans2 = dist_arr[pb][pa2] + dist_arr[pa2][pa1];

    cout << min(ans1, ans2) << '\n';

    return 0;
}
