// brute.cpp：小数据暴力解，递归枚举每一行的皇后放在哪一列。
#include <bits/stdc++.h>
using namespace std;

int n;
int place[10]; // place[r] = c 表示第 r 行皇后在第 c 列
vector<vector<string>> ans;

bool check() {
    for (int r1 = 0; r1 < n; r1++)
        for (int r2 = r1 + 1; r2 < n; r2++)
            if (place[r1] == place[r2] || abs(place[r1] - place[r2]) == r2 - r1)
                return false;
    return true;
}

void dfs(int r) {
    if (r == n) {
        if (check()) {
            vector<string> board(n, string(n, '.'));
            for (int i = 0; i < n; i++)
                board[i][place[i]] = 'Q';
            ans.push_back(board);
        }
        return;
    }
    for (int c = 0; c < n; c++) {
        place[r] = c;
        dfs(r + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    dfs(0);
    for (auto &v : ans) {
        for (auto &s : v)
            cout << s << '\n';
        cout << '\n';
    }
    return 0;
}
