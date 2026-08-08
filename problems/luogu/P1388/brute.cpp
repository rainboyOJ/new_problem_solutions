#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，递归枚举最后一次运算和左右乘号数量。

const int MAXN = 20;

int n, k;
int a[MAXN];
int sum[MAXN];

int range_sum(int l, int r) {
    return sum[r] - sum[l - 1];
}

long long solve(int l, int r, int t) {
    if (t < 0 || t > r - l) {
        return -1;
    }
    if (t == 0) {
        return range_sum(l, r);
    }

    long long best = -1;

    for (int mid = l; mid < r; mid++) {
        int left_len = mid - l + 1;
        int right_len = r - mid;

        // 最后一次运算是加号：左右乘号数量之和为 t。
        for (int x = 0; x <= t; x++) {
            int y = t - x;
            if (x >= left_len || y >= right_len) {
                continue;
            }
            long long left_value = solve(l, mid, x);
            long long right_value = solve(mid + 1, r, y);
            if (left_value == -1 || right_value == -1) {
                continue;
            }
            best = max(best, left_value + right_value);
        }

        // 最后一次运算是乘号：当前这个乘号占 1 个。
        for (int x = 0; x <= t - 1; x++) {
            int y = t - 1 - x;
            if (x >= left_len || y >= right_len) {
                continue;
            }
            long long left_value = solve(l, mid, x);
            long long right_value = solve(mid + 1, r, y);
            if (left_value == -1 || right_value == -1) {
                continue;
            }
            best = max(best, left_value * right_value);
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    cout << solve(1, n, k) << '\n';
    return 0;
}
