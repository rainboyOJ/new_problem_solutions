/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 10:27
 * update_at: 2026-11-13 10:27
 */
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    long long c;
    if (!(cin >> n >> c)) return;

    vector<long long> s(n);
    long long cnt_odd = 0;
    long long cnt_even = 0;

    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        if (s[i] % 2 != 0) {
            cnt_odd++;
        } else {
            cnt_even++;
        }
    }

    // 1. 全集数对数量：0 <= x <= y <= c，共有 (c + 1) * (c + 2) / 2
    __int128 tot = (__int128)(c + 1) * (c + 2) / 2;

    // 2. 集合 A 大小：x + y = u in S
    // 0 <= x <= y => x <= u / 2，x 的取值范围为 [0, u / 2]，共有 u / 2 + 1 种
    __int128 size_a = 0;
    for (int i = 0; i < n; ++i) {
        size_a += (s[i] / 2 + 1);
    }

    // 3. 集合 B 大小：y - x = v in S
    // y = x + v <= c => x <= c - v，x 的取值范围为 [0, c - v]，共有 c - v + 1 种
    __int128 size_b = 0;
    for (int i = 0; i < n; ++i) {
        size_b += (c - s[i] + 1);
    }

    // 4. 交集 A cap B 大小：x + y = u in S 且 y - x = v in S
    // 解方程：x = (u - v) / 2, y = (u + v) / 2
    // 产生整数解的充要条件是：u >= v 且 u 与 v 同奇偶
    __int128 size_ab = (__int128)cnt_odd * (cnt_odd + 1) / 2 + (__int128)cnt_even * (cnt_even + 1) / 2;

    // 5. 容斥原理求合法数对：ans = tot - |A| - |B| + |A cap B|
    __int128 ans = tot - size_a - size_b + size_ab;

    cout << (long long)ans << "\n";
}

int main() {
    // 提升标准流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
