/**
 * Author by Rainboy
 */
// brute.cpp = main.cpp（无更简单的基线）
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int t = 0, b = matrix.size() - 1, l = 0, r = matrix[0].size() - 1;
        vector<int> ans;
        while (t <= b && l <= r) {
            for (int j = l; j <= r; j++) ans.push_back(matrix[t][j]); t++;
            for (int i = t; i <= b; i++) ans.push_back(matrix[i][r]); r--;
            if (t <= b) for (int j = r; j >= l; j--) ans.push_back(matrix[b][j]); b--;
            if (l <= r) for (int i = b; i >= t; i--) ans.push_back(matrix[i][l]); l++;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    auto v = Solution().spiralOrder(a);
    for (int x : v) cout << x << ' ';
    return 0;
}
