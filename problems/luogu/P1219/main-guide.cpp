/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1219 八皇后：按行放皇后，用列、主对角线、副对角线三个标记数组剪枝，回溯求全部方案。 */

#include <iostream>

const int max_n = 14;    // n 最大为 13，多开一位
const int max_diag = 30; // 0 起始时对角线编号最大不超过 2 * max_n

int n;
int col_of_row[max_n];    // col_of_row[row]：第 row 行皇后所在的列
int used_col[max_n];      // used_col[col] = true 表示第 col 列已有皇后
int used_diag1[max_diag]; // used_diag1[k] = true 表示主对角线（row - col + n）已有皇后
int used_diag2[max_diag]; // used_diag2[k] = true 表示副对角线（row + col）已有皇后
int total_count = 0;      // 合法方案总数
int printed_count = 0;    // 已经输出的方案个数

// 输出一个完整方案：第 row 行皇后所在的列号，题目从 1 开始编号
void print_solution() {
    for (int row = 0; row < n; row += 1) {
        if (row > 0) {
            std::cout << ' ';
        }
        std::cout << col_of_row[row] + 1;
    }
    std::cout << '\n';
}

// 从第 row 行开始放皇后；列从小到大尝试，保证完整方案按字典序出现
void dfs(int row) {
    if (row == n) {  // 所有行都放完了，得到一个完整方案
        total_count += 1;
        if (printed_count < 3) {  // 只输出前 3 个方案
            print_solution();
            printed_count += 1;
        }
        return;
    }

    for (int col = 0; col < n; col += 1) {
        int d1 = row - col + n;  // 主对角线编号：同一条对角线上 row - col 相等
        int d2 = row + col;      // 副对角线编号：同一条对角线上 row + col 相等
        if (used_col[col] || used_diag1[d1] || used_diag2[d2]) {
            continue;  // 这一列或某条对角线已被占用，不能放
        }

        col_of_row[row] = col;
        used_col[col] = 1;
        used_diag1[d1] = 1;
        used_diag2[d2] = 1;

        dfs(row + 1);

        // 回溯：撤销本行放的皇后，让其他分支可以重新使用
        used_col[col] = 0;
        used_diag1[d1] = 0;
        used_diag2[d2] = 0;
    }
}

int main() {
    std::cin >> n;

    dfs(0);
    std::cout << total_count << '\n';

    return 0;
}
