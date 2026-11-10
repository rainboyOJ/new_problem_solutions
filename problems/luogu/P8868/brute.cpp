/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:57
 * update_at: 2026-11-11 00:57
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using u64 = unsigned long long;

// 暴力版本：对每个询问区间暴力两重循环枚举 [p, q]
int tid, n, q_cnt;
int a[505], b[505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> tid >> n)) return 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    cin >> q_cnt;
    while (q_cnt--) {
        int l, r;
        cin >> l >> r;

        u64 total_sum = 0;
        for (int p = l; p <= r; ++p) {
            int max_a = 0;
            int max_b = 0;
            for (int q = p; q <= r; ++q) {
                max_a = max(max_a, a[q]);
                max_b = max(max_b, b[q]);
                total_sum += 1ULL * max_a * max_b;
            }
        }
        cout << total_sum << "\n";
    }

    return 0;
}
