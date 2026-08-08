#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1005;
const int MAXOPS = MAXK * 2 + 5;

int n, k;
int op_cnt;
int op_type[MAXOPS];  // 0 表示行右移，1 表示列下移
int op_idx[MAXOPS];   // 受影响的行号或列号
int op_delta[MAXOPS]; // 循环位移的格数

// 把一条历史操作作用到当前坐标 (row, col) 上。
void apply_op(int &row, int &col, int type, int idx, int delta) {
    if (type == 0) {
        if (row == idx) {
            col = (col - 1 + delta) % n + 1;
        }
    } else {
        if (col == idx) {
            row = (row - 1 + delta) % n + 1;
        }
    }
}

// 计算数字 x 在当前表格中的位置。
void get_position(long long x, int &row, int &col) {
    row = (int)((x - 1) / n) + 1;
    col = (int)((x - 1) % n) + 1;
    for (int i = 1; i <= op_cnt; i++) {
        apply_op(row, col, op_type[i], op_idx[i], op_delta[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int q = 1; q <= k; q++) {
        long long x;
        int target_row, target_col;
        cin >> x >> target_row >> target_col;

        int row, col;
        get_position(x, row, col);

        int row_move = (target_col - col + n) % n;
        int col_move = (target_row - row + n) % n;

        cout << row_move + col_move << '\n';

        if (row_move != 0) {
            op_cnt++;
            op_type[op_cnt] = 0;
            op_idx[op_cnt] = row;
            op_delta[op_cnt] = row_move;
        }

        if (col_move != 0) {
            op_cnt++;
            op_type[op_cnt] = 1;
            op_idx[op_cnt] = target_col;
            op_delta[op_cnt] = col_move;
        }
    }

    return 0;
}
