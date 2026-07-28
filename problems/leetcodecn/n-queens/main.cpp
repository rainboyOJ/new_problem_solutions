#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> col(n), diag1(2*n-1), diag2(2*n-1);
        vector<string> board(n, string(n, '.'));
        function<void(int)> dfs = [&](int r) {
            if (r == n) { ans.push_back(board); return; }
            for (int c = 0; c < n; c++) {
                int d1 = r + c, d2 = r - c + n - 1;
                if (col[c] || diag1[d1] || diag2[d2]) continue;
                col[c] = diag1[d1] = diag2[d2] = 1;
                board[r][c] = 'Q';
                dfs(r+1);
                board[r][c] = '.';
                col[c] = diag1[d1] = diag2[d2] = 0;
            }
        };
        dfs(0);
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (auto& v : Solution().solveNQueens(n)) { for (auto& s : v) cout << s << '\n'; cout << '\n'; }
    return 0;
}
