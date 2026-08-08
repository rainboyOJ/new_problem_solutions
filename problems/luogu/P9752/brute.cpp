// brute.cpp：小数据暴力解，把 5 个密码位看成选择序列，递归枚举每一位填 0..9。
#include <bits/stdc++.h>
using namespace std;

int n;
int record_state[10][5];
int pwd[5];
int answer;

bool can_change_to_record(int row) {
    int diff[5];
    int non_zero = 0;
    for (int i = 0; i < 5; i++) {
        diff[i] = (record_state[row][i] - pwd[i] + 10) % 10;
        if (diff[i] != 0) {
            non_zero++;
        }
    }

    if (non_zero == 1) {
        return true;
    }
    if (non_zero != 2) {
        return false;
    }

    for (int i = 0; i + 1 < 5; i++) {
        if (diff[i] != 0 && diff[i] == diff[i + 1]) {
            bool ok = true;
            for (int j = 0; j < 5; j++) {
                if (j != i && j != i + 1 && diff[j] != 0) {
                    ok = false;
                }
            }
            if (ok) {
                return true;
            }
        }
    }
    return false;
}

bool check_password() {
    for (int i = 1; i <= n; i++) {
        if (!can_change_to_record(i)) {
            return false;
        }
    }
    return true;
}

void dfs_build(int pos) {
    if (pos == 5) {
        if (check_password()) {
            answer++;
        }
        return;
    }

    // 这一层选择第 pos 位密码填哪个数字。
    for (int d = 0; d <= 9; d++) {
        pwd[pos] = d;
        dfs_build(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> record_state[i][j];
        }
    }

    dfs_build(0);
    cout << answer << '\n';
    return 0;
}
