/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:42
 * update_at: 2026-10-06 13:42
 */

// Jam 数字 = 从区间 [s,t] 里选 w 个字母组成的严格递增序列，
// 全体 Jam 数字按字典序排列。求后继就是"组合加一"：
// 从右往左找第一个未到上界的位，该位加 1，右边各位重置为最小连续字母。
#include <cstdio>
#include <iostream>
#include <string>
typedef long long ll;

const int MAXW = 30;

ll s, t, w;          // s 在求后继时用不到，读入只为完整解析输入
char cur[MAXW];      // cur[i] 表示 Jam 数字第 i 位（从 0 数起）的字母

// 求紧接在 cur 之后的 Jam 数字；已是最大数字则返回 0，否则返回 1
bool next_jam() {
    // 从最右往左找第一个还能加 1 的位
    for (ll i = w - 1; i >= 0; i--) {
        // 上界：最右位是第 t 号字母，其余位是右邻位的前一个字母（保证严格递增）
        char limit = (i == w - 1) ? char('a' + t - 1) : char(cur[i + 1] - 1);
        if (cur[i] < limit) {
            cur[i]++; // 该位加 1
            // 右边各位取紧随其后的最小连续字母，保证严格递增
            for (ll j = i + 1; j < w; j++) cur[j] = char(cur[j - 1] + 1);
            return true;
        }
    }
    return false; // 所有位都顶到上界，说明已是最大 Jam 数字
}

int main() {
    std::cin >> s >> t >> w >> cur;
    for (int k = 1; k <= 5; k++) {
        if (!next_jam()) break; // 后面没有更多 Jam 数字了
        std::cout << cur << "\n";
    }
    return 0;
}
