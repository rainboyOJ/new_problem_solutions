/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 09:55
 * update_at: 2026-11-10 09:55
 */
// brute.cpp：小数据暴力解，枚举所有满足「父亲先染色」的染色顺序，取最小代价。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 12;

int n, root;
ll  w[maxn];
int fa[maxn];
bool used[maxn];      // 是否已染色
ll  best;

void dfs(int dep, ll cost) {
    if (dep > n) {
        best = min(best, cost);
        return;
    }
    for (int i = 1; i <= n; i ++ ) {
        if (used[i]) continue;
        if (i != root && !used[fa[i]]) continue;   // 父亲必须先染色
        used[i] = true;
        dfs(dep + 1, cost + (ll)dep * w[i]);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> root) {
        if (n == 0 && root == 0) break;
        for (int i = 1; i <= n; i ++ ) cin >> w[i], used[i] = false;
        for (int i = 1, a, b; i < n; i ++ ) {
            cin >> a >> b;
            fa[b] = a;
        }
        best = LLONG_MAX;
        dfs(1, 0);
        cout << best << '\n';
    }
    return 0;
}
