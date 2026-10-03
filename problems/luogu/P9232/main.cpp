/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:40
 * update_at: 2026-10-03 10:40
 */
// P9232 [蓝桥杯 2023 省 A] 更小的数
// 记 f(l, r) = 「把子串 s[l..r] 反转后，新数字是否严格小于原数字」。
// 反转只改动 [l, r] 这一段，所以新串与原串的比较结果由**第一处不同**决定。
// 按位置从外向内看，第一处不同只能出现在三段之一：
//   1. 位置 l：新串是 s[r]，原串是 s[l]；
//   2. 位置 r：新串是 s[l]，原串是 s[r]；
//   3. 严格夹在中间的 s[l+1..r-1]。
// 情形 1 和 3 是互斥的，于是得到转移：
//   若 s[l] != s[r]：第一处不同就在位置 l，f(l, r) = [s[l] > s[r]]；
//   若 s[l] == s[r]：位置 l、r 都相同，只能看中间，f(l, r) = f(l+1, r-1)。
// 当 r - l + 1 = 2 或 3 时中间为空串或单字符，反转后与原串完全相同，
// 这两个区间的 f 恒为 0（正好是 s[l]==s[r] 分支的边界）。
//
// 实现：按右端点 r 从小到大推进。f(l, r) 在两端相等时需要 f(l+1, r-1)，
// 那是「右端点为 r-1」的上一轮结果，因此只要用 prev[] 保存上一轮的 f，
// 本轮结果写进 cur[]，每轮结束再把 cur 复制给 prev，空间就是 O(n)。
// 答案 = 所有 l < r 的 f(l, r) 之和，最多 n(n-1)/2 个方案。
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 5005;

int n;
char s[MAXN];  // 输入的数字串，下标 0..n-1
int dp_prev[MAXN]; // dp_prev[l] 保存上一轮（右端点为 r-1）的 f(l, r-1)
int cur[MAXN]; // cur[l] 保存本轮（右端点为 r）的 f(l, r)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = (int)strlen(s);

    long long ans = 0;

    // 枚举右端点 r，左端点 l 从 r-1 递减到 0
    for (int r = 1; r < n; r++) {
        for (int l = r - 1; l >= 0; l--) {
            int v; // v = f(l, r)

            if (s[l] != s[r]) {
                // 第一处不同就在最左边的 l：反转后该位变成原来的 s[r]
                v = (s[l] > s[r]) ? 1 : 0;
            } else {
                // 两端字符相同，整体是否更小取决于中间子串 s[l+1..r-1]
                if (r - l + 1 >= 4) {
                    v = dp_prev[l + 1]; // f(l+1, r-1)，上一轮已算好
                } else {
                    v = 0; // 长度 2、3：中间为空串或单字符，反转后不变
                }
            }

            cur[l] = v;
            ans += v;
        }

        // 本轮结果成为下一轮需要的「右端点为 r」的历史答案
        for (int i = 0; i < n; i++) {
            dp_prev[i] = cur[i];
        }
    }

    cout << ans << "\n";
    return 0;
}
