// brute.cpp：直接枚举重合长度并逐字符比较，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

string s, t;

bool same_suffix_prefix(const string &a, const string &b, int len) {
    int n = (int) a.size();
    for (int i = 0; i < len; i++) {
        if (a[n - len + i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> t;

    int ans = 0;
    int limit = min((int) s.size(), (int) t.size());

    for (int len = 1; len <= limit; len++) {
        if (same_suffix_prefix(s, t, len)) {
            ans = max(ans, len);
        }
        if (same_suffix_prefix(t, s, len)) {
            ans = max(ans, len);
        }
    }

    cout << ans << '\n';
    return 0;
}
