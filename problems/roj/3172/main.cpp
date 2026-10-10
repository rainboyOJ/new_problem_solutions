/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 棋盘分割：记忆化搜索最小化各块分值平方和，最后换算成均方差
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

const int SIZE = 8;    // 棋盘边长固定为 8
const int MAXK = 20;   // 切块数上界
const ll INF = 1000000000000000000LL; // 一块也切不动时的不可行代价

int cells[SIZE][SIZE];
ll pre[SIZE + 1][SIZE + 1]; // 二维前缀和
ll memo[SIZE][SIZE][SIZE][SIZE][MAXK + 1]; // best(r1,c1,r2,c2,k) 的缓存，-1 表示未算

// 闭区间矩形 [r1,r2] x [c1,c2] 的分值之和
ll box(int r1, int c1, int r2, int c2) {
    return pre[r2 + 1][c2 + 1] - pre[r1][c2 + 1] - pre[r2 + 1][c1] + pre[r1][c1];
}

// 把矩形切成 k 块时各块分值平方和的最小值
ll best(int r1, int c1, int r2, int c2, int k) {
    if (k == 1) {
        ll s = box(r1, c1, r2, c2);
        return s * s;
    }
    ll& res = memo[r1][c1][r2][c2][k];
    if (res >= 0) {
        return res;
    }
    ll ans = INF;
    // 横着切：上面一块定稿，下面一块还要再切 k-1 刀
    for (int i = r1; i < r2; i++) {
        ll s1 = box(r1, c1, i, c2);
        ll v = s1 * s1 + best(i + 1, c1, r2, c2, k - 1);
        if (v < ans) {
            ans = v;
        }
        ll s2 = box(i + 1, c1, r2, c2);
        v = s2 * s2 + best(r1, c1, i, c2, k - 1);
        if (v < ans) {
            ans = v;
        }
    }
    // 竖着切：左一块定稿，右一块还要再切 k-1 刀
    for (int j = c1; j < c2; j++) {
        ll s1 = box(r1, c1, r2, j);
        ll v = s1 * s1 + best(r1, j + 1, r2, c2, k - 1);
        if (v < ans) {
            ans = v;
        }
        ll s2 = box(r1, j + 1, r2, c2);
        v = s2 * s2 + best(r1, c1, r2, j, k - 1);
        if (v < ans) {
            ans = v;
        }
    }
    res = ans;
    return ans;
}

int main() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            for (int a = 0; a < SIZE; a++) {
                for (int b = 0; b < SIZE; b++) {
                    for (int k = 0; k <= MAXK; k++) {
                        memo[r][c][a][b][k] = -1;
                    }
                }
            }
        }
    }
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            scanf("%d", &cells[r][c]);
            pre[r + 1][c + 1] = pre[r][c + 1] + pre[r + 1][c] - pre[r][c] + cells[r][c];
        }
    }
    ll total = pre[SIZE][SIZE];
    ll s2 = best(0, 0, SIZE - 1, SIZE - 1, n); // Σx² 的最小值
    double ans = sqrt((double)s2 / n - ((double)total / n) * ((double)total / n));
    printf("%.3f\n", ans);
    return 0;
}
