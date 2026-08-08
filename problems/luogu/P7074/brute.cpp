#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据 DFS 枚举所有合法路径，用来帮助理解题意和对拍。

const int MAXN = 8;
const long long NEG_INF = -(1LL << 60);

int n, m;
int a[MAXN][MAXN];
bool vis[MAXN][MAXN];
long long ans = NEG_INF;

int dx[3] = {-1, 1, 0};
int dy[3] = {0, 0, 1};

void dfs(int x, int y, long long sum) {
    if (x == n && y == m) {
        ans = max(ans, sum);
        return;
    }

    for (int k = 0; k < 3; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 1 || nx > n || ny < 1 || ny > m) {
            continue;
        }
        if (vis[nx][ny]) {
            continue;
        }

        vis[nx][ny] = true;
        dfs(nx, ny, sum + a[nx][ny]);
        vis[nx][ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    vis[1][1] = true;
    dfs(1, 1, a[1][1]);

    cout << ans << '\n';
    return 0;
}
