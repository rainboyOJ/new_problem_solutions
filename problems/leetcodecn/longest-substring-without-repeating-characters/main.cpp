/**
 * Author by Rainboy
 */
// main.cpp：滑动窗口，char->last_pos 跳跃，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int last[128] = {}, l = 0, ans = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            l = max(l, last[s[r]]);
            ans = max(ans, r - l + 1);
            last[s[r]] = r + 1;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; cin >> s;
    cout << Solution().lengthOfLongestSubstring(s) << '\n';
    return 0;
}
