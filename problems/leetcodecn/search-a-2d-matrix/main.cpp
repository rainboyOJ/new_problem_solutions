#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size(), l = 0, r = m*n - 1;
        while (l <= r) {
            int mid = (l+r)/2, val = matrix[mid/n][mid%n];
            if (val == target) return true;
            if (val < target) l = mid+1; else r = mid-1;
        }
        return false;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n, t; cin >> m >> n >> t;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
    cout << Solution().searchMatrix(a, t) << '\n';
    return 0;
}
