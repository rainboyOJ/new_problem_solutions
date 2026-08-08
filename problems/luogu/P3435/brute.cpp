// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

// 判断前缀 s[1..len] 的前缀 s[1..period_len] 是否是一个合法 period。
bool is_period(int len, int period_len) {
    if (period_len <= 0 || period_len >= len) {
        return false;
    }
    for (int i = 1; i <= len; i++) {
        int pos = (i - 1) % period_len + 1;
        if (s[i] != s[pos]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;
    s = " " + s;

    long long ans = 0;

    for (int len = 1; len <= n; len++) {
        for (int period_len = len - 1; period_len >= 1; period_len--) {
            if (is_period(len, period_len)) {
                ans += period_len;
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
