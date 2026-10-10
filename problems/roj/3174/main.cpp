/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 战略游戏：树形 DP 求最小点覆盖（多组数据，读到 EOF）
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

void solve_one(int n) {
    vector<vector<int> > children(n);
    char tok[64];
    int root = -1;
    for (int line = 0; line < n; line++) {
        int u, c;
        scanf("%63s", tok);
        sscanf(tok, "%d:(%d)", &u, &c);
        if (root < 0) {
            root = u; // 第一行描述的就是树根
        }
        for (int i = 0; i < c; i++) {
            int v;
            scanf("%d", &v);
            children[u].push_back(v);
        }
    }

    // 先做一次 BFS 得到「父先于子」的访问顺序
    vector<int> order;
    order.push_back(root);
    for (int head = 0; head < (int)order.size(); head++) {
        int u = order[head];
        for (int i = 0; i < (int)children[u].size(); i++) {
            order.push_back(children[u][i]);
        }
    }

    vector<ll> dp0(n, 0), dp1(n, 1); // dp0：u 不放士兵；dp1：u 放士兵
    for (int t = (int)order.size() - 1; t >= 0; t--) {
        int u = order[t];
        for (int i = 0; i < (int)children[u].size(); i++) {
            int c = children[u][i];
            dp0[u] += dp1[c]; // u 不放，每条 (u,c) 只能靠 c 覆盖
            dp1[u] += dp0[c] < dp1[c] ? dp0[c] : dp1[c];
        }
    }
    ll ans = dp0[root] < dp1[root] ? dp0[root] : dp1[root];
    printf("%lld\n", ans);
}

int main() {
    int n;
    bool any = false;
    while (scanf("%d", &n) == 1) {
        solve_one(n);
        any = true;
    }
    (void)any;
    return 0;
}
