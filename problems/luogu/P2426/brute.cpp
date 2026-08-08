#include <bits/stdc++.h>
using namespace std;

static vector<int> a;

long long score(int l, int r) {
    if (l == r) {
        return a[l];
    }
    return 1LL * abs(a[l] - a[r]) * (r - l + 1);
}

long long dfs(int l, int r) {
    if (l > r) {
        return 0;
    }

    long long best = 0;

    // 枚举这一步从左端删掉 [l, k]
    for (int k = l; k <= r; ++k) {
        best = max(best, score(l, k) + dfs(k + 1, r));
    }

    // 枚举这一步从右端删掉 [k, r]
    for (int k = l; k <= r; ++k) {
        best = max(best, dfs(l, k - 1) + score(k, r));
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    cout << dfs(1, n) << '\n';
    return 0;
}
