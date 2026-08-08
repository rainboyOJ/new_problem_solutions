#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 ans;

// 直接枚举 push / pop 操作序列。
// pushed: 已经入栈了多少个数
// in_stack: 当前栈里有多少个数
void dfs(int pushed, int in_stack) {
    if (pushed == n && in_stack == 0) {
        ans++;
        return;
    }

    if (pushed < n) {
        dfs(pushed + 1, in_stack + 1);
    }

    if (in_stack > 0) {
        dfs(pushed, in_stack - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(0, 0);
    cout << ans << '\n';

    return 0;
}
