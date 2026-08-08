#include <bits/stdc++.h>
using namespace std;

static string s;

int dfs(int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == r) {
        return 1;
    }

    int best = dfs(l + 1, r) + 1;

    // 暴力枚举 s[l] 想和后面哪个相同字符共用一次涂色。
    for (int k = l + 1; k <= r; ++k) {
        if (s[k] != s[l]) {
            continue;
        }
        int left = dfs(l + 1, k - 1);
        int right = dfs(k, r);
        best = min(best, left + right);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cout << dfs(0, (int)s.size() - 1) << '\n';
    return 0;
}
