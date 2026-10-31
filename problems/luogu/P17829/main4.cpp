/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 19:50
 * update_at: 2026-10-31 19:58
 */
// main4.cpp：值域可枚举时的解法，要求 max a_i < 2^20。
// 换成另一种看问题的角度：一个掩码 X 能被选出来，当且仅当至少有 m 个数包含 X 的全部位。
// 于是先把每个值的出现次数放进桶，再用超集和（SOS DP）求出
// super_cnt[X] = 包含 X 全部位的数的个数，最后取 super_cnt[X] >= m 的最大 X。
#include <bits/stdc++.h>
using namespace std;

const int BITS = 20;           // 本层要求 max a_i < 2^20
const int SIZE = 1 << BITS;    // 桶的大小 2^20，int 数组约占 4MB
int n, m;
int super_cnt[SIZE];           // super_cnt[X]：包含掩码 X 全部位的数的个数，初值是该值的出现次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        ++super_cnt[x];
    }

    // 超集和：按位逐个把「多含一位」的计数并进来
    for (int b = 0; b < BITS; ++b)
        for (int x = 0; x < SIZE; ++x)
            if (((x >> b) & 1) == 0) super_cnt[x] += super_cnt[x ^ (1 << b)];

    // 从大到小找第一个能被选出 m 个数的掩码
    for (int x = SIZE - 1; x >= 0; --x)
        if (super_cnt[x] >= m) {
            cout << x << '\n';
            return 0;
        }

    cout << 0 << '\n';   // 只有 m > n 才会走到这里，题面保证不会出现
    return 0;
}
