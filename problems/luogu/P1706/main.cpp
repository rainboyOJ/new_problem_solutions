/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n;
int choose[15];
bool vis[15];

void dfs(int dep) {
    if (dep == n) {
        for (int i = 0; i < n; i++)
            cout << setw(5) << choose[i];
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            choose[dep] = i;
            dfs(dep + 1);
            vis[i] = false;
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
