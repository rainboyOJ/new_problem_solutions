/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 09:05
 * update_at: 2026-09-27 22:56
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
//   染色判断只跟"5 列窗口"有关，跟具体列号/权值无关；
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

// 取一列图案 pattern 的第 row 位：1 表示 X，0 表示 O。
inline int color(int pattern, int row) {
    return (pattern >> row) & 1;
}

/* ---------------- 窗口里"经过中间列"的三连 ----------------
 * 窗口是 3 行 x 5 列。长度为 3 的直线有很多条，但本轮只结算中间列（列 2），
 * 所以只保留"经过列 2"的线。每条线写成 3 个格子。
 *
 *        列 0   列 1   列 2   列 3   列 4
 *   行 0   .      .      .      .      .
 *   行 1   .      .      .      .      .
 *   行 2   .      .      .      .      .
 *                 ↑ 中间列，本轮的结算对象
 */
const int LINE_CNT = 16;      // 横向 9 + 纵向 1 + 右下斜 3 + 右上斜 3
int line_r[LINE_CNT][3];      // 每条线 3 个格子的行
int line_c[LINE_CNT][3];      // 每条线 3 个格子的列

void build_lines() {
    int cnt = 0;

    // 横向 9 条：每行都有 3 条（起点列 0 / 1 / 2），条条都经过列 2，生成：
    //   ((0,0),(0,1),(0,2))  ((0,1),(0,2),(0,3))  ((0,2),(0,3),(0,4))
    //   ((1,0),(1,1),(1,2))  ((1,1),(1,2),(1,3))  ((1,2),(1,3),(1,4))
    //   ((2,0),(2,1),(2,2))  ((2,1),(2,2),(2,3))  ((2,2),(2,3),(2,4))
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < 3; c++) {
            for (int k = 0; k < 3; k++) {
                line_r[cnt][k] = r;
                line_c[cnt][k] = c + k;
            }
            cnt++;
        }
    }

    // 纵向 1 条：只有列 2 自己的竖线完整落在窗口里，生成：
    //   ((0,2),(1,2),(2,2))
    for (int k = 0; k < 3; k++) {
        line_r[cnt][k] = k;
        line_c[cnt][k] = 2;
    }
    cnt++;

    // 右下斜 3 条：从第 0 行走到第 2 行，行 +1、列 +1，生成：
    //   ((0,0),(1,1),(2,2))  ((0,1),(1,2),(2,3))  ((0,2),(1,3),(2,4))
    for (int c = 0; c < 3; c++) {
        for (int k = 0; k < 3; k++) {
            line_r[cnt][k] = k;
            line_c[cnt][k] = c + k;
        }
        cnt++;
    }

    // 右上斜 3 条：从第 0 行走到第 2 行，行 +1、列 -1，生成：
    //   ((0,2),(1,1),(2,0))  ((0,3),(1,2),(2,1))  ((0,4),(1,3),(2,2))
    for (int c = 0; c < 3; c++) {
        for (int k = 0; k < 3; k++) {
            line_r[cnt][k] = k;
            line_c[cnt][k] = c + 2 - k;
        }
        cnt++;
    }
}

// 窗口中间列哪几行位于某个三连中：第 row 位 = 1 表示 (row, 2) 被染色。
// window[c] 取值 0..7 是真实列，8(NONE) 表示棋盘外的虚拟列。
int colored_mask_of(const int window[5]) {
    int mask = 0;

    for (int i = 0; i < LINE_CNT; i++) {
        // 三连里只要有一格是虚拟列（棋盘外），这条线就不成立
        int r0 = line_r[i][0], c0 = line_c[i][0];
        if (window[c0] == NONE) continue;

        // 三个格子同色，才构成一条三连
        int target = color(window[c0], r0);
        bool same = true;
        for (int k = 1; k < 3; k++) {
            int r = line_r[i][k], c = line_c[i][k];
            if (window[c] == NONE || color(window[c], r) != target) { same = false; break; }
        }
        if (!same) continue;

        // 只登记中间列的行
        for (int k = 0; k < 3; k++) {
            if (line_c[i][k] == 2) mask |= 1 << line_r[i][k];
        }
    }

    return mask;
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
        colored_mask[code] = (unsigned char)colored_mask_of(window);
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

    build_lines();
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
