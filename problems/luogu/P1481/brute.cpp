#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力枚举所有可能的词链，只适合小数据对拍和教学。

const int MAXN = 25;

int n;
string s[MAXN];

bool is_prefix(const string &a, const string &b) {
    if ((int)a.size() >= (int)b.size()) {
        return false;
    }
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int dfs(int last) {
    int best = 1;

    for (int i = last + 1; i <= n; i++) {
        if (is_prefix(s[last], s[i])) {
            best = max(best, 1 + dfs(i));
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dfs(i));
    }

    cout << ans << '\n';
    return 0;
}
