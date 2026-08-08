// brute_01_style.cpp：按位构造写法，把每一位放哪个数字看成一层决策。
#include <bits/stdc++.h>
using namespace std;

int cost_digit[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int total_len;
string answer;

// 判断剩余 rest 根火柴能否填满 slots 个数位。
bool can_fill(int rest, int slots) {
    if (rest < 0) {
        return false;
    }
    return 2 * slots <= rest && rest <= 7 * slots;
}

bool dfs_build(int pos, int rest) {
    if (pos == total_len) {
        return rest == 0;
    }

    int slots_left = total_len - pos - 1;
    int start_digit = (pos == 0 ? 1 : 0);

    // 从小到大尝试数字，第一次成功就是当前长度下的最小数。
    for (int d = start_digit; d <= 9; d++) {
        int left = rest - cost_digit[d];
        if (!can_fill(left, slots_left)) {
            continue;
        }
        answer[pos] = char('0' + d);
        if (dfs_build(pos + 1, left)) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        if (n == 1) {
            cout << -1 << '\n';
            continue;
        }

        total_len = (n + 6) / 7; // 位数越少，正整数越小。
        answer.assign(total_len, '0');

        if (dfs_build(0, n)) {
            cout << answer << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
