/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-15 13:40
 * update_at: 2026-11-15 13:55
 */
// main.cpp：区间 DP（自底向上）
//
// 核心思想：
// 1. 先压缩相邻同色块，答案只取决于压缩后的序列 c[0..m-1]。
// 2. 无论从哪个单点出发，已被洪水填充吞并的区域始终是一个连续区间 [l, r]。
//    而且在最优策略下，这整块区域当前的颜色一定等于左端原色 c[l] 或右端原色 c[r]。
// 3. 状态定义：
//    dp[l][r][0]：把子区间 [l, r] 染成全同色、且最终颜色为 c[l] 的最少步数。
//    dp[l][r][1]：把子区间 [l, r] 染成全同色、且最终颜色为 c[r] 的最少步数。
//
// 转移分析（区间长度从 2 到 m）：
// - 若要使 [l, r] 统一为颜色 c[l] (状态 0)，它必然由 [l+1, r] 扩张而来：
//   - 若 [l+1, r] 已是 c[l+1]，需花费 1 次染色变成 c[l]（相邻已去重，c[l] != c[l+1]）；
//   - 若 [l+1, r] 已是 c[r]，则当 c[l] == c[r] 时代价为 0，否则为 1。
//   即：dp[l][r][0] = min(dp[l+1][r][0] + 1, dp[l+1][r][1] + (c[l] != c[r]));
// - 对称地，使 [l, r] 统一为 c[r] (状态 1)：
//   dp[l][r][1] = min(dp[l][r-1][1] + 1, dp[l][r-1][0] + (c[l] != c[r]));
//
// 最终答案：min(dp[0][m-1][0], dp[0][m-1][1])。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int n;
int m;                   // 压缩相邻同色后的块数
int c[MAXN];             // 压缩后的颜色数组
short dp[MAXN][MAXN][2]; // dp[l][r][0/1]，用 short 节省内存（约 96 MB）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;

    // 读入并压缩相邻相同的颜色
    m = 0;
    for (int i = 0; i < n; ++i) {
        int color;
        cin >> color;
        if (m == 0 || c[m - 1] != color) {
            c[m++] = color;
        }
    }

    // 边界条件：单点区间 [i, i] 自身已同色，操作数为 0（全局数组已默认为 0）
    // 按区间长度从 2 到 m 递推
    for (int len = 2; len <= m; ++len) {
        for (int l = 0; l <= m - len; ++l) {
            int r = l + len - 1;
            int diff = (c[l] != c[r] ? 1 : 0);

            // 吞并并统一为左端颜色 c[l]
            dp[l][r][0] = min((int)dp[l + 1][r][0] + 1, (int)dp[l + 1][r][1] + diff);

            // 吞并并统一为右端颜色 c[r]
            dp[l][r][1] = min((int)dp[l][r - 1][1] + 1, (int)dp[l][r - 1][0] + diff);
        }
    }

    // 最终目标：将整个区间 [0, m-1] 统一为某种颜色
    cout << min(dp[0][m - 1][0], dp[0][m - 1][1]) << '\n';

    return 0;
}
