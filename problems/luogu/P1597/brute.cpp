// brute.cpp：直接按题意一条一条执行赋值语句。
#include <bits/stdc++.h>
using namespace std;

string s;
int val[3];

int get_value(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    return val[ch - 'a'];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    memset(val, 0, sizeof(val));

    for (int i = 0; i < (int) s.size(); i += 5) {
        char left = s[i];
        char right = s[i + 3];
        val[left - 'a'] = get_value(right);
    }

    cout << val[0] << ' ' << val[1] << ' ' << val[2] << '\n';
    return 0;
}
