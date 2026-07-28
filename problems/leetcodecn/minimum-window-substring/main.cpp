/**
 * Author by Rainboy
 */
// main.cpp：滑动窗口 + need/have 计数，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int cnt[128] = {}, need = 0;
        for (char ch : t) { if (cnt[ch] == 0) need++; cnt[ch]++; }
        int l = 0, have = 0, start = 0, len = INT_MAX;
        for (int r = 0; r < (int)s.size(); r++) {
            if (--cnt[s[r]] == 0) have++;
            while (have == need) {
                if (r - l + 1 < len) { len = r - l + 1; start = l; }
                if (++cnt[s[l]] > 0) have--;
                l++;
            }
        }
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s, t; cin >> s >> t;
    cout << Solution().minWindow(s, t) << '\n';
    return 0;
}
