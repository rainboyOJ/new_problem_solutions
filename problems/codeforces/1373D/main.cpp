/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 10:50
 * update_at: 2026-11-04 15:40
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 5;

ll n;
ll a[MAXN]; // 原数组，下标 0 到 n - 1

// 最大子段和 dp（允许空段，返回 >= 0）
// dp[i] = 以 b[i] 结尾的最大子段和
ll max_subarray(vector<ll> &b) {
    ll best = 0;
    ll dp = 0;
    for (ll i = 0; i < (ll)b.size(); ++i) {
        dp = max(b[i], dp + b[i]);
        best = max(best, dp);
    }
    return best;
}

// 求解单个测试用例
void solve() {
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 初始状态下所有偶数位置的元素之和
    ll tot = 0;
    for (ll i = 0; i < n; i += 2) {
        tot += a[i];
    }

    // dif[i]：第 i 位对"偶数位和"的贡献变化
    //   i 为奇数（反转后会移到偶数位）：+a[i]
    //   i 为偶数（反转后会被挤走）    ：-a[i]
    // 于是反转偶数长度区间 [l, r] 的收益 = 区间奇数位之和 - 偶数位之和
    //                                   = dif 上的一段子段和
    vector<ll> dif(n);
    for (ll i = 0; i < n; ++i) {
        dif[i] = (i & 1) ? a[i] : -a[i];
    }

    // 反转长度必须是偶数 ⇒ l 与 r 奇偶性相反 ⇒ 区间由连续的"相邻两元素"配对构成
    // 每一对的收益都是 dif[i] + dif[i-1]，也就是 a[i] - a[i-1]（奇数位 - 偶数位）
    // 两种情况只是"右端点 r 的奇偶性"不同：

    // b1：右端点 r 为偶数下标 → 配对 (1,2), (3,4), (5,6)...
    vector<ll> b1;
    for (ll i = 2; i < n; i += 2) {
        b1.push_back(dif[i] + dif[i - 1]);
    }

    // b2：右端点 r 为奇数下标 → 配对 (0,1), (2,3), (4,5)...
    vector<ll> b2;
    for (ll i = 1; i < n; i += 2) {
        b2.push_back(dif[i] + dif[i - 1]);
    }

    // 反转区间必须是若干连续配对，收益就是 b 上的一个连续子段和
    ll max_gain = max(max_subarray(b1), max_subarray(b2));

    cout << tot + max_gain << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
