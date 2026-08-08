#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = (int)s.size();
    int ans = 0;

    // 朴素枚举所有区间，统计其中 G 和 R 的数量。
    for (int l = 0; l < n; l++) {
        int cnt_g = 0;
        int cnt_r = 0;
        for (int r = l; r < n; r++) {
            if (s[r] == 'G') {
                cnt_g++;
            } else {
                cnt_r++;
            }
            if (cnt_g == cnt_r) {
                ans = max(ans, r - l + 1);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
