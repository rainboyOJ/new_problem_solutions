// brute.cpp：搜索所有从 1 号站到 n 号站的租船方案，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int INF = 1e9;

int n;
int cost_days[MAXN][MAXN];
int ans = INF;

void dfs(int x, int sum) {
    if (sum >= ans) {
        return;
    }
    if (x == n) {
        ans = min(ans, sum);
        return;
    }

    for (int y = x + 1; y <= n; y++) {
        dfs(y, sum + cost_days[x][y]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> cost_days[i][j];
        }
    }

    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}
