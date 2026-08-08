// brute.cpp：搜索所有从顶部到底部的路径，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n;
int a[MAXN][MAXN];
int ans;

void dfs(int x, int y, int sum) {
    sum += a[x][y];
    if (x == n) {
        ans = max(ans, sum);
        return;
    }

    dfs(x + 1, y, sum);
    dfs(x + 1, y + 1, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    dfs(1, 1, 0);
    cout << ans << '\n';
    return 0;
}
