#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int T;
int n;
int a[MAXN][MAXN];
int used_col[MAXN];

// 朴素搜索：按行依次决定，这一行到底选哪一列的黑格。
// 只要能给每一行都选到一个互不冲突的黑格，就说明答案是 Yes。
bool dfs(int row) {
    if (row > n) {
        return true;
    }

    for (int col = 1; col <= n; col++) {
        if (a[row][col] == 0 || used_col[col]) {
            continue;
        }
        used_col[col] = 1;
        if (dfs(row + 1)) {
            return true;
        }
        used_col[col] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }

        memset(used_col, 0, sizeof(used_col));
        if (dfs(1)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
