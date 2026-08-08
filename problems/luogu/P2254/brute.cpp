#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXT = 205;
const int NEG_INF = -1000000000;

int n, m, start_x, start_y, seg_cnt;
char grid_map[MAXN][MAXN];
int dp[MAXN][MAXN], nxt_dp[MAXN][MAXN];
int dir_list[MAXT], total_time;
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：按时间一秒一秒地做 DP。
    // 每一秒只有两种选择：施魔法原地不动，或者顺着当前方向滑动一格。
    cin >> n >> m >> start_x >> start_y >> seg_cnt;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid_map[i][j];
        }
    }

    total_time = 0;
    for (int i = 1; i <= seg_cnt; i++) {
        int l, r, d;
        cin >> l >> r >> d;
        int len = r - l + 1;
        for (int t = 1; t <= len; t++) {
            dir_list[++total_time] = d;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = NEG_INF;
        }
    }
    dp[start_x][start_y] = 0;

    for (int t = 1; t <= total_time; t++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                nxt_dp[i][j] = NEG_INF;
            }
        }

        int d = dir_list[t];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (dp[i][j] <= NEG_INF / 2) {
                    continue;
                }

                // 这一秒施魔法，原地不动。
                nxt_dp[i][j] = max(nxt_dp[i][j], dp[i][j]);

                // 这一秒不施魔法，顺着当前方向滑一格。
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 1 && ni <= n && nj >= 1 && nj <= m &&
                    grid_map[ni][nj] != 'x') {
                    nxt_dp[ni][nj] = max(nxt_dp[ni][nj], dp[i][j] + 1);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = nxt_dp[i][j];
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << '\n';
    return 0;
}
