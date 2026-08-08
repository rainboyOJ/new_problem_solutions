#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

static int n, m;
static vector<string> grid;

bool ok(int row, int l, int r) {
    for (int i = l; i <= r; ++i) {
        if (grid[row][i] == 'X') {
            return false;
        }
    }
    return true;
}

int dfs(int row, int l, int r) {
    if (row > n) {
        return 1;
    }

    long long ways = 1; // 从这一层开始不再继续放。

    for (int nl = l; nl <= r; ++nl) {
        for (int nr = nl; nr <= r; ++nr) {
            if (!ok(row, nl, nr)) {
                continue;
            }
            ways += dfs(row + 1, nl, nr);
        }
    }

    return ways % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    grid.assign(n + 1, string(m + 1, '.'));
    vector<string> rows(n + 1);
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        rows[i] = s;
    }
    for (int i = 1; i <= n; ++i) {
        string s = rows[n - i + 1];
        for (int j = 1; j <= m; ++j) {
            grid[i][j] = s[j - 1];
        }
    }

    cout << dfs(1, 1, m) % MOD << '\n';
    return 0;
}
