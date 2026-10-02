/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:41
 * update_at: 2026-10-01 22:41
 */
// main.cpp：枚举所有 5 位密码，检查它能否一次操作变成每个记录状态。
// 核心思路：对每个候选密码，逐条验证它能否通过一次操作（转一个拨圈或两个相邻同幅度）到达记录状态。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;                 // 记录状态数（≤ 8）
int record_state[10][5]; // 记录状态，每行 5 位数字（0-9，int 足够）
int pwd[5];           // 当前候选密码

// 判断当前密码 pwd 能否通过一次操作变成 record_state[row]。
// 一次操作 = 转一个拨圈（任意幅度），或同时转两个相邻拨圈（幅度相同）。
bool can_change_to_record(int row) {
    int diff[5]; // 每个拨圈需要转动的幅度（0-9）
    int non_zero = 0;
    for (int i = 0; i < 5; i++) {
        diff[i] = (record_state[row][i] - pwd[i] + 10) % 10;
        if (diff[i] != 0) {
            non_zero++;
        }
    }

    // 情况 1：只转动一个拨圈（任意幅度）。
    if (non_zero == 1) {
        return true;
    }

    // 情况 2：同时转动两个相邻拨圈，且幅度相同。
    if (non_zero == 2) {
        for (int i = 0; i + 1 < 5; i++) {
            if (diff[i] != 0 && diff[i] == diff[i + 1]) {
                // 确认只有这两个位置有差异。
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

// 检查当前密码能否一次操作变成所有 n 个记录状态。
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

    // 枚举所有 5 位密码（00000 ~ 99999）。
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
