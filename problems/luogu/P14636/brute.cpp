// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MOD = 998244353;

int control_id, test_count;
int n, m;
long long a[MAXN];
int w[MAXN];

bool cmp_item(int x, int y) {
    long long left = a[x] * w[y];
    long long right = a[y] * w[x];
    if (left != right) {
        return left > right;
    }
    if (a[x] != a[y]) {
        return a[x] > a[y];
    }
    return x < y;
}

long long greedy_value() {
    vector<int> id;
    for (int i = 1; i <= n; i++) {
        id.push_back(i);
    }
    sort(id.begin(), id.end(), cmp_item);

    int money = m;
    long long sum = 0;
    for (int i = 0; i < (int)id.size(); i++) {
        int x = id[i];
        if (money >= w[x]) {
            money -= w[x];
            sum += a[x];
        }
    }
    return sum;
}

long long optimal_value() {
    vector<long long> dp(m + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int money = m; money >= w[i]; money--) {
            if (dp[money - w[i]] < 0) {
                continue;
            }
            dp[money] = max(dp[money], dp[money - w[i]] + a[i]);
        }
    }

    long long best = 0;
    for (int money = 0; money <= m; money++) {
        best = max(best, dp[money]);
    }
    return best;
}

void solve_one() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    int total = 1 << n;

    // 枚举每颗糖果定价为 1 或 2 元。
    for (int mask = 0; mask < total; mask++) {
        for (int i = 1; i <= n; i++) {
            if (mask & (1 << (i - 1))) {
                w[i] = 2;
            } else {
                w[i] = 1;
            }
        }

        if (greedy_value() == optimal_value()) {
            ans++;
        }
    }

    cout << ans % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> control_id >> test_count;
    while (test_count--) {
        solve_one();
    }

    return 0;
}
