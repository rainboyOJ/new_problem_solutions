#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 2005;

int n, m;
int a[MAXN];
int cnt[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int kind = 0;      // 当前窗口里已经包含了多少种画家
    int l = 1;
    int ans_l = 1;
    int ans_r = n;

    for (int r = 1; r <= n; r++) {
        if (cnt[a[r]] == 0) {
            kind++;
        }
        cnt[a[r]]++;

        while (kind == m) {
            if (r - l < ans_r - ans_l) {
                ans_l = l;
                ans_r = r;
            }

            cnt[a[l]]--;
            if (cnt[a[l]] == 0) {
                kind--;
            }
            l++;
        }
    }

    cout << ans_l << ' ' << ans_r << '\n';
    return 0;
}
