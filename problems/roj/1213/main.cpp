/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:51
 * update_at: 2026-10-05 10:51
 */
// main.cpp：八皇后问题，按列回溯放皇后，用位掩码压缩"行 / 两条对角线"的占用状态。
// 与 main.py 同一算法：每层取最低可行行，产出顺序就是题目要求的"列优先、行号升序"。

#include <bits/stdc++.h>
using namespace std;

const int SIZE = 8;                 // 棋盘边长，本题固定为八皇后
const int ALL_ROWS = (1 << SIZE) - 1; // 八行全满：掩码的低 8 位全是 1

int choose_col[SIZE]; // choose_col[c] 表示第 c 列皇后所在的行号（0 起）
int no;               // 当前解的编号，从 1 开始递增

// cols / d1 / d2 分别是已被占用的行、副对角线（左上→右下）、
// 主对角线（左下→右上）掩码；列每右移一格，两条对角线掩码就各整体移位一位，
// 于是"对角线冲突"退化成一次位与。掩码只有 8 位，用 int 足够。
void dfs(int c, int cols, int d1, int d2) {
    if (c == SIZE) { // 八列都放好了，choose_col[0..7] 就是一个完整解，直接输出
        no++;
        cout << "No. " << no << "\n";
        for (int r = 0; r < SIZE; r++) { // 按行打印棋盘，皇后所在格是 1
            for (int col = 0; col < SIZE; col++) {
                cout << (choose_col[col] == r ? 1 : 0) << " ";
            }
            cout << "\n";
        }
        return;
    }
    int avail = ALL_ROWS & ~(cols | d1 | d2); // 这一列还能落在哪些行
    while (avail) {
        int bit = avail & -avail; // 最低位的可行行
        avail ^= bit;             // 该行枚举过就划掉
        choose_col[c] = __builtin_ctz(bit); // 行号 = 二进制最低位的下标
        dfs(c + 1, cols | bit, (d1 | bit) << 1, (d2 | bit) >> 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    dfs(0, 0, 0, 0); // 从第 0 列开始，三个掩码都为空

    return 0;
}
