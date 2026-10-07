/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:41
 * update_at: 2026-10-06 09:41
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 15;
const int SHOW = 3; // 题面只要求输出前 3 个解

int n;
int pos[MAXN]; // pos[row] 表示第 row 行棋子所在的列号（从 1 开始）
int total;     // 解的总数
int head[MAXN][MAXN]; // 保存前 SHOW 个解
int head_cnt;         // 已保存的解数

// 在第 row 行放置棋子，col/diag1/diag2 为已占用的列、主对角线、副对角线的位掩码
void dfs(int row, int col, int diag1, int diag2) {
    if (row == n) { // n 行都放好了，得到一个完整解
        ++total;
        if (head_cnt < SHOW) {
            for (int i = 0; i < n; ++i) {
                head[head_cnt][i] = pos[i];
            }
            ++head_cnt;
        }
        return;
    }
    int full = (1 << n) - 1; // 低 n 位全 1
    int free = full & ~(col | diag1 | diag2); // 本行所有合法列
    while (free) {
        int bit = free & -free; // 取列号最小的合法列，保证字典序
        free ^= bit;
        pos[row] = __builtin_ctz(bit) + 1; // bit = 1 << (列号-1)，还原列号
        // 下一行：列直接合并；两条对角线朝相反方向各平移一位
        dfs(row + 1, col | bit, (diag1 | bit) << 1, (diag2 | bit) >> 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    total = 0;
    head_cnt = 0;
    dfs(0, 0, 0, 0);
    for (int k = 0; k < head_cnt; ++k) {
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << head[k][i];
        }
        cout << '\n';
    }
    cout << total << '\n';
    return 0;
}
