#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
string s;
int pref[6][MAXN];

// 3 个字母的 6 种全排列模式串基底
const string perms[6] = {
    "abc",
    "acb",
    "bac",
    "bca",
    "cab",
    "cba"
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> s)) return 0;

    // 预处理 6 种模式串的前缀差异数组
    for (int p = 0; p < 6; p++) {
        for (int i = 0; i < n; i++) {
            char target = perms[p][i % 3];
            pref[p][i + 1] = pref[p][i] + (s[i] != target);
        }
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        int ans = r - l + 1; // 上界为全部替换
        for (int p = 0; p < 6; p++) {
            ans = min(ans, pref[p][r] - pref[p][l - 1]);
        }
        cout << ans << "\n";
    }

    return 0;
}
