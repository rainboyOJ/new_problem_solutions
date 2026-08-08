// brute.cpp：直接枚举每个长度为 8 的子串并比较计数，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string s;
int n;

bool same_count(const string &a, const string &b) {
    int c1[26] = {0};
    int c2[26] = {0};
    for (int i = 0; i < 8; i++) {
        c1[a[i] - 'a']++;
        c2[b[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (c1[i] != c2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cin >> n;

    long long ans = 0;
    while (n--) {
        string t;
        cin >> t;
        for (int i = 0; i + 7 < (int) s.size(); i++) {
            string sub = s.substr(i, 8);
            if (same_count(sub, t)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
