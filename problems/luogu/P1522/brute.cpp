#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;
const long double INF = 1e100L;

int n;
long double x[MAXN], y[MAXN];
long double base_dist[MAXN][MAXN];
long double work_dist[MAXN][MAXN];

long double get_dist(int i, int j) {
    long double dx = x[i] - x[j];
    long double dy = y[i] - y[j];
    return sqrtl(dx * dx + dy * dy);
}

void floyd(long double dist_arr[MAXN][MAXN]) {
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
}

long double calc_diameter(long double dist_arr[MAXN][MAXN]) {
    long double ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist_arr[i][j] >= INF / 2) {
                continue;
            }
            if (dist_arr[i][j] > ret) {
                ret = dist_arr[i][j];
            }
        }
    }
    return ret;
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
                base_dist[i][j] = 0;
            }
            else {
                base_dist[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1] == '1') {
                base_dist[i][j] = get_dist(i, j);
            }
        }
    }

    floyd(base_dist);

    long double answer = INF;

    // 朴素思路：枚举每一条可加的新边，真的把它加上，再重跑一次 Floyd。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (base_dist[i][j] < INF / 2) {
                continue;
            }

            for (int a = 1; a <= n; a++) {
                for (int b = 1; b <= n; b++) {
                    work_dist[a][b] = base_dist[a][b];
                }
            }

            long double bridge = get_dist(i, j);
            work_dist[i][j] = bridge;
            work_dist[j][i] = bridge;

            floyd(work_dist);

            long double cand = calc_diameter(work_dist);
            if (cand < answer) {
                answer = cand;
            }
        }
    }

    cout << fixed << setprecision(6) << (double) answer << '\n';

    return 0;
}
