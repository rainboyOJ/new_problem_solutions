#include <bits/stdc++.h>
using namespace std;

int p1, p2, p3;
string s;

bool is_lower_letter(char ch) {
    return ch >= 'a' && ch <= 'z';
}

bool is_digit_char(char ch) {
    return ch >= '0' && ch <= '9';
}

bool can_expand(char left_ch, char right_ch) {
    bool both_letters = is_lower_letter(left_ch) && is_lower_letter(right_ch);
    bool both_digits = is_digit_char(left_ch) && is_digit_char(right_ch);

    if (!both_letters && !both_digits) {
        return false;
    }
    if (right_ch <= left_ch) {
        return false;
    }
    return true;
}

char convert_char(char ch) {
    if (p1 == 3) {
        return '*';
    }
    if (p1 == 2 && is_lower_letter(ch)) {
        return char(ch - 'a' + 'A');
    }
    return ch;
}

void append_expand(string &ans, char left_ch, char right_ch) {
    if (right_ch == left_ch + 1) {
        return;
    }

    if (p3 == 1) {
        for (int code = left_ch + 1; code <= right_ch - 1; code++) {
            char out_ch = convert_char(char(code));
            for (int k = 1; k <= p2; k++) {
                ans += out_ch;
            }
        }
    }
    else {
        for (int code = right_ch - 1; code >= left_ch + 1; code--) {
            char out_ch = convert_char(char(code));
            for (int k = 1; k <= p2; k++) {
                ans += out_ch;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p1 >> p2 >> p3;
    cin >> s;

    string ans;
    int len = (int) s.size();

    for (int i = 0; i < len; i++) {
        if (s[i] != '-') {
            ans += s[i];
            continue;
        }

        if (i == 0 || i == len - 1) {
            ans += '-';
            continue;
        }

        char left_ch = s[i - 1];
        char right_ch = s[i + 1];

        if (!can_expand(left_ch, right_ch)) {
            ans += '-';
            continue;
        }

        append_expand(ans, left_ch, right_ch);
    }

    cout << ans << '\n';
    return 0;
}
