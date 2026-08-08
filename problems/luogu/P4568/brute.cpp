#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

int n, m, k;
int s, t;
long long dist_arr[205][205];

int state_id(int city, int used) {
    return used * n + city + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    cin >> s >> t;

    int tot = (k + 1) * n;
    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= tot; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;

        for (int used = 0; used <= k; used++) {
            int a = state_id(u, used);
            int b = state_id(v, used);
            if (len < dist_arr[a][b]) {
                dist_arr[a][b] = len;
                dist_arr[b][a] = len;
            }

            if (used < k) {
                a = state_id(u, used);
                b = state_id(v, used + 1);
                if (0 < dist_arr[a][b]) {
                    dist_arr[a][b] = 0;
                }

                a = state_id(v, used);
                b = state_id(u, used + 1);
                if (0 < dist_arr[a][b]) {
                    dist_arr[a][b] = 0;
                }
            }
        }
    }

    for (int mid = 1; mid <= tot; mid++) {
        for (int i = 1; i <= tot; i++) {
            if (dist_arr[i][mid] >= INF / 2) {
                continue;
            }
            for (int j = 1; j <= tot; j++) {
                if (dist_arr[mid][j] >= INF / 2) {
                    continue;
                }
                long long nd = dist_arr[i][mid] + dist_arr[mid][j];
                if (nd < dist_arr[i][j]) {
                    dist_arr[i][j] = nd;
                }
            }
        }
    }

    long long answer = INF;
    for (int used = 0; used <= k; used++) {
        if (dist_arr[state_id(s, 0)][state_id(t, used)] < answer) {
            answer = dist_arr[state_id(s, 0)][state_id(t, used)];
        }
    }

    cout << answer << '\n';

    return 0;
}
