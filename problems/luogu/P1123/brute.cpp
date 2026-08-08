// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int T;
int n, m;
long long a[MAXN][MAXN];  // 棋盘权值
int chosen[MAXN][MAXN];   // 是否已经选择这个格子
long long ans;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool can_take(int x, int y) {
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && chosen[nx][ny]) {
            return false;
        }
    }
    return true;
}

void dfs(int pos, long long sum) {
    if (pos > n * m) {
        ans = max(ans, sum);
        return;
    }

    int x = (pos - 1) / m + 1;
    int y = (pos - 1) % m + 1;

    // 不选当前格子。
    dfs(pos + 1, sum);

    // 只有和已选格子都不相邻时，才能选当前格子。
    if (can_take(x, y)) {
        chosen[x][y] = 1;
        dfs(pos + 1, sum + a[x][y]);
        chosen[x][y] = 0;
    }
}

long long solve_one_case() {
    memset(chosen, 0, sizeof(chosen));
    ans = 0;
    dfs(1, 0);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        cout << solve_one_case() << '\n';
    }

    return 0;
}
