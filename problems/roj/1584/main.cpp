/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:11
 * update_at: 2026-10-05 10:11
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 5;

// 骑士编号 1..n，每个骑士恰好厌恶一个人，形成基环树森林
int val[MAXN];    // val[u]: 骑士 u 的战斗力
int to_[MAXN];    // to_[u]: u 最厌恶的骑士（u 有一条指向它的出边）
int deg[MAXN];    // deg[u]: u 的入度，拓扑排序剥叶子用
ll f0[MAXN];      // f0[u]: 不选 u 时，u 子树（含收缩贡献）内的最大权和
ll f1[MAXN];      // f1[u]: 选 u 时，u 子树（含收缩贡献）内的最大权和
int que[MAXN];    // 手写队列：拓扑排序中入度为 0 的节点
bool vis[MAXN];   // vis[u]: u 是否已属于某个处理过的环
int cyc[MAXN];    // 环上节点的收集数组

// 拓扑排序剥除所有树枝：树枝上的树形 DP 收缩到环上节点
// 返回剩余入度 > 0 的节点个数（即所有环上的节点数）
int trim_trees(int n) {
    int head = 0, tail = 0;
    for (int u = 1; u <= n; ++u)
        if (deg[u] == 0) que[tail++] = u;
    while (head < tail) {
        int u = que[head++];
        int p = to_[u];
        // 树枝贡献转移给唯一出边邻居 p（与经典树形 DP 一致）
        f0[p] += max(f0[u], f1[u]);
        f1[p] += f0[u];
        if (--deg[p] == 0) que[tail++] = p;
    }
    return n - tail; // 未入过队的节点入度仍 > 0，正好是环上节点
}

// 在环上破环为链做 DP，返回该基环树的最大权独立集
ll solve_cycle(int m) {
    const ll NEG = -(1LL << 60);

    // 方案 1：强制不选环首 cyc[0]，则环尾可选可不选
    ll dp0 = f0[cyc[0]], dp1 = NEG;
    for (int i = 1; i < m; ++i) {
        int u = cyc[i];
        ll nd0 = max(dp0, dp1) + f0[u];
        ll nd1 = dp0 + f1[u];
        dp0 = nd0;
        dp1 = nd1;
    }
    ll best1 = max(dp0, dp1);

    // 方案 2：强制选环首 cyc[0]，则环尾强制不选
    dp0 = NEG;
    dp1 = f1[cyc[0]];
    for (int i = 1; i < m; ++i) {
        int u = cyc[i];
        ll nd0 = max(dp0, dp1) + f0[u];
        ll nd1 = dp0 + f1[u];
        dp0 = nd0;
        dp1 = nd1;
    }
    ll best2 = dp0;

    return max(best1, best2);
}

int main() {
    // 关闭同步，N 最大 1e6，必须快读快写
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    for (int u = 1; u <= n; ++u) {
        cin >> val[u] >> to_[u];
        f1[u] = val[u]; // 初始树形 DP：选自己至少有自身权值
        deg[to_[u]]++;
    }

    trim_trees(n);

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] > 0 && !vis[i]) {
            // 沿出边走一圈收集环上节点
            int m = 0;
            int u = i;
            while (!vis[u]) {
                vis[u] = true;
                cyc[m++] = u;
                u = to_[u];
            }
            ans += solve_cycle(m);
        }
    }

    cout << ans << "\n";
    return 0;
}
