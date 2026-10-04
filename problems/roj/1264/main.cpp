/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:27
 * update_at: 2026-10-05 07:27
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll h[MAXN];      // 每位同学的身高
ll rise[MAXN];   // rise[i]：以 i 结尾的最长严格上升子序列长度
ll fall[MAXN];   // fall[i]：从 i 开始的最长严格下降子序列长度

// 对数组 a[1..n] 求以每个位置结尾的最长严格上升子序列长度
void lis_strict(ll a[], ll dp[], ll n) {
    for (ll i = 1; i <= n; i++) {
        dp[i] = 1; // 至少包含自己
        for (ll j = 1; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
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
        cin >> h[i];
    }

    lis_strict(h, rise, n); // 正向求严格上升

    // 反转序列求“严格上升”，对应原序列的“严格下降”
    ll rev_h[MAXN];
    ll rev_dp[MAXN];
    for (ll i = 1; i <= n; i++) {
        rev_h[i] = h[n - i + 1];
    }
    lis_strict(rev_h, rev_dp, n);
    for (ll i = 1; i <= n; i++) {
        fall[i] = rev_dp[n - i + 1];
    }

    ll keep = 0; // 最多能保留的同学数
    for (ll i = 1; i <= n; i++) {
        ll total = rise[i] + fall[i] - 1; // 峰值被算了两次，减 1
        if (total > keep) {
            keep = total;
        }
    }

    cout << n - keep << "\n";
    return 0;
}
