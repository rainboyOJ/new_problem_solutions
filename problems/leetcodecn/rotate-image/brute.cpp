/**
 * Author by Rainboy
 */
// brute.cpp：额外矩阵 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        auto copy = matrix;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[j][n - 1 - i] = copy[i][j];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    Solution().rotate(a);
    for (auto& row : a) {
        for (int x : row) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
