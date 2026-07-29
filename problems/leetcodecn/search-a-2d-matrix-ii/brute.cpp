/**
 * Author by Rainboy
 */
// brute.cpp：全矩阵扫描 O(mn)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        for (auto &row : matrix)
            for (int x : row)
                if (x == target)
                    return true;
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, t;
    cin >> m >> n >> t;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    cout << Solution().searchMatrix(a, t) << '\n';
    return 0;
}
