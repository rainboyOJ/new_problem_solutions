#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力枚举每一步是爬还是跳，只适合小数据对拍。

const int MAXN = 25;
const long long INF = (1LL << 60);

int n;
int h[MAXN];

// dfs(pos, tired)
// pos   : 当前所在楼层
// tired : 1 表示刚跳过，下一步不能继续跳；0 表示当前可以跳
long long dfs(int pos, int tired) {
    if (pos == n) {
        return 0;
    }

    long long ans = INF;

    // 爬到下一层一定是合法的，爬完后就恢复成可跳状态。
    ans = min(ans, (long long)h[pos + 1] + dfs(pos + 1, 0));

    // 只有当前不疲惫时，才允许继续施法跳跃。
    if (tired == 0) {
        ans = min(ans, dfs(pos + 1, 1));
        if (pos + 2 <= n) {
            ans = min(ans, dfs(pos + 2, 1));
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    cout << dfs(0, 0) << '\n';
    return 0;
}
