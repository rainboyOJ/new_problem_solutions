// brute.cpp：小数据朴素解，按整数/小数/分数/百分数四类分别反转。
#include <bits/stdc++.h>
using namespace std;

string trim_left_zero(string s) {
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') {
        i++;
    }
    return s.substr(i);
}

string trim_right_zero(string s) {
    while ((int)s.size() > 1 && s.back() == '0') {
        s.pop_back();
    }
    return s;
}

string rev_int(string s) {
    reverse(s.begin(), s.end());
    return trim_left_zero(s);
}

string rev_frac(string s) {
    reverse(s.begin(), s.end());
    return trim_right_zero(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') {
            cout << rev_int(s.substr(0, i)) << '.' << rev_frac(s.substr(i + 1)) << '\n';
            return 0;
        }
        if (s[i] == '/') {
            cout << rev_int(s.substr(0, i)) << '/' << rev_int(s.substr(i + 1)) << '\n';
            return 0;
        }
        if (s[i] == '%') {
            cout << rev_int(s.substr(0, i)) << "%\n";
            return 0;
        }
    }
    cout << rev_int(s) << '\n';
    return 0;
}
