#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = (1LL << 60);

int n, m;
int eu[1005], ev[1005];
long long ew[1005];
long long dist_arr[MAXN][MAXN];
long long backup_dist[MAXN][MAXN];

void floyd(long long a[MAXN][MAXN]) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (a[i][k] >= INF / 2) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (a[k][j] >= INF / 2) {
                    continue;
                }
                long long nd = a[i][k] + a[k][j];
                if (nd < a[i][j]) {
                    a[i][j] = nd;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                backup_dist[i][j] = 0;
            }
            else {
                backup_dist[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        cin >> eu[i] >> ev[i] >> ew[i];
        backup_dist[eu[i]][ev[i]] = ew[i];
        backup_dist[ev[i]][eu[i]] = ew[i];
    }

    long long answer = 0;

    // 暴力枚举哪条边被封掉，然后重跑一次 Floyd。
    for (int ban = 1; ban <= m; ban++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist_arr[i][j] = backup_dist[i][j];
            }
        }

        dist_arr[eu[ban]][ev[ban]] = INF;
        dist_arr[ev[ban]][eu[ban]] = INF;

        floyd(dist_arr);
        answer = max(answer, dist_arr[1][n]);
    }

    cout << answer << '\n';

    return 0;
}
