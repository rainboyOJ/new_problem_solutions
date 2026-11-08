/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-07 11:21
 * update_at: 2026-11-07 11:21
 */
// main2.cpp：DP O(n^2) 解法（正解的过渡形态，可对拍）
//   f[i] = 把前 i 个元素划分成若干段、且每段和都不等于 K 的方案数
//   f[0] = 1
//   f[i] = sum_{0 <= j < i, sum(j+1..i) != K} f[j]
// 答案 f[n]
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
const int mod = 998244353;

int n;
ll K;
ll a[maxn];
ll pre[maxn];   // 前缀和 pre[i] = a[1] + ... + a[i]
ll f[maxn];

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);

    cin >> n >> K;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];

    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        ll sum = 0;
        for (int j = 0; j < i; ++j) {          // 枚举最后一段 (j+1 .. i)
            ll seg = pre[i] - pre[j];          // 该段和
            if (seg == K) continue;            // 这一段不合法，跳过
            sum += f[j];
        }
        f[i] = sum % mod;
    }

    cout << f[n] % mod << "\n";
    return 0;
}
