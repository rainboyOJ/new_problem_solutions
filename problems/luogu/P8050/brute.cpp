// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 205;

int n1, m1, n2, m2, k;
int top_rows;
int total_rows;
int a[MAXN][MAXN];
int miss_x, miss_y;

int row_len(int row) {
    if (row <= top_rows) {
        return m1;
    }
    return m2;
}

int cell_sign(int row, int col) {
    if ((row + col) % 2 == 0) {
        return 1;
    }
    return -1;
}

void read_input() {
    cin >> n1 >> m1 >> n2 >> m2 >> k;
    if (n1 > 0 && m1 > 0) {
        top_rows = n1;
    } else {
        top_rows = 0;
    }
    total_rows = top_rows + n2;

    miss_x = miss_y = 0;
    for (int i = 1; i <= total_rows; i++) {
        int len = row_len(i);
        for (int j = 1; j <= len; j++) {
            cin >> a[i][j];
            if (a[i][j] == 999999) {
                miss_x = i;
                miss_y = j;
            }
        }
    }
}

// 直接枚举缺失值，检查黑白带符号和是否和初始棋盘一致。
bool check_value(int value) {
    ll sum = 0;
    for (int i = 1; i <= total_rows; i++) {
        int len = row_len(i);
        for (int j = 1; j <= len; j++) {
            int cur = a[i][j];
            if (i == miss_x && j == miss_y) {
                cur = value;
            }
            sum += 1LL * cell_sign(i, j) * cur;
        }
    }

    ll target = 0;
    for (int i = 1; i <= total_rows; i++) {
        int len = row_len(i);
        for (int j = 1; j <= len; j++) {
            target += 1LL * cell_sign(i, j) * k;
        }
    }
    return sum == target;
}

void solve() {
    for (int value = -1000; value <= 1000; value++) {
        if (check_value(value)) {
            cout << value << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
