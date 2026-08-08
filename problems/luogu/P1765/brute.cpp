// brute.cpp：直接按手机键盘分组逐字符统计按键次数。
#include <bits/stdc++.h>
using namespace std;

string s;

int get_cost(char ch) {
    if (ch == ' ') {
        return 1;
    }
    string groups[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (int) groups[i].size(); j++) {
            if (groups[i][j] == ch) {
                return j + 1;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);

    int ans = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        ans += get_cost(s[i]);
    }

    cout << ans << '\n';
    return 0;
}
