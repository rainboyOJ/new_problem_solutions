/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-24 17:47
 * update_at: 2026-07-24 17:53
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
const int MAXN = 20;

int n, m, k;
int up_step[MAXN], down_step[MAXN];
int has_pipe[MAXN], pipe_low[MAXN], pipe_high[MAXN];
int best_clicks = INF;
int most_passed = 0;

void search_paths(int position, int height, int clicks, int passed_pipes) {
    most_passed = max(most_passed, passed_pipes);
    if (position == n) {
        best_clicks = min(best_clicks, clicks);
        return;
    }

    int rise = up_step[position];
    // 枚举这一步点击 1 次、2 次……，直到高度达到 m。
    // 到达 m 后再点击一次仍会停在 m，这也是一次合法的时间转移。
    int target = height;
    for (int count = 1;; count++) {
        target = min(m, target + rise);
        int next_position = position + 1;
        if (!has_pipe[next_position]
            || (target > pipe_low[next_position] && target < pipe_high[next_position])) {
            search_paths(next_position, target, clicks + count, passed_pipes + has_pipe[next_position]);
        }
        if (target == m) {
            break;
        }
    }

    // 枚举这一步不点击的情况。
    target = height - down_step[position];
    if (target > 0) {
        int next_position = position + 1;
        if (!has_pipe[next_position]
            || (target > pipe_low[next_position] && target < pipe_high[next_position])) {
            search_paths(next_position, target, clicks, passed_pipes + has_pipe[next_position]);
        }
    }
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

    // 小数据从每个合法初始高度出发，完整枚举每一步的点击次数。
    for (int height = 1; height <= m; height++) {
        search_paths(0, height, 0, 0);
    }

    if (best_clicks < INF) {
        cout << 1 << '\n' << best_clicks << '\n';
    } else {
        cout << 0 << '\n' << most_passed << '\n';
    }
    return 0;
}
