#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    long long max_sum = 0;
    for (int i = 1; i <= n; i++) {
        max_sum += a[i] * b[i];
    }

    // 暴力枚举所有可能的反转区间 [l, r]
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            long long cur = 0;
            for (int i = 1; i < l; i++) cur += a[i] * b[i];
            for (int i = l; i <= r; i++) cur += a[r - (i - l)] * b[i];
            for (int i = r + 1; i <= n; i++) cur += a[i] * b[i];
            max_sum = max(max_sum, cur);
        }
    }

    cout << max_sum << "\n";
    return 0;
}
