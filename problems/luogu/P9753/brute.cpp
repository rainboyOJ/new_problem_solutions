/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:36
 * update_at: 2026-10-01 22:36
 */
// brute.cpp：小数据暴力解，枚举所有子串并用栈模拟相邻相同字符的消除。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 暴力只服务小数据，n 取到 100 左右

int n;
string s;

// 判断 s[left..right] 能否被完全消除：扫描一遍，栈顶与当前字符相同就弹栈。
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

    // 依次枚举所有非空连续子串，能消除就计数。
    ll answer = 0;
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
