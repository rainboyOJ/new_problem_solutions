// brute.cpp：小数据暴力解，枚举每个盒子最终剩多少颗糖。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
long long x;
long long a[MAXN], b[MAXN];
long long total_sum;
long long best_keep;
long long suffix_sum[MAXN];

void dfs(int pos, long long keep_sum) {
    if (keep_sum + suffix_sum[pos] <= best_keep) {
        return;
    }

    if (pos > n) {
        best_keep = max(best_keep, keep_sum);
        return;
    }

    // 暴力枚举第 pos 个盒子最终剩下多少颗糖。
    for (long long remain = 0; remain <= a[pos]; remain++) {
        if (pos > 1 && b[pos - 1] + remain > x) {
            continue;
        }
        b[pos] = remain;
        dfs(pos + 1, keep_sum + remain);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_sum += a[i];
    }
    for (int i = n; i >= 1; i--) {
        suffix_sum[i] = suffix_sum[i + 1] + a[i];
    }

    best_keep = -1;
    dfs(1, 0);

    cout << total_sum - best_keep << '\n';

    return 0;
}
