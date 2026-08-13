/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:19
 * update_at: 2026-08-13 13:19
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15; // n 最大为 13，多开一点防止越界
const int MAXD = 30; // 对角线编号范围：row - col + n 最大 25，row + col 最大 26

int n;
int pos[MAXN];        // pos[i]：第 i 行皇后所在的列号
int used_col[MAXN];   // used_col[c]：第 c 列是否已放皇后
int used_diag1[MAXD]; // used_diag1[k]：主对角线 row - col + n 是否已放皇后
int used_diag2[MAXD]; // used_diag2[k]：副对角线 row + col 是否已放皇后
long long total_ans;  // 合法方案总数
int printed_cnt;      // 已经输出的方案个数

// 输出当前完整方案：一行内按行号输出皇后所在列号。
void print_solution() {
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << pos[i];
    }
    cout << '\n';
}

// 从第 row 行开始放皇后，枚举这一行可以放在哪一列。
// 列从小到大枚举，保证完整方案按字典序出现。
void dfs(int row) {
    if (row > n) { // 所有行都放完了，得到一个完整方案
        total_ans++;
        if (printed_cnt < 3) { // 只输出前 3 个解
            print_solution();
            printed_cnt++;
        }
        return;
    }

    for (int col = 1; col <= n; col++) {
        int d1 = row - col + n; // 主对角线编号：同一条对角线上 row - col 相等
        int d2 = row + col;     // 副对角线编号：同一条对角线上 row + col 相等
        if (used_col[col] || used_diag1[d1] || used_diag2[d2]) {
            continue; // 这一列或某条对角线已被占用，不能放
        }

        pos[row] = col;
        used_col[col] = 1;
        used_diag1[d1] = 1;
        used_diag2[d2] = 1;

        dfs(row + 1);

        // 回溯：撤销本行放的皇后
        used_col[col] = 0;
        used_diag1[d1] = 0;
        used_diag2[d2] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    dfs(1);
    cout << total_ans << '\n';

    return 0;
}
