/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:17
 * update_at: 2026-07-11 19:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

struct Operation {
    int from, to;
    ll val;
};

int n;
ll h[MAXN], avg, sub[MAXN];
vector<int> g[MAXN];
vector<Operation> ans;

void dfs_sum(int u, int fa) {
    sub[u] = h[u] - avg;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs_sum(v, u);
        sub[u] += sub[v];
    }
}

// 小数据递归版，直接对应官方 distribute 思路。
void dfs_build(int u, int fa) {
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa || sub[v] < 0) continue;
        dfs_build(v, u);
        if (sub[v] > 0) {
            ans.push_back((Operation){v, u, sub[v]});
        }
    }

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa || sub[v] >= 0) continue;
        ans.push_back((Operation){u, v, -sub[v]});
        dfs_build(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        avg += h[i];
    }
    avg /= n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_sum(1, 0);
    dfs_build(1, 0);

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i].from << ' ' << ans[i].to << ' ' << ans[i].val << '\n';
    }

    return 0;
}
