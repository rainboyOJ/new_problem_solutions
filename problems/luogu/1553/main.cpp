#include <bits/stdc++.h>
using namespace std;

string reverse_integer_part(string s) {
    reverse(s.begin(), s.end());
    int pos = 0;
    while (pos + 1 < (int)s.size() && s[pos] == '0') {
        pos++;
    }
    return s.substr(pos);
}

string reverse_decimal_part(string s) {
    reverse(s.begin(), s.end());
    while ((int)s.size() > 1 && s.back() == '0') {
        s.pop_back();
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int dot = (int)s.find('.');
    int slash = (int)s.find('/');
    int percent = (int)s.find('%');

    if (dot != (int)string::npos) {
        string left = s.substr(0, dot);
        string right = s.substr(dot + 1);
        cout << reverse_integer_part(left) << '.' << reverse_decimal_part(right) << '\n';
    } else if (slash != (int)string::npos) {
        string left = s.substr(0, slash);
        string right = s.substr(slash + 1);
        cout << reverse_integer_part(left) << '/' << reverse_integer_part(right) << '\n';
    } else if (percent != (int)string::npos) {
        string number = s.substr(0, percent);
        cout << reverse_integer_part(number) << "%\n";
    } else {
        cout << reverse_integer_part(s) << '\n';
    }
    return 0;
}
