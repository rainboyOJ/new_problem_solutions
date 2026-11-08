/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-07 11:21
 * update_at: 2026-11-07 11:21
 */
// 正解 O(n log n)：DP + 前缀和分组
//
// f[i] = 前 i 个元素分成若干段、每段和均不等于 K 的方案数, f[0]=1
// f[i] = Σ_{0<=j<i} f[j]  -  Σ_{0<=j<i, pre[j] = pre[i]-K} f[j]
//
// 维护:
//   S      = Σ_{j < i} f[j]                (滚动前缀和)
//   bad[x] = Σ_{j < i, pre[j] = x} f[j]    (按前缀和分组累加)
//
// 注意 bad 中只包含 j <= i-1 的项, 所以 j = i 自身永远不会被误减,
// 即使 K = 0 (此时 pre[i]-K == pre[i]) 也无需特判。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;

int n;
ll K;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> K;

    map<ll, int> bad;           // 前缀和 -> Σf[j]
    bad[0] = 1;                 // pre[0] = 0, 贡献 f[0] = 1

    ll pre = 0;                 // pre[i] 滚动
    ll S = 1;                   // S(i-1), 初始 i=1: 只有 f[0]=1

    int f = 0;
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        pre += x;               // 现在 pre = pre[i]

        auto it = bad.find(pre - K);
        f = (int)((S - (it == bad.end() ? 0 : it->second)) % mod + mod) % mod;

        S = (S + f) % mod;      // 把 f[i] 并入 S, 供 i+1 用
        bad[pre] = (int)((bad[pre] + (ll)f) % mod);  // 把 f[i] 挂到 pre[i] 上
    }

    cout << f % mod << "\n";
    return 0;
}
