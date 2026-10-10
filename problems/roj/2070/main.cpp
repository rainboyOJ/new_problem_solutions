/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:07
 * update_at: 2026-10-08 07:07
 */
// usaco-4.3.2 素数方阵（ROJ 2070）
// 5x5 网格的 5 行、5 列、2 条对角线都是数位和恰为 S 的五位素数，左上角固定为 D。
//
// 关键：两条对角线只共享中心点，先把它们定下来就锁死四角与中心；四条边框线
// 于是各有两个端点已知。边框上四个"肩部"数字 b/v/d/x、g/i/q/s 一旦选定，
// 内部 4 个格子的值就被行 1、行 3、列 1、列 3 的数位和唯一确定，
// 只剩第 2 行、第 2 列两个和约束作为校验——搜索因此坍缩成两层小枚举。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXV = 100000;                        // 五位素数 < 100000
const int PW[5] = {10000, 1000, 100, 10, 1};    // 第 pos 位权重（0 = 万位）

bool isPrime[MAXV];            // 埃氏筛结果
int g[5][5];                   // 网格，g[r][c]：第 r 行第 c 列，0 行在最上
int S;                         // 各条线共同的数位和
int D;                         // 左上角固定数字
vector<int> cand;              // 数位和恰为 S 的五位素数，升序
vector<int> headTail[10][10];  // headTail[h][t]：首位 h、末位 t 的候选素数
vector<string> ans;            // 所有解，按行拼成的 25 位数字串

int digit(int x, int pos) {
    // 取五位数的第 pos 位，0 = 万位 … 4 = 个位
    return x / PW[pos] % 10;
}

bool okValue(int v) {
    // 合法线：五位素数且数位和恰为 S（首位非零由 v >= 10000 保证）
    if (v < 10000 || !isPrime[v]) return false;
    int sum = 0;
    for (int k = 0; k < 5; k++) sum += digit(v, k);
    return sum == S;
}

int make5(int a, int b, int c, int d, int e) {
    return a * 10000 + b * 1000 + c * 100 + d * 10 + e;
}

int main() {
    for (int i = 2; i < MAXV; i++) isPrime[i] = true;
    for (int i = 2; i * i < MAXV; i++)
        if (isPrime[i])
            for (int j = i * i; j < MAXV; j += i) isPrime[j] = false;

    if (scanf("%d %d", &S, &D) != 2) return 0;

    for (int p = 10000; p < MAXV; p++) {
        if (!isPrime[p]) continue;
        int sum = 0;
        for (int k = 0; k < 5; k++) sum += digit(p, k);
        if (sum == S) cand.push_back(p);
    }
    if (cand.empty()) { printf("NONE\n"); return 0; }
    for (size_t t = 0; t < cand.size(); t++)
        headTail[cand[t] / 10000][cand[t] % 10].push_back(cand[t]);

    for (size_t i1 = 0; i1 < cand.size(); i1++) {
        int d1 = cand[i1];                          // 主对角线，首位必须等于 D
        if (digit(d1, 0) != D) continue;
        int mid = digit(d1, 2);                     // 中心点 (2,2)
        int e3 = digit(d1, 1), e5 = digit(d1, 3);   // 主对角线第 2、4 位
        for (size_t i2 = 0; i2 < cand.size(); i2++) {
            int d2 = cand[i2];                      // 副对角线，必须穿过中心点
            if (digit(d2, 2) != mid) continue;
            // 副对角线也按从左到右读：左端是左下角，故第 1 位 = 左下角、第 5 位 = 右上角
            int x40 = digit(d2, 0), x04 = digit(d2, 4);  // 左下、右上角
            int x44 = digit(d1, 4);                      // 右下角
            int f4 = digit(d2, 1), f2 = digit(d2, 3);    // 副对角线第 2、4 位（g[3][1]、g[1][3]）

            // 第 0、4 行：首尾即左上/右上、左下/右下角
            vector<int> &r0s = headTail[D][x04], &r4s = headTail[x40][x44];
            // 第 0、4 列：首尾即左上/左下角、右上/右下角
            vector<int> &c0s = headTail[D][x40], &c4s = headTail[x04][x44];

            for (size_t a = 0; a < r0s.size(); a++) {
                int r0 = r0s[a];
                int b = digit(r0, 1), c = digit(r0, 2), d = digit(r0, 3);
                for (size_t ii = 0; ii < r4s.size(); ii++) {
                    int r4 = r4s[ii];
                    int v = digit(r4, 1), w = digit(r4, 2), x = digit(r4, 3);
                    // 列 1、列 3 的数位和分别定出 g[2][1]、g[2][3]
                    int m = S - b - e3 - f4 - v;
                    int o = S - d - f2 - e5 - x;
                    if (m < 0 || m > 9 || o < 0 || o > 9) continue;
                    int col1 = make5(b, e3, m, f4, v);
                    if (!okValue(col1)) continue;
                    int col3 = make5(d, f2, o, e5, x);
                    if (!okValue(col3)) continue;

                    for (size_t bb = 0; bb < c0s.size(); bb++) {
                        int c0 = c0s[bb];
                        int gg = digit(c0, 1), l = digit(c0, 2), q = digit(c0, 3);
                        for (size_t dd = 0; dd < c4s.size(); dd++) {
                            int c4 = c4s[dd];
                            int i = digit(c4, 1), n = digit(c4, 2), s = digit(c4, 3);
                            // 行 1、行 3 的数位和分别定出 g[1][2]、g[3][2]
                            int h = S - gg - e3 - f2 - i;
                            int r = S - q - f4 - e5 - s;
                            if (h < 0 || h > 9 || r < 0 || r > 9) continue;
                            if (!okValue(make5(gg, e3, h, f2, i))) continue;   // 第 1 行
                            if (!okValue(make5(q, f4, r, e5, s))) continue;    // 第 3 行
                            // 第 2 行 / 第 2 列是最后两个和约束，顺带查素数
                            if (!okValue(make5(l, m, mid, o, n))) continue;    // 第 2 行
                            if (!okValue(make5(c, h, mid, r, w))) continue;    // 第 2 列

                            g[0][0] = D;    g[0][1] = b;  g[0][2] = c;   g[0][3] = d;   g[0][4] = x04;
                            g[1][0] = gg;   g[1][1] = e3; g[1][2] = h;   g[1][3] = f2;  g[1][4] = i;
                            g[2][0] = l;    g[2][1] = m;  g[2][2] = mid; g[2][3] = o;   g[2][4] = n;
                            g[3][0] = q;    g[3][1] = f4; g[3][2] = r;   g[3][3] = e5;  g[3][4] = s;
                            g[4][0] = x40;  g[4][1] = v;  g[4][2] = w;   g[4][3] = x;   g[4][4] = x44;
                            string cur;
                            for (int rr = 0; rr < 5; rr++)
                                for (int cc = 0; cc < 5; cc++) cur += char('0' + g[rr][cc]);
                            ans.push_back(cur);
                        }
                    }
                }
            }
        }
    }

    if (ans.empty()) { printf("NONE\n"); return 0; }
    sort(ans.begin(), ans.end());   // 按 25 位数升序
    for (size_t i = 0; i < ans.size(); i++) {
        if (i) printf("\n");
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) putchar(ans[i][r * 5 + c]);
            putchar('\n');
        }
    }
    return 0;
}
