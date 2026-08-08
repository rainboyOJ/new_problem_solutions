#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 15;
const int MAXM = 15;
const i64 MOD = 998244353LL;

int n, m;
int a[MAXN][MAXM];
int cnt[MAXM];
i64 ans;

// 朴素暴力：
// 每种做法枚举“不选”或“选哪一种食材”，
// 到叶子时再检查是否存在某种食材超过了一半。
void dfs(int row, int chosen, i64 ways) {
    if (row > n) {
        if (chosen == 0) {
            return;
        }

        for (int j = 1; j <= m; j++) {
            if (cnt[j] * 2 > chosen) {
                return;
            }
        }

        ans += ways;
        ans %= MOD;
        return;
    }

    dfs(row + 1, chosen, ways);

    for (int j = 1; j <= m; j++) {
        if (a[row][j] == 0) {
            continue;
        }

        cnt[j]++;
        dfs(row + 1, chosen + 1, ways * a[row][j] % MOD);
        cnt[j]--;
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

    dfs(1, 0, 1);
    cout << ans << '\n';

    return 0;
}
