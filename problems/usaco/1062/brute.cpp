/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:15
 * update_at: 2026-07-11 20:16
 */
// brute.cpp：小数据朴素解，把树根定为 1 后逐点模拟“翻倍再传播”。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
vector<int> g[MAXN];
long long ans;

int need_double_count(int children) {
    int cows = 1;
    int cnt = 0;
    while (cows < children + 1) {
        cows *= 2;
        cnt++;
    }
    return cnt;
}

void dfs(int u, int fa) {
    int children = 0;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v != fa) children++;
    }

    // 先在当前农场翻倍到足够：给每个孩子 1 头，还要自己留下 1 头。
    ans += need_double_count(children);
    ans += children;

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v != fa) {
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 0);
    cout << ans << '\n';

    return 0;
}
