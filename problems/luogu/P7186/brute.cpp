#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 直接维护整张表，并按题目要求一格一格地移动目标数字。
const int MAXN = 55;

int n, k;
int a[MAXN][MAXN];

void shift_row_right(int row) {
    int last = a[row][n];
    for (int col = n; col >= 2; col--) {
        a[row][col] = a[row][col - 1];
    }
    a[row][1] = last;
}

void shift_col_down(int col) {
    int last = a[n][col];
    for (int row = n; row >= 2; row--) {
        a[row][col] = a[row - 1][col];
    }
    a[1][col] = last;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    int value = 0;
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            value++;
            a[row][col] = value;
        }
    }

    for (int q = 1; q <= k; q++) {
        int x, target_row, target_col;
        cin >> x >> target_row >> target_col;

        int row = 0, col = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i][j] == x) {
                    row = i;
                    col = j;
                }
            }
        }

        int ans = 0;

        while (col != target_col) {
            shift_row_right(row);
            col = col % n + 1;
            ans++;
        }

        while (row != target_row) {
            shift_col_down(target_col);
            row = row % n + 1;
            ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}
