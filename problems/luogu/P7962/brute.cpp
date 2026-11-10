/**
 * Problem: luogu P7962 - [NOIP2021] 方差 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-10 23:15
 * Description: 全排列枚举差分重排计算最小方差
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using ll = long long;

const ll INF = 1e18;

int n;
int a[20];
int d[20];
int cur_a[20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int diff_cnt = n - 1;
    for (int i = 1; i <= diff_cnt; ++i) {
        d[i] = a[i + 1] - a[i];
    }
    sort(d + 1, d + diff_cnt + 1);

    ll ans = INF;

    do {
        cur_a[1] = a[1];
        ll sum = cur_a[1];
        ll sq_sum = static_cast<ll>(cur_a[1]) * cur_a[1];

        for (int i = 1; i <= diff_cnt; ++i) {
            cur_a[i + 1] = cur_a[i] + d[i];
            sum += cur_a[i + 1];
            sq_sum += static_cast<ll>(cur_a[i + 1]) * cur_a[i + 1];
        }

        ll cur_var = static_cast<ll>(n) * sq_sum - sum * sum;
        if (cur_var < ans) {
            ans = cur_var;
        }
    } while (next_permutation(d + 1, d + diff_cnt + 1));

    cout << ans << "\n";

    return 0;
}
