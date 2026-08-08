// brute.cpp：直接按题意计算 ISBN 的识别码并比较。
#include <bits/stdc++.h>
using namespace std;

string s;

char calc_check_digit() {
    int sum = 0;
    int pos = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        if (s[i] == '-') {
            continue;
        }
        if (pos <= 9) {
            sum += (s[i] - '0') * pos;
            pos++;
        }
    }

    int mod = sum % 11;
    if (mod == 10) {
        return 'X';
    }
    return char('0' + mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    char check = calc_check_digit();
    if (s.back() == check) {
        cout << "Right\n";
    }
    else {
        s.back() = check;
        cout << s << '\n';
    }

    return 0;
}
