// brute.cpp：小数据暴力搜索，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, k;
long long a[MAXN][MAXN];
long long best_ans;

void dfs(int x, int y, int used, long long sum) {
    // 当前点不用三倍经验。
    long long sum1 = sum + a[x][y];
    if (x == n) {
        best_ans = max(best_ans, sum1);
    }
    else {
        dfs(x + 1, y, used, sum1);
        dfs(x + 1, y + 1, used, sum1);
    }

    // 当前点使用一次三倍经验。
    if (used < k) {
        long long sum2 = sum + a[x][y] * 3;
        if (x == n) {
            best_ans = max(best_ans, sum2);
        }
        else {
            dfs(x + 1, y, used + 1, sum2);
            dfs(x + 1, y + 1, used + 1, sum2);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    k = min(k, n);
    best_ans = -(1LL << 60);
    dfs(1, 1, 0, 0);

    cout << best_ans << '\n';
    return 0;
}
