#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);
const int MAXW = 8;
const int MAXS = 1 << 7;

struct State {
    long long cost;
    int cnt;
};

int n, m;
long long a[55][55];
long long cost_sum[55][MAXS];
State dp[2][MAXS][MAXS];

bool better(const State &x, const State &y) {
    if (x.cost != y.cost) {
        return x.cost < y.cost;
    }
    return x.cnt < y.cnt;
}

State add_state(const State &x, long long add_cost, int add_cnt) {
    if (x.cost >= INF / 2) {
        return {INF, 0};
    }
    return {x.cost + add_cost, x.cnt + add_cnt};
}

bool row_ok(int up, int mid, int down, int full) {
    int cover = mid | up | down | ((mid << 1) & full) | (mid >> 1);
    return cover == full;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int H, W;
    static long long w[55][8];
    if (n >= m) {
        H = n;
        W = m;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                w[i][j] = a[i][j];
            }
        }
    } else {
        H = m;
        W = n;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                w[i][j] = a[j][i];
            }
        }
    }

    int full = (1 << W) - 1;
    for (int i = 1; i <= H; i++) {
        for (int mask = 0; mask <= full; mask++) {
            cost_sum[i][mask] = 0;
            for (int b = 0; b < W; b++) {
                if (mask & (1 << b)) {
                    cost_sum[i][mask] += w[i][b + 1];
                }
            }
        }
    }

    for (int p = 0; p <= 1; p++) {
        for (int s1 = 0; s1 <= full; s1++) {
            for (int s2 = 0; s2 <= full; s2++) {
                dp[p][s1][s2] = {INF, 0};
            }
        }
    }

    // 处理完第 1 行后，上一行是 0，当前行是 cur，尚未检查第 1 行是否被下一行覆盖。
    for (int cur = 0; cur <= full; cur++) {
        dp[1][0][cur] = {cost_sum[1][cur], __builtin_popcount((unsigned int) cur)};
    }

    for (int row = 1; row < H; row++) {
        int now = row & 1;
        int nxt = now ^ 1;
        for (int s1 = 0; s1 <= full; s1++) {
            for (int s2 = 0; s2 <= full; s2++) {
                dp[nxt][s1][s2] = {INF, 0};
            }
        }

        for (int up = 0; up <= full; up++) {
            for (int mid = 0; mid <= full; mid++) {
                State cur_state = dp[now][up][mid];
                if (cur_state.cost >= INF / 2) {
                    continue;
                }
                for (int down = 0; down <= full; down++) {
                    if (!row_ok(up, mid, down, full)) {
                        continue;
                    }
                    State nxt_state = add_state(cur_state, cost_sum[row + 1][down],
                                                __builtin_popcount((unsigned int) down));
                    if (better(nxt_state, dp[nxt][mid][down])) {
                        dp[nxt][mid][down] = nxt_state;
                    }
                }
            }
        }
    }

    int last = H & 1;
    State ans = {INF, 0};
    for (int up = 0; up <= full; up++) {
        for (int mid = 0; mid <= full; mid++) {
            State cur_state = dp[last][up][mid];
            if (cur_state.cost >= INF / 2) {
                continue;
            }
            if (!row_ok(up, mid, 0, full)) {
                continue;
            }
            if (better(cur_state, ans)) {
                ans = cur_state;
            }
        }
    }

    cout << ans.cnt << ' ' << ans.cost << '\n';
    return 0;
}
