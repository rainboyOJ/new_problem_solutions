// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n;
int pos[MAXN];   // pos[i]：第 i 行皇后放置的列
long long total_ans;
int printed_cnt;

bool can_place(int row, int col) {
    for (int i = 1; i < row; i++) {
        if (pos[i] == col) {
            return false;
        }
        if (abs(i - row) == abs(pos[i] - col)) {
            return false;
        }
    }
    return true;
}

void print_solution() {
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << pos[i];
    }
    cout << '\n';
}

void dfs(int row) {
    if (row > n) {
        total_ans++;
        if (printed_cnt < 3) {
            print_solution();
            printed_cnt++;
        }
        return;
    }

    for (int col = 1; col <= n; col++) {
        if (!can_place(row, col)) {
            continue;
        }
        pos[row] = col;
        dfs(row + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    total_ans = 0;
    printed_cnt = 0;
    dfs(1);
    cout << total_ans << '\n';

    return 0;
}
