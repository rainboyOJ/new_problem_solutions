/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:42
 * update_at: 2026-10-04 23:42
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const ll INF = 1000000000000000000LL;

ll n;
ll a[MAXN];         // a[i] 表示第 i 堆石子的数量
ll s[MAXN];         // s[i] = 前 i 堆石子的总数（前缀和），用于 O(1) 求区间和
ll dp[MAXN][MAXN];  // dp[l][r] 表示把第 l 到第 r 堆石子合并成一堆的最小得分

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
}

void solve() {
    // 按区间长度从小到大递推，计算 dp[l][r] 时它依赖的子区间都已经算好。
    // 长度为 1 的区间不需要合并，dp[l][l] 由全局数组默认为 0。
    for (ll len = 2; len <= n; len++) {
        for (ll l = 1; l + len - 1 <= n; l++) {
            ll r = l + len - 1;
            dp[l][r] = INF;
            // 枚举最后一次合并的分割点 k，把区间 [l, r] 分成 [l, k] 与 [k+1, r] 两堆。
            for (ll k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
            // 最后一次合并的得分就是整个区间的石子总数。
            dp[l][r] += s[r] - s[l - 1];
        }
    }
    cout << dp[1][n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
