/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:49
 * update_at: 2026-10-05 09:49
 */
// 树的最小权支配集：三态树形 DP。
// dp0[u]：u 自己设看守，u 子树全部被看守的最小经费；
// dp1[u]：u 不设看守，但被某个儿子看到，u 子树全部被看守的最小经费；
// dp2[u]：u 不设看守、儿子也没看到它，只能指望父亲，u 子树内除 u 外
//         全部被看守的最小经费。
// 根没有父亲，答案为 min(dp0[root], dp1[root])。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1505;
const ll INF = 1e18;

ll n;
ll cost[MAXN]; // cost[u]：在 u 宫殿设看守的经费
int child_cnt[MAXN]; // child_cnt[u]：u 的儿子数
int child[MAXN][MAXN]; // child[u][j]：u 的第 j 个儿子（题面即按此给出，直接存矩阵）
bool has_parent[MAXN]; // has_parent[v]：v 是否出现过在某个父亲的儿子列表里
int order[MAXN]; // order：自顶向下的访问序，逆序即自底向上的转移序

ll dp0[MAXN], dp1[MAXN], dp2[MAXN];

// 从根出发用栈收集自顶向下遍历序；输入本身就是"父亲 -> 儿子"的有向描述，
// 入度为 0 的结点即根。
int find_root() {
    for (int u = 1; u <= n; u++) {
        if (!has_parent[u]) return u;
    }
    return 1; // 理论上不会走到这里
}

// 自底向上做三态转移。
void solve() {
    int root = find_root();

    // 用数组模拟栈：先得到自顶向下的访问序 order[0..cnt-1]。
    int cnt = 0;
    order[cnt++] = root;
    for (int i = 0; i < cnt; i++) {
        int u = order[i];
        for (int j = 1; j <= child_cnt[u]; j++) {
            order[cnt++] = child[u][j];
        }
    }

    // 逆序迭代：处理 u 时它的所有儿子已经转移完毕。
    for (int i = cnt - 1; i >= 0; i--) {
        int u = order[i];

        // dp0：u 自己设看守，每个儿子三态任选（父亲已看到它，dp2 也合法）。
        // dp2：u 不设看守，每个儿子都不能指望 u，只能取 dp0 / dp1。
        ll sum0 = cost[u], sum2 = 0;
        // min_delta：把某个儿子从 min(dp0,dp1) 抬到 dp0 的最小代价增量，
        // 用于计算"至少一个儿子设了看守"的 dp1。
        ll min_delta = INF;
        for (int j = 1; j <= child_cnt[u]; j++) {
            int v = child[u][j];
            sum0 += min(min(dp0[v], dp1[v]), dp2[v]);
            sum2 += min(dp0[v], dp1[v]);
            ll delta = dp0[v] - min(dp0[v], dp1[v]);
            if (delta < min_delta) min_delta = delta;
        }
        dp0[u] = sum0;
        dp2[u] = sum2;
        if (child_cnt[u] == 0) {
            dp1[u] = INF; // 叶子没有儿子，不可能"被儿子看到"
        } else {
            dp1[u] = sum2 + min_delta;
        }
    }

    cout << min(dp0[root], dp1[root]) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u, m;
        ll k;
        cin >> u >> k >> m;
        cost[u] = k;
        child_cnt[u] = m;
        for (int j = 1; j <= m; j++) {
            cin >> child[u][j];
            has_parent[child[u][j]] = true;
        }
    }

    solve();

    return 0;
}
