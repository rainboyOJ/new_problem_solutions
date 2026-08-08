// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m;
int cost_[MAXN];
vector<int> pre[MAXN]; // pre[i] : 所有必须在 i 之前完成的奶牛

// 直接枚举“以 u 结尾”的所有依赖链，返回这条链的最大耗时。
int dfs(int u) {
    int best_pre = 0;
    for (int v : pre[u]) {
        best_pre = max(best_pre, dfs(v));
    }
    return best_pre + cost_[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cost_[i];
        pre[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        pre[v].push_back(u);
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, dfs(i));
    }

    cout << answer << '\n';
    return 0;
}
