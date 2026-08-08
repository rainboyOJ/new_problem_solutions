#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 memo[25][25];
bool vis[25][25];

// dfs(fifty_left, hundred_left) 表示：
// 还剩多少个拿 50 元的人、多少个拿 100 元的人没有排到时，
// 后面还能形成多少种合法排队方案。
i64 dfs(int fifty_left, int hundred_left) {
    if (fifty_left == 0 || hundred_left == 0) {
        return 1;
    }

    if (vis[fifty_left][hundred_left]) {
        return memo[fifty_left][hundred_left];
    }
    vis[fifty_left][hundred_left] = true;

    i64 ans = 0;

    // 安排一个拿 50 元的人，不需要找零。
    ans += dfs(fifty_left - 1, hundred_left);

    // 当前零钱数 = 已出现的 50 元人数 - 已出现的 100 元人数
    // = (n - fifty_left) - (n - hundred_left)
    // = hundred_left - fifty_left
    if (hundred_left > fifty_left) {
        ans += dfs(fifty_left, hundred_left - 1);
    }

    memo[fifty_left][hundred_left] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << dfs(n, n) << '\n';

    return 0;
}
