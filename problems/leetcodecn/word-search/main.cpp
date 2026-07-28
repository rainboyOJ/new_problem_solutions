#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        function<bool(int,int,int)> dfs = [&](int i, int j, int idx) {
            if (idx == (int)word.size()) return true;
            if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[idx]) return false;
            char tmp = board[i][j]; board[i][j] = '#';
            bool ok = dfs(i-1,j,idx+1) || dfs(i+1,j,idx+1) || dfs(i,j-1,idx+1) || dfs(i,j+1,idx+1);
            board[i][j] = tmp;
            return ok;
        };
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (dfs(i,j,0)) return true;
        return false;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<char>> b(m, vector<char>(n));
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> b[i][j];
    string w; cin >> w;
    cout << Solution().exist(b, w) << '\n';
    return 0;
}
