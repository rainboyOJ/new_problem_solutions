#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 一层一层地削去所有正高度连续段，每削一层连续段就对应一次操作。
const int MAXN = 100000 + 5;

int n;
int h[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    long long ans = 0;
    while (true) {
        bool has_positive = false;
        int i = 1;

        while (i <= n) {
            while (i <= n && h[i] == 0) {
                i++;
            }
            if (i > n) {
                break;
            }

            has_positive = true;
            ans++;

            while (i <= n && h[i] > 0) {
                h[i]--;
                i++;
            }
        }

        if (!has_positive) {
            break;
        }
    }

    cout << ans << '\n';
    return 0;
}
