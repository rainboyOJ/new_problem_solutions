#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans_l = 1;
    int ans_r = n;

    // 朴素枚举所有区间，检查是否覆盖了所有画家。
    for (int l = 1; l <= n; l++) {
        vector<int> cnt(m + 1, 0);
        int kind = 0;
        for (int r = l; r <= n; r++) {
            if (cnt[a[r]] == 0) {
                kind++;
            }
            cnt[a[r]]++;

            if (kind == m) {
                if (r - l < ans_r - ans_l) {
                    ans_l = l;
                    ans_r = r;
                }
                break;
            }
        }
    }

    cout << ans_l << ' ' << ans_r << '\n';
    return 0;
}
