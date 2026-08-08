#include <bits/stdc++.h>
using namespace std;

string s, t;

bool all_nine(const string &str) {
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] != '9') {
            return false;
        }
    }
    return true;
}

// 把左半边镜像到右半边，生成一个回文串。
void make_palindrome(string &str) {
    int len = str.size();
    for (int i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    // 全是 9 时，答案一定是 100...001。
    if (all_nine(s)) {
        cout << '1';
        for (int i = 1; i < (int)s.size(); i++) {
            cout << '0';
        }
        cout << '1' << '\n';
        return 0;
    }

    t = s;
    make_palindrome(t);

    // 直接镜像后已经比原数大，就是最小答案。
    if (t > s) {
        cout << t << '\n';
        return 0;
    }

    // 否则需要把中间这一位（或左中位）往前进位，
    // 再重新镜像一次。
    int pos = ((int)t.size() - 1) / 2;
    while (pos >= 0 && t[pos] == '9') {
        t[pos] = '0';
        pos--;
    }
    t[pos]++;

    make_palindrome(t);
    cout << t << '\n';

    return 0;
}
