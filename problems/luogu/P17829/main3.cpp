/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 19:50
 * update_at: 2026-10-31 19:50
 */
// main3.cpp：只对特殊性质 A 成立（所有 a_i 都是 2^k - 1 的形状）。
// 这种数末尾是一串连续的 1，两个这样的数按位与等于较小的那个，
// 所以选出 m 个数后的答案就是这 m 个数里的最小值，取最大的 m 个数即可。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, m;
int a[maxn];  // a_i < 2^30，int 足够

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // 升序排序后，第 m 大的数就在下标 n - m + 1 上
    sort(a + 1, a + n + 1);
    cout << a[n - m + 1] << '\n';
    return 0;
}
