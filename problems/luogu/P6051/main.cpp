#include <bits/stdc++.h>
using namespace std;

bool is_digit_char(char ch) {
    return ch >= '0' && ch <= '9';
}

bool is_negative_sign(const string &s, int i) {
    if (s[i] != '-') {
        return false;
    }
    if (i + 1 >= (int) s.size() || !is_digit_char(s[i + 1])) {
        return false;
    }
    if (i > 0 && is_digit_char(s[i - 1])) {
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        long long sum = 0;
        bool has_number = false;
        int n = (int) line.size();
        int i = 0;

        while (i < n) {
            if (is_digit_char(line[i]) || is_negative_sign(line, i)) {
                int sign = 1;
                if (line[i] == '-') {
                    sign = -1;
                    i++;
                }

                long long value = 0;
                while (i < n && is_digit_char(line[i])) {
                    value = value * 10 + (line[i] - '0');
                    i++;
                }

                sum += sign * value;
                has_number = true;
            }
            else {
                i++;
            }
        }

        if (has_number) {
            cout << sum << '\n';
        }
    }

    return 0;
}
