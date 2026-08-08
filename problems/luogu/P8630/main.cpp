#include <bits/stdc++.h>
using namespace std;

string s;
int n;

// 把 26 个字母出现次数拼成一个字符串签名，方便放进 map。
string build_key(const int cnt[]) {
    string key;
    for (int i = 0; i < 26; i++) {
        key += to_string(cnt[i]);
        key += '#';
    }
    return key;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cin >> n;

    map<string, int> mp;
    int cnt[26] = {0};

    for (int i = 0; i < (int) s.size(); i++) {
        cnt[s[i] - 'a']++;
        if (i >= 8) {
            cnt[s[i - 8] - 'a']--;
        }
        if (i >= 7) {
            mp[build_key(cnt)]++;
        }
    }

    long long ans = 0;
    while (n--) {
        string t;
        cin >> t;
        int need[26] = {0};
        for (int i = 0; i < 8; i++) {
            need[t[i] - 'a']++;
        }
        ans += mp[build_key(need)];
    }

    cout << ans << '\n';
    return 0;
}
