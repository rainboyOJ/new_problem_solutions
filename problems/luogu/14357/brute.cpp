// brute.cpp：小数据暴力解，枚举选择哪些数字，再排序成最大数字。
#include <bits/stdc++.h>
using namespace std;

bool better(const string &a, const string &b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string digits = "";
    for (int i = 0; i < (int)s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            digits += s[i];
        }
    }

    int n = (int)digits.size();
    string best = "";

    for (int mask = 1; mask < (1 << n); mask++) {
        string cur = "";
        bool has_non_zero = false;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) != 0) {
                cur += digits[i];
                if (digits[i] != '0') {
                    has_non_zero = true;
                }
            }
        }
        if (!has_non_zero) {
            continue;
        }
        sort(cur.begin(), cur.end(), greater<char>());
        if (better(cur, best)) {
            best = cur;
        }
    }

    cout << best << '\n';
    return 0;
}
