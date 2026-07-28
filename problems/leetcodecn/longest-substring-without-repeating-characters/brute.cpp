/**
 * Author by Rainboy
 */
// brute.cpp：检查所有子串 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            set<char> st;
            for (int j = i; j < n; j++) {
                if (st.count(s[j])) break;
                st.insert(s[j]);
                ans = max(ans, j - i + 1);
            }
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
