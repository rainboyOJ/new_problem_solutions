#include <bits/stdc++.h>
using namespace std;

const int MAXM = 405;

int n, m;
int x[MAXM], y[MAXM];
int choose_item[25];
int ans;

void dfs_choose(int u) {
    if (u == n + 1) {
        for (int i = 1; i <= m; i++) {
            if (choose_item[x[i]] && choose_item[y[i]]) {
                return;
            }
        }
        ans++;
        return;
    }

    choose_item[u] = 0;
    dfs_choose(u + 1);
    choose_item[u] = 1;
    dfs_choose(u + 1);
    choose_item[u] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：递归枚举每种原料选或不选，再检查是否出现冲突对。
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i] >> y[i];
    }

    ans = 0;
    memset(choose_item, 0, sizeof(choose_item));
    dfs_choose(1);
    cout << ans << '\n';
    return 0;
}
