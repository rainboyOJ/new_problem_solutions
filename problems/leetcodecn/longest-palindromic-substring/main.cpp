#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), start = 0, len = 0;
        auto expand = [&](int l, int r) {
            while (l >= 0 && r < n && s[l] == s[r]) {
                l--;
                r++;
            }
            if (r - l - 1 > len) {
                start = l + 1;
                len = r - l - 1;
            }
        };
        for (int i = 0; i < n; i++) {
            expand(i, i);
            expand(i, i + 1);
        }
        return s.substr(start, len);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    cout << Solution().longestPalindrome(s) << '\n';
    return 0;
}
