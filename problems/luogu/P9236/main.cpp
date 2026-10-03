/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:01
 * update_at: 2026-10-03 11:01
 */
// P9236 [蓝桥杯 2023 省 A] 异或和之和
// 正解：按位统计前缀异或的 0/1 个数。
// 第 k 位对答案的贡献 = 2^k * (该位上 c[0] * c[1])
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5 + 5;

int n;
int a[maxn];
int pre[maxn]; // pre[i] = a[1] ^ a[2] ^ ... ^ a[i]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 预异或：pre[0] = 0，pre[i] = pre[i-1] ^ a[i]
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ a[i];
    }

    ll ans = 0;
    // 逐位统计。A_i <= 2^20，再加上可能出现的进位，到 20 位足够；
    // 多算几位也不会错，这里写到 30 位纯粹为了保险。
    for (int k = 0; k <= 30; k++) {
        ll cnt[2] = {0, 0};
        // 统计前缀异或数组 pre[0..n] 中第 k 位为 0 / 1 的个数
        for (int i = 0; i <= n; i++) {
            cnt[(pre[i] >> k) & 1]++;
        }
        // 一 0 一 1 的下标对 (L-1, R) 恰好满足 pre[L-1] != pre[R]，
        // 也就是区间 [L, R] 的异或和第 k 位为 1，共 cnt[0] * cnt[1] 个区间
        ans += (1LL << k) * cnt[0] * cnt[1];
    }

    cout << ans << "\n";
    return 0;
}
