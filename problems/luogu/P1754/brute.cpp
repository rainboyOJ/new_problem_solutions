#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 ans;

// 直接枚举整条排队序列。
// fifty_left: 还剩多少个拿 50 元的人没排
// hundred_left: 还剩多少个拿 100 元的人没排
// change_cnt: 当前售票员手里有多少张 50 元零钱
void dfs(int fifty_left, int hundred_left, int change_cnt) {
    if (fifty_left == 0 && hundred_left == 0) {
        ans++;
        return;
    }

    if (fifty_left > 0) {
        dfs(fifty_left - 1, hundred_left, change_cnt + 1);
    }

    if (hundred_left > 0 && change_cnt > 0) {
        dfs(fifty_left, hundred_left - 1, change_cnt - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(n, n, 0);
    cout << ans << '\n';

    return 0;
}
