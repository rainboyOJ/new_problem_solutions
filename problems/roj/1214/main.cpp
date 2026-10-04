/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:42
 * update_at: 2026-10-05 05:42
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int N = 8;                // 棋盘为 8 × 8
const int ALL = (1 << N) - 1;   // 低 8 位为 1，表示当前行可放列的掩码

int col_of_row[N];              // col_of_row[i] 记录第 i 行皇后所在的列号（1..8）
vector<string> solutions;       // 所有合法皇后串

// 按行 DFS：row 为当前处理行，cols/diag1/diag2 分别记录已被占用的列、主对角线、副对角线
void dfs(int row, int cols, int diag1, int diag2) {
    if (row == N) {
        string s;
        for (int i = 0; i < N; ++i) s.push_back('0' + col_of_row[i]);
        solutions.push_back(s);
        return;
    }
    int free = ALL & ~(cols | diag1 | diag2); // 当前行仍可放的列
    while (free) {
        int low = free & -free;                // 取最低位 1 作为当前列
        int c = __builtin_ctz(low);            // 列号 0..7
        col_of_row[row] = c + 1;
        // 下一行：列占用不变；对角线分别左移/右移一位表示攻击范围向下延伸
        dfs(row + 1, cols | low, (diag1 | low) << 1, (diag2 | low) >> 1);
        free ^= low;                           // 清除这一位，尝试下一列
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    dfs(0, 0, 0, 0);
    sort(solutions.begin(), solutions.end());  // 按整数值排序

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        cout << solutions[b - 1] << '\n';
    }
    return 0;
}
