#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 memo[25][25];
bool vis[25][25];

// in_left: 还有多少个数没入栈
// in_stack: 当前栈里有多少个数
i64 dfs(int in_left, int in_stack) {
    if (in_left == 0) {
        return 1;
    }

    if (vis[in_left][in_stack]) {
        return memo[in_left][in_stack];
    }
    vis[in_left][in_stack] = true;

    i64 ans = 0;

    // 继续入栈一个数
    ans += dfs(in_left - 1, in_stack + 1);

    // 如果栈非空，还可以出栈一个数
    if (in_stack > 0) {
        ans += dfs(in_left, in_stack - 1);
    }

    memo[in_left][in_stack] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << dfs(n, 0) << '\n';

    return 0;
}
