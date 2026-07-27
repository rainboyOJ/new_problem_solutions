/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-24 17:47
 * update_at: 2026-07-24 17:51
 */
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
const int MAXN = 10005;
const int MAXM = 1005;

int n, m, k;
int up_step[MAXN], down_step[MAXN];
int has_pipe[MAXN], pipe_low[MAXN], pipe_high[MAXN];
int dp[MAXM], next_dp[MAXM];

bool has_reachable_height() {
    for (int height = 1; height <= m; height++) {
        if (dp[height] < INF) {
            return true;
        }
    }
    return false;
}

int minimum_clicks() {
    for (int height = 1; height <= m; height++) {
        dp[height] = 0;
    }

    int passed_pipes = 0;
    for (int position = 1; position <= n; position++) {
        for (int height = 1; height <= m; height++) {
            next_dp[height] = INF;
        }

        int rise = up_step[position - 1];
        int fall = down_step[position - 1];

        // 点击一次到达 min(m, height + rise)，再用下面的循环补齐连续点击。
        for (int height = 1; height <= m; height++) {
            if (dp[height] >= INF) {
                continue;
            }
            int target = min(m, height + rise);
            next_dp[target] = min(next_dp[target], dp[height] + 1);
        }

        // 对于还没有到顶的高度，每增加 rise 高度需要再点击一次。
        for (int height = rise + 1; height < m; height++) {
            if (next_dp[height - rise] < INF) {
                next_dp[height] = min(next_dp[height], next_dp[height - rise] + 1);
            }
        }

        // 到达 m 时会封顶，所以 m-rise 到 m-1 的状态都能一步到达 m。
        int source_begin = max(1, m - rise);
        for (int height = source_begin; height < m; height++) {
            if (next_dp[height] < INF) {
                next_dp[m] = min(next_dp[m], next_dp[height] + 1);
            }
        }

        // 不点击时下降 fall，高度不能降到 0。
        for (int height = fall + 1; height <= m; height++) {
            if (dp[height] < INF) {
                next_dp[height - fall] = min(next_dp[height - fall], dp[height]);
            }
        }

        for (int height = 1; height <= m; height++) {
            dp[height] = next_dp[height];
        }

        if (has_pipe[position]) {
            for (int height = 1; height <= m; height++) {
                if (height <= pipe_low[position] || height >= pipe_high[position]) {
                    dp[height] = INF;
                }
            }
            if (!has_reachable_height()) {
                cout << 0 << '\n' << passed_pipes << '\n';
                return -1;
            }
            passed_pipes++;
        } else if (!has_reachable_height()) {
            cout << 0 << '\n' << passed_pipes << '\n';
            return -1;
        }
    }

    int answer = INF;
    for (int height = 1; height <= m; height++) {
        answer = min(answer, dp[height]);
    }
    cout << 1 << '\n' << answer << '\n';
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int position = 0; position < n; position++) {
        cin >> up_step[position] >> down_step[position];
    }
    for (int i = 1; i <= k; i++) {
        int position, low, high;
        cin >> position >> low >> high;
        has_pipe[position] = 1;
        pipe_low[position] = low;
        pipe_high[position] = high;
    }

    minimum_clicks();
    return 0;
}
