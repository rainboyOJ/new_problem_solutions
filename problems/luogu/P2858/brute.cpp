#include <bits/stdc++.h>
using namespace std;

static int n;
static vector<long long> a;

long long dfs(int l, int r, int day) {
    if (l == r) {
        return a[l] * day;
    }

    // 暴力枚举今天卖左端还是右端。
    long long sell_left = a[l] * day + dfs(l + 1, r, day + 1);
    long long sell_right = a[r] * day + dfs(l, r - 1, day + 1);
    return max(sell_left, sell_right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    cout << dfs(1, n, 1) << '\n';
    return 0;
}
