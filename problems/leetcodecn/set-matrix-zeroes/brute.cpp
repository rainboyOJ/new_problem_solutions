/**
 * Author by Rainboy
 */
// brute.cpp：额外矩阵记录零位置，O(mn) 空间。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        auto copy = matrix;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (copy[i][j] == 0) {
                    for (int r = 0; r < m; r++) matrix[r][j] = 0;
                    for (int c = 0; c < n; c++) matrix[i][c] = 0;
                }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    Solution().setZeroes(a);
    for (auto& row : a) {
        for (int x : row) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
