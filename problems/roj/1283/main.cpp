/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:50
 * update_at: 2026-10-05 07:50
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll a[MAXN];     // 按游览顺序给出的景点海拔
ll up[MAXN];    // up[i]：以 i 结尾的最长严格上升子序列长度
ll down[MAXN];  // down[i]：从 i 开始向右的最长严格下降子序列长度

// 对序列 b[1..n] 求以每个位置结尾的最长严格上升子序列长度
void lis_strict(ll b[], ll dp[], ll n) {
    for (ll i = 1; i <= n; i++) {
        dp[i] = 1; // 至少包含自己
        for (ll j = 1; j < i; j++) {
            if (b[j] < b[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    lis_strict(a, up, n); // 正向：以 i 结尾的最长严格上升段

    // 反转海拔后「向右严格下降」变成「向右严格上升」，复用同一份 LIS
    ll rev[MAXN];    // 反转后的海拔
    ll rev_dp[MAXN]; // 反转序列上每个位置结尾的最长严格上升长度
    for (ll i = 1; i <= n; i++) {
        rev[i] = a[n - i + 1];
    }
    lis_strict(rev, rev_dp, n);
    for (ll i = 1; i <= n; i++) {
        down[i] = rev_dp[n - i + 1];
    }

    ll ans = 0; // 最多能浏览的景点数
    for (ll i = 1; i <= n; i++) {
        ll total = up[i] + down[i] - 1; // 峰顶被两侧各数了一次，减 1
        if (total > ans) {
            ans = total;
        }
    }

    cout << ans << "\n";
    return 0;
}
