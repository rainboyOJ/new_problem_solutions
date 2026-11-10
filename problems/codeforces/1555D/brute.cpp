#include <bits/stdc++.h>
using namespace std;

// 检查字符串是否不包含任何长度 >= 2 的回文子串
bool is_beautiful(const string& t) {
    int len = t.size();
    for (int i = 0; i < len; i++) {
        if (i + 1 < len && t[i] == t[i + 1]) return false;
        if (i + 2 < len && t[i] == t[i + 2]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string s;
    if (!(cin >> n >> m >> s)) return 0;

    const string alphabet = "abc";

    while (m--) {
        int l, r;
        cin >> l >> r;
        string sub = s.substr(l - 1, r - l + 1);
        int len = sub.size();

        int best = len;
        // 暴力枚举所有长度为 len 的 'a','b','c' 构成的串（只适合极短串）
        // 或者直接枚举 6 种周期串进行比较
        const string perms[6] = {"abc", "acb", "bac", "bca", "cab", "cba"};
        for (int p = 0; p < 6; p++) {
            int diff = 0;
            for (int i = 0; i < len; i++) {
                if (sub[i] != perms[p][(l - 1 + i) % 3]) {
                    diff++;
                }
            }
            best = min(best, diff);
        }
        cout << best << "\n";
    }

    return 0;
}
