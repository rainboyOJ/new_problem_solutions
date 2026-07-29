#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                pal[i][j] = (s[i] == s[j]) && (j - i < 2 || pal[i + 1][j - 1]);
        vector<vector<string>> ans;
        vector<string> cur;
        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                ans.push_back(cur);
                return;
            }
            for (int j = i; j < n; j++)
                if (pal[i][j]) {
                    cur.push_back(s.substr(i, j - i + 1));
                    dfs(j + 1);
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
    for (auto &v : Solution().partition(s)) {
        for (auto &x : v)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
