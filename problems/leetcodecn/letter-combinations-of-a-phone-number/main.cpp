#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};
        vector<string> m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        string cur;
        function<void(int)> dfs = [&](int i) {
            if (i == (int)digits.size()) {
                ans.push_back(cur);
                return;
            }
            for (char ch : m[digits[i] - '0']) {
                cur.push_back(ch);
                dfs(i + 1);
                cur.pop_back();
            }
        };
        dfs(0);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    for (auto &x : Solution().letterCombinations(s))
        cout << x << ' ';
    return 0;
}
