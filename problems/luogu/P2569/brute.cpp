#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = -(1LL << 60);

int T, MaxP, W;
int ap[25], bp[25], as[25], bs[25];
// memo[day][hold][wait]：
// 从第 day 天开始，当前持有 hold 股，还要再等 wait 天才能继续交易时，
// 从现在到最后一天能够得到的最大额外收益。
long long memo[25][25][25];
int vis[25][25][25];

long long dfs(int day, int hold, int wait) {
    if (day > T) {
        return 0;
    }
    if (vis[day][hold][wait]) {
        return memo[day][hold][wait];
    }
    vis[day][hold][wait] = 1;

    int next_wait = wait;
    if (next_wait > 0) {
        next_wait--;
    }

    // 今天不交易。
    long long best = dfs(day + 1, hold, next_wait);

    if (wait == 0) {
        // 今天买一些股票。
        int max_buy = min(as[day], MaxP - hold);
        for (int x = 1; x <= max_buy; x++) {
            best = max(best, dfs(day + 1, hold + x, W) - 1LL * x * ap[day]);
        }

        // 今天卖一些股票。
        int max_sell = min(bs[day], hold);
        for (int x = 1; x <= max_sell; x++) {
            best = max(best, dfs(day + 1, hold - x, W) + 1LL * x * bp[day]);
        }
    }

    memo[day][hold][wait] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据记忆化搜索。
    // 直接枚举每天买多少、卖多少，或者什么都不做，用来帮助理解题意并辅助对拍。
    cin >> T >> MaxP >> W;
    for (int i = 1; i <= T; i++) {
        cin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    }

    memset(vis, 0, sizeof(vis));
    cout << dfs(1, 0, 0) << '\n';
    return 0;
}
