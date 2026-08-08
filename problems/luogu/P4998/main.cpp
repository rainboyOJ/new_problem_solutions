#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 1000000 + 5;
const int MAXA = 1000000;

int n, k;
int a[MAXN];
int freq[MAXA + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }

    sort(a + 1, a + n + 1);

    int left_mid = a[(n + 1) / 2];
    int right_mid = a[(n + 2) / 2];

    // 中位数区间内的所有整数位置，总代价都相同。
    i64 min_cost = 0;
    for (int i = 1; i <= n; i++) {
        min_cost += llabs((i64)a[i] - left_mid);
    }

    i64 interval_len = (i64)right_mid - left_mid + 1;
    if (k <= interval_len) {
        cout << min_cost * k << '\n';
        return 0;
    }

    i64 answer = min_cost * interval_len;
    int need = k - (int)interval_len;

    // 左侧代价序列：f(left_mid - 1), f(left_mid - 2), ...
    // 右侧代价序列：f(right_mid + 1), f(right_mid + 2), ...
    // 这两条序列都是单调不降的，直接归并取前 need 小即可。

    int x_left = left_mid;
    int cnt_less = lower_bound(a + 1, a + n + 1, left_mid) - (a + 1); // 严格小于 left_mid 的个数
    i64 cost_left = min_cost;

    int x_right = right_mid;
    int cnt_le = upper_bound(a + 1, a + n + 1, right_mid) - (a + 1); // 小于等于 right_mid 的个数
    i64 cost_right = min_cost;

    while (need--) {
        // 向左走一步：f(x-1) - f(x) = n - 2 * count(a_i < x)
        i64 next_left = cost_left + (i64)n - 2LL * cnt_less;

        // 向右走一步：f(x+1) - f(x) = 2 * count(a_i <= x) - n
        i64 next_right = cost_right + 2LL * cnt_le - n;

        if (next_left <= next_right) {
            answer += next_left;
            cost_left = next_left;
            x_left--;

            if (x_left >= 0) {
                cnt_less -= freq[x_left];
            }
        } else {
            answer += next_right;
            cost_right = next_right;
            x_right++;

            if (x_right <= MAXA) {
                cnt_le += freq[x_right];
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
