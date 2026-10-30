#include <bits/stdc++.h>
using namespace std;

int n;
int a[15];
int ans[6000][11];
int cnt = 0;

void dfs(int dep, int sum) {
    // 10 种配料全部选择完毕
    if (dep > 10) {
        if (sum == n) {
            cnt++;
            for (int i = 1; i <= 10; i++)
                ans[cnt][i] = a[i];
        }
        return;
    }

    // 枚举当前配料的用量：1、2、3
    for (int i = 1; i <= 3; i++) {
        // 剪枝：剩余配料无法凑出 n
        int newSum = sum + i;
        int remaining = 10 - dep;

        if (newSum + remaining > n) continue;
        if (newSum + remaining * 3 < n) continue;

        a[dep] = i;               // 做选择
        dfs(dep + 1, newSum);     // 递归
        a[dep] = 0;               // 回溯
    }
}

int main() {
    cin >> n;

    dfs(1, 0);

    cout << cnt << '\n';

    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << ans[i][j];
            if (j < 10) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
