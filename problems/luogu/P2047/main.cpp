#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 5;
const long long INF = (1LL << 60);

int n, m;
long long dist_arr[MAXN][MAXN];
long long cnt_arr[MAXN][MAXN];
long double answer[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
                cnt_arr[i][j] = 1;
            }
            else {
                dist_arr[i][j] = INF;
                cnt_arr[i][j] = 0;
            }
        }
        answer[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        if (w < dist_arr[u][v]) {
            dist_arr[u][v] = dist_arr[v][u] = w;
            cnt_arr[u][v] = cnt_arr[v][u] = 1;
        }
        else if (w == dist_arr[u][v]) {
            cnt_arr[u][v]++;
            cnt_arr[v][u]++;
        }
    }

    // Floyd + 最短路条数统计。
    // 如果经过 k 更短，就替换距离和条数；
    // 如果经过 k 一样短，就把这部分方案数加上。
    // 这里跳过 i==k 或 j==k，避免用到 dist[i][i] 这类平凡路径时重复计数。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (i == k) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (j == k || i == j) {
                    continue;
                }

                long long nd = dist_arr[i][k] + dist_arr[k][j];
                long long ways = cnt_arr[i][k] * cnt_arr[k][j];

                if (nd < dist_arr[i][j]) {
                    dist_arr[i][j] = nd;
                    cnt_arr[i][j] = ways;
                }
                else if (nd == dist_arr[i][j]) {
                    cnt_arr[i][j] += ways;
                }
            }
        }
    }

    // 如果 v 在 s 到 t 的最短路上，那么一定满足：
    // dist[s][v] + dist[v][t] == dist[s][t]
    // 此时经过 v 的最短路条数就是 cnt[s][v] * cnt[v][t]。
    for (int v = 1; v <= n; v++) {
        for (int s = 1; s <= n; s++) {
            if (s == v) {
                continue;
            }
            for (int t = 1; t <= n; t++) {
                if (t == v || t == s) {
                    continue;
                }

                if (dist_arr[s][v] + dist_arr[v][t] == dist_arr[s][t]) {
                    answer[v] += (long double) cnt_arr[s][v] * cnt_arr[v][t] / cnt_arr[s][t];
                }
            }
        }
    }

    cout << fixed << setprecision(3);
    for (int i = 1; i <= n; i++) {
        cout << (double) answer[i] << '\n';
    }

    return 0;
}
