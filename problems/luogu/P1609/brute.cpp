#include <bits/stdc++.h>
using namespace std;

string s;

bool is_palindrome(const string &str) {
    int len = str.size();
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 字符串形式加一，适合小数据暴力。
void add_one(string &str) {
    int pos = str.size() - 1;
    while (pos >= 0 && str[pos] == '9') {
        str[pos] = '0';
        pos--;
    }

    if (pos >= 0) {
        str[pos]++;
    } else {
        str = "1" + str;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    // brute.cpp：不断把数字加一，直到遇到下一个回文数。
    // 这个做法很直观，但只适合小数据验证。
    do {
        add_one(s);
    } while (!is_palindrome(s));

    cout << s << '\n';

    return 0;
}
