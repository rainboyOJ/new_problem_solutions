// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, q;
long long a[MAXN], prefix_sum[MAXN];

long long range_sum(int l, int r) {
    return prefix_sum[r] - prefix_sum[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;

        unsigned long long result = 0;
        for (int i = 1; i <= n; i++) {
            long long best = -(1LL << 60);
            for (int l = 1; l <= i; l++) {
                for (int r = i; r <= n; r++) {
                    int len = r - l + 1;
                    if (L <= len && len <= R) {
                        best = max(best, range_sum(l, r));
                    }
                }
            }
            long long product = best * (long long)i;
            result ^= (unsigned long long)product;
        }

        cout << result << '\n';
    }

    return 0;
}
