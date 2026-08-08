// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 998244353;
const int MAXN = 25;

int n, k;
i64 a[MAXN];
i64 label[MAXN];
i64 best_value;

// 计算当前一种分段方式的平方和。
i64 calc_value() {
    i64 total = 0;
    for (int i = 1; i <= n; i++) {
        i64 x = a[i] + label[i];
        total += x * x;
    }
    return total;
}

void dfs_assign(int pos, int limit_m) {
    if (pos > n) {
        i64 cur = calc_value();
        if (cur > best_value) best_value = cur;
        return;
    }

    // 空段允许存在，所以标签序列只要求不下降。
    for (int v = label[pos - 1]; v <= limit_m; v++) {
        label[pos] = v;
        dfs_assign(pos + 1, limit_m);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    i64 answer = 0;

    for (int m = 1; m <= k; m++) {
        best_value = -(1LL << 60);
        label[0] = 1;
        dfs_assign(1, m);
        answer += best_value % MOD;
        answer %= MOD;
    }

    cout << answer % MOD << '\n';
    return 0;
}
