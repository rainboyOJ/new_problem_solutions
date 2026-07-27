/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n, r;
int choose[25];

void dfs(int dep, int start) {
    if (dep == r) {
        for (int i = 0; i < r; i++)
            cout << setw(3) << choose[i];
        cout << endl;
        return;
    }
    for (int i = start; i <= n; i++) {
        choose[dep] = i;
        dfs(dep + 1, i + 1);
    }
}

int main() {
    cin >> n >> r;
    dfs(0, 1);
    return 0;
}
