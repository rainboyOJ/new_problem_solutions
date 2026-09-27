/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 09:05
 * update_at: 2026-09-27 09:07
 */
// main2.cpp：T4 棋(Chess) 教学版——"五列窗口"DP（对应 main2.py）。
//
// 和 main.cpp 的"三列窗口 + 染色标记"不同，这里换个更好懂的切入角度：
//   一条三连最多跨 3 列，所以某一列的格子"是否染色"只取决于它左右各 2 列。
//   等一列左右各 2 列都确定了（凑齐 5 列窗口），就能一次性算出这一整列的得分。
// 好处：状态里不用再存"这一格是否已计入"的标记，思想更直白。
// 代价：状态要记最近 4 列；棋盘左边/右边不存在的列用"虚拟列"补上。
//
// 为了让 n = 1000 也能跑进 1s，这里多做一步预处理：
//   is_colored 只跟"5 列窗口"有关，跟具体列号/权值无关；
//   而同一个窗口会被大量 (状态, 新列图案) 组合反复查询。
//   所以先把所有窗口的"中间列染色情况"算好，主循环里 O(1) 查表。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG = -(1LL << 60);
const int MAXN = 1005;
const int ROWS = 3;      // 棋盘固定 3 行

const int PAT_CNT = 8;   // 一列的图案：3bit，0..7（bit r = 1 表示第 r 行是 X）
const int NONE = 8;      // 虚拟列（棋盘外），用一个额外取值 8 表示
const int BASE = 9;      // 状态按 9 进制存，每一位 0..8

const int SZ = BASE * BASE * BASE * BASE; // 状态：最近 4 列，9^4 = 6561
const int WIN_SZ = SZ * BASE;             // 窗口：最近 5 列，9^5 = 59049

int n;
ll w[ROWS][MAXN];        // w[行][列]：每个格子的权值

// 四个方向：横、竖、右下斜、右上斜
const int DR[4] = {0, 1, 1, 1};
const int DC[4] = {1, 0, 1, -1};

// 取一列图案 pattern 的第 row 位：1 表示 X，0 表示 O。
inline int color(int pattern, int row) {
    return (pattern >> row) & 1;
}

// 判断 5 列窗口 window[0..4] 的正中间列（下标 2）中，第 row 格是否位于某个三连里。
// window[c] 取值 0..7 是真实列，8(NONE) 表示棋盘外的虚拟列。
bool is_colored(const int window[5], int row) {
    if (window[2] == NONE) return false; // 中间列本身不存在
    int target = color(window[2], row);  // 这一格的颜色

    for (int d = 0; d < 4; d++) {
        // 当前格可以是这条三连里的第 0 / 1 / 2 个格子
        for (int position = 0; position < 3; position++) {
            bool same = true;
            for (int k = 0; k < 3; k++) {
                // 由"当前格"和"它在这条线里的位置"反推出整条线的 3 个格子
                int r = row + (k - position) * DR[d];
                int c = 2 + (k - position) * DC[d];
                if (r < 0 || r >= ROWS || c < 0 || c >= 5) { same = false; break; }
                if (window[c] == NONE) { same = false; break; } // 越出棋盘
                if (color(window[c], r) != target) { same = false; break; }
            }
            if (same) return true; // 找到一条三连
        }
    }
    return false;
}

/* ---------------- 状态 / 窗口的编码 ----------------
 * 把若干列图案按 9 进制拼成一个整数（低位是最旧的一列）。
 * 4 位 -> 状态，5 位 -> 窗口。
 */
inline int encode4(int d0, int d1, int d2, int d3) {
    return d0 + d1 * BASE + d2 * BASE * BASE + d3 * BASE * BASE * BASE;
}
inline void decode4(int s, int d[4]) {
    for (int i = 0; i < 4; i++) {
        d[i] = s % BASE;
        s /= BASE;
    }
}

/* ---------------- 预处理：窗口 -> 中间列的染色情况 ----------------
 * colored_mask[code] 的第 r 位 = 1，表示该窗口中间列第 r 行会被染色。
 * 同一个窗口在 DP 中会被查很多次，预处理后每次只需一次数组访问。
 */
static unsigned char colored_mask[WIN_SZ];

void precompute_colored() {
    for (int code = 0; code < WIN_SZ; code++) {
        int window[5];
        int t = code;
        for (int i = 0; i < 5; i++) { // 拆出 5 个 9 进制位
            window[i] = t % BASE;
            t /= BASE;
        }
        int mask = 0;
        for (int row = 0; row < ROWS; row++) {
            if (is_colored(window, row)) mask |= 1 << row;
        }
        colored_mask[code] = (unsigned char)mask;
    }
}

// 5 列都确定时，算出正中间列（对应棋盘第 col 列）的完整得分。
// middle_pattern 就是中间列的图案，用来定符号（X 红 +，O 蓝 -）。
ll middle_score(int code, int middle_pattern, int col) {
    int mask = colored_mask[code];
    ll score = 0;
    for (int row = 0; row < ROWS; row++) {
        if (!((mask >> row) & 1)) continue; // 没染色就不计分
        int sign = (color(middle_pattern, row) == 1) ? 1 : -1;
        score += sign * w[row][col];
    }
    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < n; c++) {
            cin >> w[r][c];
        }
    }

    precompute_colored();

    static ll dp[SZ], ndp[SZ]; // dp[状态] = 已经结算完的最大得分
    for (int s = 0; s < SZ; s++) dp[s] = NEG;

    // 初始：最近 4 列都是"虚拟列"（棋盘左边不存在）
    dp[encode4(NONE, NONE, NONE, NONE)] = 0;

    // 枚举 n 列真实棋盘，再补 2 列虚拟列，
    // 让最后两列也能各自成为一次"窗口正中间"被结算。
    for (int next_col = 0; next_col < n + 2; next_col++) {
        for (int s = 0; s < SZ; s++) ndp[s] = NEG;

        // 真实列可选图案 0..7；补出来的虚拟列只能是 NONE
        int lo = 0, hi = PAT_CNT;
        if (next_col >= n) { lo = NONE; hi = NONE + 1; }

        for (int s = 0; s < SZ; s++) {
            if (dp[s] == NEG) continue; // 不可达状态
            int d[4];
            decode4(s, d);

            for (int pattern = lo; pattern < hi; pattern++) {
                // 旧 4 列 + 新列 = 5 列窗口；顺手算出它的 9 进制编码
                int code = encode4(d[0], d[1], d[2], d[3]) + pattern * SZ;

                ll gain = 0;
                int middle_col = next_col - 2; // 窗口正中对应的棋盘列
                if (0 <= middle_col && middle_col < n) {
                    // 中间列左右各 2 列都齐了，可以结算它的整列得分
                    gain = middle_score(code, d[2], middle_col);
                }

                // 窗口右移一列：丢掉最旧的 d0，新状态是 (d1, d2, d3, pattern)
                int ns = encode4(d[1], d[2], d[3], pattern);
                ndp[ns] = max(ndp[ns], dp[s] + gain);
            }
        }

        for (int s = 0; s < SZ; s++) dp[s] = ndp[s];
    }

    // 全部列都已结算，取最大得分
    ll ans = NEG;
    for (int s = 0; s < SZ; s++) ans = max(ans, dp[s]);
    cout << ans << '\n';
    return 0;
}
