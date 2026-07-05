// brute_01_style.cpp：选择序列风格暴力，每一层递归决定下一步往哪个方向走。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
const long long NEG_INF = -(1LL << 60);

int n, m;
int a[MAXN][MAXN];
bool used[MAXN][MAXN];
long long answer = NEG_INF;

int dx[3] = {-1, 1, 0};
int dy[3] = {0, 0, 1};

void dfs(int dep, int x, int y, long long sum) {
    if (x == n && y == m) {
        answer = max(answer, sum);
        return;
    }

    // dep 表示已经走了多少步。每一层从 3 个方向中选择一个继续走。
    for (int choice = 0; choice < 3; choice++) {
        int nx = x + dx[choice];
        int ny = y + dy[choice];

        if (nx < 1 || nx > n || ny < 1 || ny > m) {
            continue;
        }
        if (used[nx][ny]) {
            continue;
        }

        used[nx][ny] = true;
        dfs(dep + 1, nx, ny, sum + a[nx][ny]);
        used[nx][ny] = false;
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

    used[1][1] = true;
    dfs(0, 1, 1, a[1][1]);

    cout << answer << '\n';
    return 0;
}
