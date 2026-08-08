#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int NEG_INF = -1000000000;

int n, m, start_x, start_y, seg_cnt;
char grid_map[MAXN][MAXN];
// dp[x][y]：处理完当前这段时间后，钢琴停在 (x,y) 的最大滑行距离。
int dp[MAXN][MAXN];
// old_dp 是上一段时间结束后的状态，当前段的所有转移都只能从它转来。
int old_dp[MAXN][MAXN];
// 单调队列里存的是某一行/列上的候选下标。
int q[MAXN];

struct Segment {
    int l, r, dir;
} seg[MAXN];

// 处理“向上滑动 len 步”的整段转移。
void move_up(int len) {
    for (int col = 1; col <= m; col++) {
        int head = 0, tail = -1;
        for (int row = n; row >= 1; row--) {
            if (grid_map[row][col] == 'x') {
                head = 0;
                tail = -1;
                dp[row][col] = NEG_INF;
                continue;
            }

            // 向上最多走 len 步，所以候选起点行号不能超过 row + len。
            while (head <= tail && q[head] > row + len) {
                head++;
            }

            // 转移式：
            // old_dp[k][col] + (k - row)
            // 对固定 row 来说，只要维护 old_dp[k][col] + k 的最大值即可。
            while (head <= tail &&
                   old_dp[q[tail]][col] + q[tail] <= old_dp[row][col] + row) {
                tail--;
            }
            q[++tail] = row;

            if (old_dp[q[head]][col] <= NEG_INF / 2) {
                dp[row][col] = NEG_INF;
            } else {
                dp[row][col] = old_dp[q[head]][col] + q[head] - row;
            }
        }
    }
}

// 处理“向下滑动 len 步”的整段转移。
void move_down(int len) {
    for (int col = 1; col <= m; col++) {
        int head = 0, tail = -1;
        for (int row = 1; row <= n; row++) {
            if (grid_map[row][col] == 'x') {
                head = 0;
                tail = -1;
                dp[row][col] = NEG_INF;
                continue;
            }

            // 向下最多走 len 步，所以候选起点行号不能小于 row - len。
            while (head <= tail && q[head] < row - len) {
                head++;
            }

            // 转移式：
            // old_dp[k][col] + (row - k)
            // 对固定 row 来说，维护 old_dp[k][col] - k 的最大值。
            while (head <= tail &&
                   old_dp[q[tail]][col] - q[tail] <= old_dp[row][col] - row) {
                tail--;
            }
            q[++tail] = row;

            if (old_dp[q[head]][col] <= NEG_INF / 2) {
                dp[row][col] = NEG_INF;
            } else {
                dp[row][col] = old_dp[q[head]][col] - q[head] + row;
            }
        }
    }
}

// 处理“向左滑动 len 步”的整段转移。
void move_left(int len) {
    for (int row = 1; row <= n; row++) {
        int head = 0, tail = -1;
        for (int col = m; col >= 1; col--) {
            if (grid_map[row][col] == 'x') {
                head = 0;
                tail = -1;
                dp[row][col] = NEG_INF;
                continue;
            }

            // 向左最多走 len 步，所以候选起点列号不能超过 col + len。
            while (head <= tail && q[head] > col + len) {
                head++;
            }

            // 转移式：
            // old_dp[row][k] + (k - col)
            while (head <= tail &&
                   old_dp[row][q[tail]] + q[tail] <= old_dp[row][col] + col) {
                tail--;
            }
            q[++tail] = col;

            if (old_dp[row][q[head]] <= NEG_INF / 2) {
                dp[row][col] = NEG_INF;
            } else {
                dp[row][col] = old_dp[row][q[head]] + q[head] - col;
            }
        }
    }
}

// 处理“向右滑动 len 步”的整段转移。
void move_right(int len) {
    for (int row = 1; row <= n; row++) {
        int head = 0, tail = -1;
        for (int col = 1; col <= m; col++) {
            if (grid_map[row][col] == 'x') {
                head = 0;
                tail = -1;
                dp[row][col] = NEG_INF;
                continue;
            }

            // 向右最多走 len 步，所以候选起点列号不能小于 col - len。
            while (head <= tail && q[head] < col - len) {
                head++;
            }

            // 转移式：
            // old_dp[row][k] + (col - k)
            while (head <= tail &&
                   old_dp[row][q[tail]] - q[tail] <= old_dp[row][col] - col) {
                tail--;
            }
            q[++tail] = col;

            if (old_dp[row][q[head]] <= NEG_INF / 2) {
                dp[row][col] = NEG_INF;
            } else {
                dp[row][col] = old_dp[row][q[head]] - q[head] + col;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_x >> start_y >> seg_cnt;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid_map[i][j];
        }
    }
    for (int i = 1; i <= seg_cnt; i++) {
        cin >> seg[i].l >> seg[i].r >> seg[i].dir;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = NEG_INF;
        }
    }
    dp[start_x][start_y] = 0;

    for (int i = 1; i <= seg_cnt; i++) {
        // 这一段时间的总秒数。
        int len = seg[i].r - seg[i].l + 1;

        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                old_dp[x][y] = dp[x][y];
            }
        }

        // 方向编号：
        // 1 上，2 下，3 左，4 右
        if (seg[i].dir == 1) {
            move_up(len);
        } else if (seg[i].dir == 2) {
            move_down(len);
        } else if (seg[i].dir == 3) {
            move_left(len);
        } else {
            move_right(len);
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
