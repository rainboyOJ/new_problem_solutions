// brute.cpp：小数据朴素解，用栈检查每个右括号是否有左括号匹配。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<char> st;
    bool ok = true;
    for (int i = 0; i < (int)s.size() && s[i] != '@'; i++) {
        if (s[i] == '(') {
            st.push_back(s[i]);
        } else if (s[i] == ')') {
            if (st.empty()) {
                ok = false;
            } else {
                st.pop_back();
            }
        }
    }
    if (!st.empty()) {
        ok = false;
    }

    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}
