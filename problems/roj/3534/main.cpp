/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:28
 * update_at: 2026-10-06 13:28
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll h[MAXN];      // 身高序列
ll up[MAXN];     // 以 i 结尾的最长严格上升子序列长度
ll down[MAXN];   // 以 i 开头的最长严格下降子序列长度

// 计算以每个位置结尾的最长严格上升子序列长度
void lis_ends(ll a[], ll dp[], int n) {
    for (int i = 1; i <= n; i++) {
        dp[i] = 1; // 至少包含自己
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    lis_ends(h, up, n); // 正向：以 i 结尾的严格上升

    // 反向求下降：把序列反转后求以每个位置结尾的上升，再反转回来
    ll rev_h[MAXN], rev_dp[MAXN];
    for (int i = 1; i <= n; i++) {
        rev_h[i] = h[n - i + 1];
    }
    lis_ends(rev_h, rev_dp, n);
    for (int i = 1; i <= n; i++) {
        down[i] = rev_dp[n - i + 1];
    }

    ll best = 0;
    for (int i = 1; i <= n; i++) {
        best = max(best, up[i] + down[i] - 1);
    }
    cout << n - best << "\n";
    return 0;
}
