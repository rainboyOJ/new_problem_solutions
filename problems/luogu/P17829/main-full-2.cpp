/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 09:20
 */
// main-full-2.cpp：正解的另一种写法——直接维护必修掩码 ans，不开桶。
// ans 就是"已经确定必须为 1 的位"，它本身也是答案，不需要额外的状态。
// 判第 b 位时试探 want = ans | (1 << b)，数一数有多少个数含 want 的全部位；
// 够 m 个就把 ans 换成 want，否则这一位放弃。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, m;
int a[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int ans = 0;                    // 已确定必须为 1 的位构成的掩码，同时也是最终答案
    for (int b = 29; b >= 0; --b) { // b: 29 -> 0，从高位到低位
        // 注意: want (111000) 表示面的都有选, 第b位也取1
        int want = ans | (1 << b); // 假设第 b 位也取 1
        int cnt = 0;               // 有多少个数同时含 want 的全部位
        for (int i = 1; i <= n; ++i) {
            if ((a[i] & want) == want) ++cnt;
        }
        if (cnt >= m) ans = want; // 够 m 个，第 b 位可以取 1
    }

    cout << ans << '\n';
    return 0;
}
