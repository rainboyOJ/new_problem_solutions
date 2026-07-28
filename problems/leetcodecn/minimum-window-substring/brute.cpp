/**
 * Author by Rainboy
 */
// brute.cpp：枚举所有窗口 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        if (n < m) return "";
        string ans;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                string sub = s.substr(i, j - i + 1);
                vector<int> cnt(128);
                for (char ch : sub) cnt[ch]++;
                bool ok = true;
                for (char ch : t) if (--cnt[ch] < 0) { ok = false; break; }
                if (ok && (ans.empty() || (int)sub.size() < (int)ans.size()))
                    ans = sub;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s, t; cin >> s >> t;
    cout << Solution().minWindow(s, t) << '\n';
    return 0;
}
