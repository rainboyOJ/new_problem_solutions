#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

struct Stick {
    int l, w;
};

int n;
Stick a[MAXN];
int dp[MAXN]; // dp[i]：以第 i 根木棍结尾的最长严格上升子序列长度

bool cmp_stick(const Stick &x, const Stick &y) {
    if (x.l != y.l) {
        return x.l > y.l;
    }
    return x.w > y.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].w;
    }

    sort(a + 1, a + n + 1, cmp_stick);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            // 长度已经按降序排好，只需要再要求宽度也严格上升。
            if (a[j].w < a[i].w) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
