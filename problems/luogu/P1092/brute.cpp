#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据全排列解。
// 直接把 A.. 对应的数字全部枚举出来，最后检查整道 n 进制加法是否成立。
// 这个版本最直观，但复杂度是 n!，只适合很小的数据验证。

int n;
string a, b, c;
int value_of[26];
int used_digit[26];
int answer[26];
bool solved = false;

bool check_full() {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int x = value_of[a[i] - 'A'];
        int y = value_of[b[i] - 'A'];
        int z = value_of[c[i] - 'A'];

        int sum = x + y + carry;
        if (sum % n != z) {
            return false;
        }
        carry = sum / n;
    }

    return carry == 0;
}

void save_answer() {
    for (int i = 0; i < n; i++) {
        answer[i] = value_of[i];
    }
}

void dfs(int idx) {
    if (solved) {
        return;
    }

    if (idx == n) {
        if (check_full()) {
            save_answer();
            solved = true;
        }
        return;
    }

    for (int digit = 0; digit < n; digit++) {
        if (used_digit[digit]) {
            continue;
        }
        value_of[idx] = digit;
        used_digit[digit] = 1;
        dfs(idx + 1);
        used_digit[digit] = 0;
        value_of[idx] = -1;
        if (solved) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b >> c;

    memset(used_digit, 0, sizeof(used_digit));
    for (int i = 0; i < 26; i++) {
        value_of[i] = -1;
        answer[i] = -1;
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
