#include <bits/stdc++.h>
using namespace std;

int n;
string s1, s2, s3;
int value_of[26];    // 每个字母对应的数字，-1 表示还未确定
int used_digit[26];  // 某个数字是否已经被使用
int order_list[26];  // 搜索字母的顺序
int order_cnt;
int answer[26];
bool solved = false;

void save_answer() {
    for (int i = 0; i < n; i++) {
        answer[i] = value_of[i];
    }
}

// 检查当前已经赋值的一部分，是否仍然可能扩展成合法解。
bool check_partial() {
    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int a = value_of[s1[i] - 'A'];
        int b = value_of[s2[i] - 'A'];
        int c = value_of[s3[i] - 'A'];

        if (a != -1 && b != -1 && c != -1) {
            int sum = a + b + carry;
            if (sum % n != c) {
                return false;
            }
            carry = sum / n;
            continue;
        }

        // 当前列还没完全确定，但如果前两项和结果都已经知道，也可以继续推进进位。
        if (a != -1 && b != -1 && c == -1) {
            int sum = a + b + carry;
            int need = sum % n;
            if (used_digit[need]) {
                return false;
            }
            carry = sum / n;
            continue;
        }

        // 如果当前列无法完全判断，就先停下，让更高位以后再说。
        break;
    }

    return true;
}

void dfs(int idx) {
    if (solved) {
        return;
    }

    if (idx == order_cnt) {
        int carry = 0;
        for (int i = n - 1; i >= 0; i--) {
            int a = value_of[s1[i] - 'A'];
            int b = value_of[s2[i] - 'A'];
            int c = value_of[s3[i] - 'A'];
            int sum = a + b + carry;
            if (sum % n != c) {
                return;
            }
            carry = sum / n;
        }
        if (carry == 0) {
            save_answer();
            solved = true;
        }
        return;
    }

    int ch = order_list[idx];

    for (int digit = n - 1; digit >= 0; digit--) {
        if (used_digit[digit]) {
            continue;
        }

        value_of[ch] = digit;
        used_digit[digit] = 1;

        if (check_partial()) {
            dfs(idx + 1);
        }

        used_digit[digit] = 0;
        value_of[ch] = -1;

        if (solved) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s1 >> s2 >> s3;

    memset(used_digit, 0, sizeof(used_digit));
    for (int i = 0; i < 26; i++) {
        value_of[i] = -1;
        answer[i] = -1;
    }

    // 从低位到高位收集字母，优先搜索出现在低位的字母。
    bool in_order[26];
    memset(in_order, 0, sizeof(in_order));

    for (int i = n - 1; i >= 0; i--) {
        int x = s1[i] - 'A';
        int y = s2[i] - 'A';
        int z = s3[i] - 'A';

        if (!in_order[x]) {
            in_order[x] = true;
            order_list[order_cnt++] = x;
        }
        if (!in_order[y]) {
            in_order[y] = true;
            order_list[order_cnt++] = y;
        }
        if (!in_order[z]) {
            in_order[z] = true;
            order_list[order_cnt++] = z;
        }
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
