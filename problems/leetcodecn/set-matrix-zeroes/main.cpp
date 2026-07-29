/**
 * Author by Rainboy
 */
// main.cpp：用首行/首列充当标记，O(1) 额外空间。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool row0 = false, col0 = false;
        for (int j = 0; j < n; j++)
            if (matrix[0][j] == 0)
                row0 = true;
        for (int i = 0; i < m; i++)
            if (matrix[i][0] == 0)
                col0 = true;
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
        if (row0)
            for (int j = 0; j < n; j++)
                matrix[0][j] = 0;
        if (col0)
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    Solution().setZeroes(a);
    for (auto &row : a) {
        for (int x : row)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
