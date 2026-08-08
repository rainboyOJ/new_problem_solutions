#include <bits/stdc++.h>
using namespace std;

int cost_digit[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

bool can_fill(int rest, int slots) {
    return 2 * slots <= rest && rest <= 7 * slots;
}

char choose_digit(int rest, int slots, bool first_digit) {
    int start = first_digit ? 1 : 0;
    for (int d = start; d <= 9; d++) {
        int left = rest - cost_digit[d];
        if (can_fill(left, slots - 1)) {
            return char('0' + d);
        }
    }
    return '?';
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

        int len = (n + 6) / 7; // 位数越少，正整数越小
        int rest = n;

        for (int pos = 1; pos <= len; pos++) {
            char ch = choose_digit(rest, len - pos + 1, pos == 1);
            cout << ch;
            rest -= cost_digit[ch - '0'];
        }
        cout << '\n';
    }

    return 0;
}
