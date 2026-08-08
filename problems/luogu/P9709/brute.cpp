// brute.cpp：小图状压 DP，直接按“占领集合”转移。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 20;
const int INF = 1e9;

int n, board_size;
int x[MAXN], y[MAXN];
int board_dist[MAXM][MAXM];
int city_dist[MAXN][MAXN];
int dp[1 << MAXN];
int dx[8] = {-1, 1, 2, -2, -1, 1, 2, -2};
int dy[8] = {2, 2, 1, 1, -2, -2, -1, -1};

void bfs_from(int start_id) {
    for (int i = 1; i <= board_size; i++) {
        for (int j = 1; j <= board_size; j++) {
            board_dist[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    q.push({x[start_id], y[start_id]});
    board_dist[x[start_id]][y[start_id]] = 0;

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();

        int cx = cur.first;
        int cy = cur.second;

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx <= 0 || ny <= 0 || nx > board_size || ny > board_size) {
                continue;
            }
            if (board_dist[nx][ny] != -1) {
                continue;
            }

            board_dist[nx][ny] = board_dist[cx][cy] + 1;
            q.push({nx, ny});
        }
    }

    for (int i = 1; i <= n; i++) {
        city_dist[start_id][i] = board_dist[x[i]][y[i]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> board_size;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= n; i++) {
        bfs_from(i);
    }

    int max_mask = 1 << n;
    for (int i = 0; i < max_mask; i++) {
        dp[i] = INF;
    }
    dp[1 << 0] = 0;

    for (int mask = 0; mask < max_mask; mask++) {
        if (dp[mask] == INF) {
            continue;
        }

        for (int j = 1; j <= n; j++) {
            if ((mask >> (j - 1)) & 1) {
                continue;
            }

            int best = INF;
            for (int i = 1; i <= n; i++) {
                if (((mask >> (i - 1)) & 1) == 0) {
                    continue;
                }
                if (city_dist[i][j] == -1) {
                    continue;
                }
                best = min(best, city_dist[i][j] + 1);
            }

            if (best == INF) {
                continue;
            }

            int next_mask = mask | (1 << (j - 1));
            dp[next_mask] = min(dp[next_mask], dp[mask] + best);
        }
    }

    if (dp[max_mask - 1] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[max_mask - 1] << '\n';
    }

    return 0;
}
