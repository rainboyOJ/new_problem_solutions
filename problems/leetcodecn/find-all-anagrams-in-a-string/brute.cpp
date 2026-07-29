/**
 * Author by Rainboy
 */
// brute.cpp：排序每个窗口 O(n * k log k)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        if (n < m)
            return {};
        string key = p;
        sort(key.begin(), key.end());
        vector<int> ans;
        for (int i = 0; i + m <= n; i++) {
            string sub = s.substr(i, m);
            sort(sub.begin(), sub.end());
            if (sub == key)
                ans.push_back(i);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, p;
    cin >> s >> p;
    auto v = Solution().findAnagrams(s, p);
    for (int x : v)
        cout << x << ' ';
    return 0;
}
