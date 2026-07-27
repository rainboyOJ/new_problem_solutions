/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n, cnt;
int choose[11];          // choose[1..10] 每种配料的选择
int ans[60000][11];       // 保存所有方案,最多 3^10=59049

void dfs(int dep) {
    if (dep == 11) {
        int sum = 0;
        for (int i = 1; i <= 10; i++) sum += choose[i];
        if (sum == n) {
            cnt++;
            for (int i = 1; i <= 10; i++) ans[cnt][i] = choose[i];
        }
        return;
    }
    for (int i = 1; i <= 3; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    cin >> n;
    dfs(1);
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << ans[i][j];
            if (j < 10) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
