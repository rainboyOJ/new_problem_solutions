/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:41
 * update_at: 2026-10-01 22:41
 */
// brute.cpp：小数据暴力解，把 5 个密码位看成选择序列，递归枚举每一位填 0..9。
// 与 main.cpp 的迭代枚举等价，写法更贴近 01 序列递归教学风格。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
int record_state[10][5];
int pwd[5];
int answer;

// 判断当前密码 pwd 能否通过一次操作变成 record_state[row]。
bool can_change_to_record(int row) {
    int diff[5];
    int non_zero = 0;
    for (int i = 0; i < 5; i++) {
        diff[i] = (record_state[row][i] - pwd[i] + 10) % 10;
        if (diff[i] != 0) {
            non_zero++;
        }
    }

    // 只转一个拨圈。
    if (non_zero == 1) {
        return true;
    }
    if (non_zero != 2) {
        return false;
    }

    // 同时转两个相邻拨圈，幅度相同。
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

// 检查当前密码能否一次操作变成所有 n 个记录状态。
bool check_password() {
    for (int i = 1; i <= n; i++) {
        if (!can_change_to_record(i)) {
            return false;
        }
    }
    return true;
}

// 递归枚举：这一层决定第 pos 位密码填哪个数字（0-9）。
void dfs_build(int pos) {
    if (pos == 5) {
        if (check_password()) {
            answer++;
        }
        return;
    }

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
