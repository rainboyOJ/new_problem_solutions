// brute.cpp：逐字符扫描每一行，识别其中的整数并求和，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

bool is_digit_char(char ch) {
    return ch >= '0' && ch <= '9';
}

// 只有“-后面紧跟数字，且前面不是数字”时，才把它看成负号。
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
