#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;
const int MAXN = 50000 + 5;
const int MAXM = 1000 + 5;

int n, m;
int a[MAXN];
long long prefix_sum[MAXN];
int dp_prev[MAXN], dp_cur[MAXN];

bool check_limit(long long lim) {
    int seg_cnt = 1;
    long long cur_sum = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] > lim) {
            return false;
        }
        if (cur_sum + a[i] <= lim) {
            cur_sum += a[i];
        } else {
            seg_cnt++;
            cur_sum = a[i];
        }
    }
    return seg_cnt <= m + 1;
}

int count_ways(long long lim) {
    memset(dp_prev, 0, sizeof(int) * (n + 1));
    dp_prev[0] = 1;

    int ans = 0;
    for (int seg = 1; seg <= m + 1; seg++) {
        memset(dp_cur, 0, sizeof(int) * (n + 1));

        int left = 0;
        int window_sum = 0;
        for (int i = 1; i <= n; i++) {
            // 先把 t=i-1 加入窗口，表示最后一段只包含 a[i] 也是可能的。
            window_sum += dp_prev[i - 1];
            if (window_sum >= MOD) {
                window_sum -= MOD;
            }

            while (left < i && prefix_sum[i] - prefix_sum[left] > lim) {
                window_sum -= dp_prev[left];
                if (window_sum < 0) {
                    window_sum += MOD;
                }
                left++;
            }
            dp_cur[i] = window_sum;
        }

        ans += dp_cur[n];
        if (ans >= MOD) {
            ans -= MOD;
        }
        memcpy(dp_prev, dp_cur, sizeof(int) * (n + 1));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    long long left = 0, right = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        left = max(left, (long long)a[i]);
        right += a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    while (left < right) {
        long long mid = (left + right) >> 1;
        if (check_limit(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    int ways = count_ways(left);
    cout << left << ' ' << ways << '\n';
    return 0;
}
