/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 19:50
 * update_at: 2026-11-02 09:20
 */
// main4.cpp：小值域解法，要求所有 a[i] < 2^20。
// 先统计每个值出现的次数，再用超集和统计包含各掩码的数的个数。
#include <bits/stdc++.h>
using namespace std;

const int BITS = 20;
const int SIZE = 1 << BITS;
int n, m;
// 初始存每个值的出现次数；DP 后存包含掩码 X 所有 1 位的数的个数。
int super_cnt[SIZE];  // 计数不超过 n，用 int；2^20 个桶约占 4 MB

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        ++super_cnt[x];
    }

    // 对第 b 位为 0 的掩码，合并“这一位为 1”时的计数。
    for (int b = 0; b < BITS; ++b) {
        for (int x = 0; x < SIZE; ++x) {
            if (((x >> b) & 1) == 0) {
                super_cnt[x] += super_cnt[x | (1 << b)];
            }
        }
    }

    // 至少有 m 个数包含 X 的所有 1 位，就能选出按位与包含 X 的 m 个数。
    for (int x = SIZE - 1; x >= 0; --x) {
        if (super_cnt[x] >= m) {
            cout << x << '\n';
            return 0;
        }
    }
    // 题目保证 m <= n，因此至少掩码 0 可行，一定会在循环内返回。
    return 0;
}
