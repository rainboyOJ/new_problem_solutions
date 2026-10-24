/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * P1220 关路灯：区间 DP，O(n^2)
 * 状态：f[l][r][0/1] = 已关掉 [l,r] 内所有灯，站在 l 端(0) / r 端(1) 时的最小耗电。
 * 前提：路过某盏灯时顺手关掉一定不亏，所以已关灯永远是包含 c 的连续区间。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 55;
int n, c;
ll pos_[maxn];   // 灯的位置
ll w[maxn];      // 灯的功率
ll pre[maxn];    // 功率前缀和
ll f[maxn][maxn][2]; // 0: 在左端, 1: 在右端

// [a,b] 外的灯的总功率（这些灯还亮着，走路时每秒烧这么多）
ll Wout(int a, int b) {
    return pre[n] - (pre[b] - pre[a-1]);
}

void read_data() {
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) {
        cin >> pos_[i] >> w[i];
        pre[i] = pre[i-1] + w[i];
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();

    const ll INF = 0x3f3f3f3f3f3f3f3fLL;
    memset(f, 0x3f, sizeof(f));
    f[c][c][0] = 0;
    f[c][c][1] = 0;

    // 按区间长度从小到大
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            if (c < l || c > r) continue; // 必须包含起点 c

            // 从 [l+1, r] 走到 l
            ll t = pos_[l+1] - pos_[l];
            f[l][r][0] = min(f[l+1][r][0] + t * Wout(l+1, r),
                             f[l+1][r][1] + (pos_[r] - pos_[l]) * Wout(l+1, r));

            // 从 [l, r-1] 走到 r
            t = pos_[r] - pos_[r-1];
            f[l][r][1] = min(f[l][r-1][1] + t * Wout(l, r-1),
                             f[l][r-1][0] + (pos_[r] - pos_[l]) * Wout(l, r-1));
        }
    }

    cout << min(f[1][n][0], f[1][n][1]) << "\n";
    return 0;
}
