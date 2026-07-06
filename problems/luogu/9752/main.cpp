// main.cpp：枚举所有 5 位密码，检查它能否一次操作变成每个记录状态。
#include <bits/stdc++.h>
using namespace std;

int n;
int record_state[10][5];
int pwd[5];

bool can_change_to_record(int row) {
    int diff[5];
    int non_zero = 0;
    for (int i = 0; i < 5; i++) {
        diff[i] = (record_state[row][i] - pwd[i] + 10) % 10;
        if (diff[i] != 0) {
            non_zero++;
        }
    }

    // 情况 1：只转动一个拨圈。
    if (non_zero == 1) {
        return true;
    }

    // 情况 2：同时转动两个相邻拨圈，且幅度相同。
    if (non_zero == 2) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> record_state[i][j];
        }
    }

    int answer = 0;
    for (int x = 0; x < 100000; x++) {
        int t = x;
        for (int i = 4; i >= 0; i--) {
            pwd[i] = t % 10;
            t /= 10;
        }
        if (check_password()) {
            answer++;
        }
    }

    cout << answer << '\n';
    return 0;
}
