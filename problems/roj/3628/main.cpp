/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:31
 * update_at: 2026-10-06 15:31
 */

// 按 NOIp2015 幻方的四条规则逐格模拟：向右上走、出界回绕、右上角特判正下、被挡改下移。

#include <cstdio>

typedef long long ll;

const int MAXN = 40; // N <= 39 且为奇数

ll n;              // 幻方边长
ll square[MAXN][MAXN]; // square[r][c] = 该格填的数，0 表示还没填

// 按题面规则从 (row,col) 求数字 K 的落点
void move_next(ll &row, ll &col) {
    if (row == 0 && col != n - 1) {        // 规则 1：第一行且非最后一列，回绕到最后一行、列右移
        row = n - 1;
        col = col + 1;
    } else if (col == n - 1 && row != 0) { // 规则 2：最后一列且非第一行，回绕到第一列、行上移
        row = row - 1;
        col = 0;
    } else if (row == 0 && col == n - 1) { // 规则 3：右上角，填正下方
        row = row + 1;
    } else if (square[row - 1][col + 1] == 0) { // 规则 4：右上方为空，填右上方
        row = row - 1;
        col = col + 1;
    } else {                               // 规则 4：右上方已被占，改填正下方
        row = row + 1;
    }
}

int main() {
    scanf("%lld", &n);
    ll row = 0;        // 数字 1 放在第一行正中间
    ll col = n / 2;
    for (ll k = 1; k <= n * n; ++k) {
        square[row][col] = k;
        move_next(row, col); // 求下一个数的落点；填到最后一个数时结果不再使用
    }
    for (ll r = 0; r < n; ++r) {
        for (ll c = 0; c < n; ++c) {
            printf("%lld%c", square[r][c], c == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
