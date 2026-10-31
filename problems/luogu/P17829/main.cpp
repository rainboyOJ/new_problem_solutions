/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 19:01
 */
// main.cpp：从高位到低位逐位贪心。
// 已经确定的位必须被选中的每个数都含有，再看当前位能不能也凑够 m 个数。
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

    int ans = 0;   // 已确定必须为 1 的位构成的掩码
    for (int b = 29; b >= 0; --b) {
        int want = ans | (1 << b);   // 假设第 b 位也取 1
        int cnt = 0;                 // 有多少个数同时含有 want 的全部位
        for (int i = 1; i <= n; ++i) {
            if ((a[i] & want) == want) ++cnt;
        }
        if (cnt >= m) ans = want;    // 够 m 个，第 b 位可以取 1
    }

    cout << ans << '\n';
    return 0;
}
