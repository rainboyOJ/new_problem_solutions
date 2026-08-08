#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int MAXK = 30;

int n, k;
int a[MAXN];
int pre[MAXN][MAXK + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            pre[i][j] = pre[i - 1][j];
        }
        for (int bit = 0; bit < k; bit++) {
            if ((a[i] >> bit) & 1) {
                pre[i][bit + 1]++;
            }
        }
    }

    int ans = 0;

    // 直接枚举所有区间，检查这段区间内 k 种特性的出现次数是否完全相同。
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int first_cnt = pre[r][1] - pre[l - 1][1];
            bool ok = true;

            for (int j = 2; j <= k; j++) {
                int now_cnt = pre[r][j] - pre[l - 1][j];
                if (now_cnt != first_cnt) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                ans = max(ans, r - l + 1);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
