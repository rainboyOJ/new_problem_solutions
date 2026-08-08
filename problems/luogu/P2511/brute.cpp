#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

int n, m;
int a[25];
long long best_limit;
int ans;

void evaluate_mask(int mask) {
    int cut_cnt = 0;
    long long cur_sum = 0;
    long long max_seg = 0;

    for (int i = 1; i <= n; i++) {
        cur_sum += a[i];
        if (i == n || (mask & (1 << (i - 1)))) {
            max_seg = max(max_seg, cur_sum);
            cur_sum = 0;
            if (i != n) {
                cut_cnt++;
            }
        }
    }

    if (cut_cnt > m) {
        return;
    }
    if (max_seg < best_limit) {
        best_limit = max_seg;
        ans = 1;
    } else if (max_seg == best_limit) {
        ans++;
        if (ans >= MOD) {
            ans -= MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举所有切割方案，直接算每种方案的最大段长。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    best_limit = (1LL << 60);
    ans = 0;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        evaluate_mask(mask);
    }

    cout << best_limit << ' ' << ans << '\n';
    return 0;
}
