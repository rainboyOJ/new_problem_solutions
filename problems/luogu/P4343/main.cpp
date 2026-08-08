#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 100000 + 5;

int l;
int target_k;
i64 a[MAXN];

int count_ac(i64 need) {
    i64 cur = 0;
    int cnt = 0;

    for (int i = 1; i <= l; i++) {
        cur += a[i];
        if (cur < 0) cur = 0;

        if (cur >= need) {
            cnt++;
            cur = 0;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> target_k;
    i64 max_prefix = 0;
    i64 cur = 0;
    for (int i = 1; i <= l; i++) {
        cin >> a[i];
        cur += a[i];
        if (cur < 0) cur = 0;
        if (cur > max_prefix) max_prefix = cur;
    }

    // 找最小的 n，使 count_ac(n) <= k。
    i64 left = 1, right = max_prefix + 1;
    while (left < right) {
        i64 mid = (left + right) >> 1;
        if (count_ac(mid) <= target_k) right = mid;
        else left = mid + 1;
    }
    i64 min_n = left;

    if (count_ac(min_n) != target_k) {
        cout << -1 << '\n';
        return 0;
    }

    // 找最大的 n，使 count_ac(n) >= k。
    left = 1, right = max_prefix + 1;
    while (left < right) {
        i64 mid = (left + right + 1) >> 1;
        if (count_ac(mid) >= target_k) left = mid;
        else right = mid - 1;
    }
    i64 max_n = left;

    cout << min_n << ' ' << max_n << '\n';
    return 0;
}
