#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;

    // 朴素枚举所有区间，统计 0 和 1 的数量。
    for (int l = 1; l <= n; l++) {
        int cnt0 = 0;
        int cnt1 = 0;
        for (int r = l; r <= n; r++) {
            if (a[r] == 0) {
                cnt0++;
            } else {
                cnt1++;
            }
            if (cnt0 == cnt1) {
                ans = max(ans, r - l + 1);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
