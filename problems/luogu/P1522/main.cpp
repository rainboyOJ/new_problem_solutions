#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;
const long double INF = 1e100L;

int n;
long double x[MAXN], y[MAXN];
long double dist_arr[MAXN][MAXN];
long double farthest_dist[MAXN];

long double get_dist(int i, int j) {
    long double dx = x[i] - x[j];
    long double dy = y[i] - y[j];
    return sqrtl(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

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

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1] == '1') {
                dist_arr[i][j] = get_dist(i, j);
            }
        }
    }

    // 先求出原图中每个连通块内部的任意两点最短路。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist_arr[i][k] >= INF / 2) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (dist_arr[k][j] >= INF / 2) {
                    continue;
                }
                long double nd = dist_arr[i][k] + dist_arr[k][j];
                if (nd < dist_arr[i][j]) {
                    dist_arr[i][j] = nd;
                }
            }
        }
    }

    long double old_diameter = 0;
    for (int i = 1; i <= n; i++) {
        farthest_dist[i] = 0;
        for (int j = 1; j <= n; j++) {
            if (dist_arr[i][j] >= INF / 2) {
                continue;
            }
            if (dist_arr[i][j] > farthest_dist[i]) {
                farthest_dist[i] = dist_arr[i][j];
            }
        }
        if (farthest_dist[i] > old_diameter) {
            old_diameter = farthest_dist[i];
        }
    }

    long double answer = INF;

    // 枚举新边的两个端点。只有原本不连通时，这条边才有意义。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist_arr[i][j] < INF / 2) {
                continue;
            }

            long double bridge = get_dist(i, j);
            long double new_diameter = farthest_dist[i] + bridge + farthest_dist[j];

            // 别的连通块可能还有更大的旧直径，也要一起保留。
            long double cand = max(old_diameter, new_diameter);
            if (cand < answer) {
                answer = cand;
            }
        }
    }

    cout << fixed << setprecision(6) << (double) answer << '\n';

    return 0;
}
