// brute.cpp：小数据暴力解，枚举所有子串并用栈模拟相邻相同字符消除。
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool can_delete(int left, int right) {
    string st;
    for (int i = left; i <= right; i++) {
        if (!st.empty() && st.back() == s[i]) {
            st.pop_back();
        } else {
            st.push_back(s[i]);
        }
    }
    return st.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    long long answer = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            if (can_delete(l, r)) {
                answer++;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
