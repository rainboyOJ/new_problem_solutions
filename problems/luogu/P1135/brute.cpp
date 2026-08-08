#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, s, t;
int k[MAXN];
bool vis[MAXN];
int ans = 1e9;

void dfs(int u, int step) {
    if (step >= ans) {
        return;
    }
    if (u == t) {
        ans = step;
        return;
    }

    int v1 = u + k[u];
    int v2 = u - k[u];

    if (v1 >= 1 && v1 <= n && !vis[v1]) {
        vis[v1] = true;
        dfs(v1, step + 1);
        vis[v1] = false;
    }
    if (v2 >= 1 && v2 <= n && !vis[v2]) {
        vis[v2] = true;
        dfs(v2, step + 1);
        vis[v2] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    // 小数据暴力：枚举所有简单路径，并用当前最优答案剪枝。
    vis[s] = true;
    dfs(s, 0);

    if (ans == (int) 1e9) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }

    return 0;
}
