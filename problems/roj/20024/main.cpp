/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:42
 * update_at: 2026-08-28 23:42
 */
// main.cpp：T4 棋(Chess) 正式解
// 思路：3 列滑窗 + colored 标记的窄带状压 DP。
// 每列压缩成 2 个 3bit：图案 pat（1=X，0=O）与"已计入权值"标记 col。
// 状态记录相邻两列 (旧列A, 新列B)，枚举新列图案后，
// 三连判定只依赖这 3 列：纵向(整列相同)、横向(同行相同)、两条对角线。
// 每个格子的权值在它的列"滑出窗口左端"时恰好结算一次，保证不重不漏。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG_INF = -(1LL << 60);
const int MAXN = 1005;

int n;
ll w[3][MAXN]; // w[行][列]：每个格子的权值

inline int bit(int x, int k) { return (x >> k) & 1; }

/* 列状态：每列 2 个 3bit（bit r 对应第 r 行）
 *   pat : 图案，bit = 1 表示 X，0 表示 O
 *   col : 已计入标记，bit = 1 表示该格子权值已经算进答案
 * 状态 s 共 12bit，低 6 位是窗口左端"旧列"，高 6 位是"新列"：
 *   s = patA | (colA<<3) | (patB<<6) | (colB<<9)
 */
inline int encode(int pa, int ca, int pb, int cb) {
    return pa | (ca << 3) | (pb << 6) | (cb << 9);
}
inline void decode(int s, int &pa, int &ca, int &pb, int &cb) {
    pa = s & 7;
    ca = (s >> 3) & 7;
    pb = (s >> 6) & 7;
    cb = (s >> 9) & 7;
}

// n <= 2：列数不够 3，只可能有"纵向三连"（整列相同 000/111）
void solve_small() {
    ll best = NEG_INF;
    for (int p0 = 0; p0 < 8; p0++) {          // 第 0 列的图案
        for (int p1 = 0; p1 < (n == 2 ? 8 : 1); p1++) { // 第 1 列的图案
            ll cur = 0;
            if (p0 == 0 || p0 == 7) {         // 第 0 列整列相同 -> 纵向三连
                int sgn = (p0 & 1) ? 1 : -1;  // X 红 +，O 蓝 -
                for (int r = 0; r < 3; r++) cur += w[r][0] * sgn;
            }
            if (n == 2 && (p1 == 0 || p1 == 7)) {
                int sgn = (p1 & 1) ? 1 : -1;
                for (int r = 0; r < 3; r++) cur += w[r][1] * sgn;
            }
            best = max(best, cur);
        }
    }
    cout << best << '\n';
}

void solve() {
    if (n <= 2) { solve_small(); return; }

    const int SZ = 1 << 12; // 4096 种状态
    static ll dp[SZ], ndp[SZ];
    for (int s = 0; s < SZ; s++) dp[s] = NEG_INF;

    // 初始：只确定第 0、1 列图案，没有任何格子计入权值
    for (int p0 = 0; p0 < 8; p0++)
        for (int p1 = 0; p1 < 8; p1++)
            dp[encode(p0, 0, p1, 0)] = 0;

    // 主循环：枚举新列 j（0 基），本轮把列 j-2 定型并结算它的权值
    for (int j = 2; j < n; j++) {
        int colFinal = j - 2; // 本轮滑出窗口左端的列
        for (int s = 0; s < SZ; s++) ndp[s] = NEG_INF;

        for (int s = 0; s < SZ; s++) {
            if (dp[s] <= NEG_INF) continue;
            int pa, ca, pb, cb;
            decode(s, pa, ca, pb, cb);

            for (int pc = 0; pc < 8; pc++) {   // 枚举新列 j 的图案
                int ca2 = ca, cb2 = cb, cc = 0; // 三列的"已计入"标记
                ll gain = 0;

                // 1. 结算旧列 j-2 中之前已被标记(计入)过的格子
                for (int r = 0; r < 3; r++)
                    if (bit(ca, r))
                        gain += w[r][colFinal] * (bit(pa, r) ? 1 : -1);

                // 2. 纵向三连：旧列整列图案相同(000/111)
                if (pa == 0 || pa == 7) {
                    int sgn = (pa & 1) ? 1 : -1;
                    for (int r = 0; r < 3; r++) {
                        if (!bit(ca2, r)) {
                            gain += w[r][colFinal] * sgn;
                            ca2 |= (1 << r);
                        }
                    }
                }

                // 3. 横向三连：同一行上旧列、中列、新列图案相同
                for (int r = 0; r < 3; r++) {
                    if (bit(pa, r) == bit(pb, r) && bit(pb, r) == bit(pc, r)) {
                        int sgn = bit(pa, r) ? 1 : -1;
                        if (!bit(ca2, r)) {     // 旧列格子：计入并立即结算
                            gain += w[r][colFinal] * sgn;
                            ca2 |= (1 << r);
                        }
                        cb2 |= (1 << r);        // 中列格子：只标记，轮到自己定型时结算
                        cc |= (1 << r);         // 新列格子：只标记
                    }
                }

                // 4. 对角线 ↘：格 (0,旧列)(1,中列)(2,新列)
                if (bit(pa, 0) == bit(pb, 1) && bit(pb, 1) == bit(pc, 2)) {
                    int sgn = bit(pa, 0) ? 1 : -1;
                    if (!bit(ca2, 0)) {
                        gain += w[0][colFinal] * sgn;
                        ca2 |= 1;
                    }
                    cb2 |= (1 << 1);
                    cc |= (1 << 2);
                }
                // 5. 对角线 ↗：格 (2,旧列)(1,中列)(0,新列)
                if (bit(pa, 2) == bit(pb, 1) && bit(pb, 1) == bit(pc, 0)) {
                    int sgn = bit(pa, 2) ? 1 : -1;
                    if (!bit(ca2, 2)) {
                        gain += w[2][colFinal] * sgn;
                        ca2 |= (1 << 2);
                    }
                    cb2 |= (1 << 1);
                    cc |= (1 << 0);
                }

                int ns = encode(pb, cb2, pc, cc);
                ndp[ns] = max(ndp[ns], dp[s] + gain);
            }
        }
        for (int s = 0; s < SZ; s++) dp[s] = ndp[s];
    }

    // 收尾：最后两列 n-2、n-1 右侧没有第三列，
    // 只可能有"纵向三连"，结算标记格子并补上纵向三连
    ll ans = NEG_INF;
    for (int s = 0; s < SZ; s++) {
        if (dp[s] <= NEG_INF) continue;
        int pa, ca, pb, cb;
        decode(s, pa, ca, pb, cb);
        ll val = dp[s];

        for (int r = 0; r < 3; r++)             // 列 n-2 的标记格子
            if (bit(ca, r)) val += w[r][n - 2] * (bit(pa, r) ? 1 : -1);
        if (pa == 0 || pa == 7) {               // 列 n-2 的纵向三连
            int sgn = (pa & 1) ? 1 : -1;
            for (int r = 0; r < 3; r++)
                if (!bit(ca, r)) val += w[r][n - 2] * sgn;
        }
        for (int r = 0; r < 3; r++)             // 列 n-1 的标记格子
            if (bit(cb, r)) val += w[r][n - 1] * (bit(pb, r) ? 1 : -1);
        if (pb == 0 || pb == 7) {               // 列 n-1 的纵向三连
            int sgn = (pb & 1) ? 1 : -1;
            for (int r = 0; r < 3; r++)
                if (!bit(cb, r)) val += w[r][n - 1] * sgn;
        }
        ans = max(ans, val);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < n; c++)
            cin >> w[r][c];

    solve();
    return 0;
}