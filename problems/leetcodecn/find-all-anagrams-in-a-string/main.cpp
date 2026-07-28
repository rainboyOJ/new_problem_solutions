/**
 * Author by Rainboy
 */
// main.cpp：滑动窗口维护 26 维计数，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        if (n < m) return {};
        array<int, 26> cnt = {};
        for (char ch : p) cnt[ch - 'a']++;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a']--;
            if (i >= m) cnt[s[i - m] - 'a']++;
            if (i >= m - 1) {
                bool ok = true;
                for (int x : cnt) if (x) { ok = false; break; }
                if (ok) ans.push_back(i - m + 1);
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s, p; cin >> s >> p;
    auto v = Solution().findAnagrams(s, p);
    for (int x : v) cout << x << ' ';
    return 0;
}
