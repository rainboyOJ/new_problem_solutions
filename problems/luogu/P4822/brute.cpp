#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const long long INF = (1LL << 60);

int n, m, k;
long long dist_arr[105][105];

int state_id(int city, int used) {
    return used * n + city;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

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

    // 直接把分层图完整建出来：
    // 第 used 层表示已经用了 used 张卡。
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
                int c = state_id(u, used);
                int d = state_id(v, used + 1);
                if (len / 2 < dist_arr[c][d]) {
                    dist_arr[c][d] = len / 2;
                }

                c = state_id(v, used);
                d = state_id(u, used + 1);
                if (len / 2 < dist_arr[c][d]) {
                    dist_arr[c][d] = len / 2;
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
        if (dist_arr[state_id(1, 0)][state_id(n, used)] < answer) {
            answer = dist_arr[state_id(1, 0)][state_id(n, used)];
        }
    }

    cout << answer << '\n';

    return 0;
}
