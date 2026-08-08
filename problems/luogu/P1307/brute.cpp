// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string s;

void solve() {
    bool neg = false;
    if (!s.empty() && s[0] == '-') {
        neg = true;
        s.erase(s.begin());
    }

    reverse(s.begin(), s.end());

    int p = 0;
    while (p + 1 < (int)s.size() && s[p] == '0') {
        p++;
    }

    if (neg) {
        cout << '-';
    }
    for (int i = p; i < (int)s.size(); i++) {
        cout << s[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    solve();

    return 0;
}
