#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<bool> dp(n + 1, false);
        // dp[i] 表示前缀 s[0..i) 能否被字典中的单词完整拆分。
        dp[0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
        return dp[n];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int m;
    cin >> s >> m;
    vector<string> dict(m);
    for (auto &x : dict)
        cin >> x;
    cout << Solution().wordBreak(s, dict) << '\n';
    return 0;
}
