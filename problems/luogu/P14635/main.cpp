#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = (long long)4e18;

int n;
long long m;
long long x[MAXN], y[MAXN];
long long sx[MAXN];        // 排序后的 x
long long prefix_x[MAXN];  // 最小的若干个单颗成本之和
long long best_even[MAXN], best_odd[MAXN];
long long min_pair_cost;

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
}

void prepare() {
    min_pair_cost = INF;
    for (int i = 1; i <= n; i++) {
        sx[i] = x[i];
        min_pair_cost = min(min_pair_cost, x[i] + y[i]);
    }

    sort(sx + 1, sx + n + 1);
    for (int i = 1; i <= n; i++) {
        prefix_x[i] = prefix_x[i - 1] + sx[i];
    }

    best_even[0] = 0;
    best_odd[0] = INF;
    for (int i = 1; i <= n; i++) {
        best_even[i] = best_even[i - 1];
        best_odd[i] = best_odd[i - 1];

        if (i % 2 == 0) {
            long long value = prefix_x[i] - (long long)(i / 2) * min_pair_cost;
            best_even[i] = min(best_even[i], value);
        } else {
            long long value = prefix_x[i] - (long long)((i - 1) / 2) * min_pair_cost;
            best_odd[i] = min(best_odd[i], value);
        }
    }
}

// 判断是否能用不超过 m 的钱买到 need 颗糖果。
bool check(long long need) {
    int parity = (int)(need % 2);
    int limit = (int)min((long long)n, need);
    long long best_single_part = (parity == 0) ? best_even[limit] : best_odd[limit];

    if (best_single_part >= INF / 2) {
        return false;
    }

    __int128 pair_cnt = (need - parity) / 2;
    __int128 cost = pair_cnt * min_pair_cost + best_single_part;

    return cost <= m;
}

void solve() {
    long long left = 0;
    long long right = m;
    long long ans = 0;

    prepare();

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
