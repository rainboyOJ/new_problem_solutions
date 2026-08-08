#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接保存所有模式串。
// 每次查询时暴力统计有多少个模式串以查询串作为前缀。

bool is_prefix(const string &pre, const string &s) {
    if ((int) pre.size() > (int) s.size()) {
        return false;
    }
    for (int i = 0; i < (int) pre.size(); i++) {
        if (pre[i] != s[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, q;
        cin >> n >> q;

        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        for (int i = 1; i <= q; i++) {
            string s;
            cin >> s;
            int ans = 0;
            for (int j = 0; j < n; j++) {
                if (is_prefix(s, a[j])) {
                    ans++;
                }
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
