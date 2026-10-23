/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:28
 * update_at: 2026-10-23 20:28
 */
// subtask_linear.cpp：对应 30% 子任务（n <= 100, q <= 10^4）的 O(qn) 解法。
// 每次询问先用 DFS 取出 a -> b 的完整路径，再沿路径扫一遍：边更新最低买入价边算利润。
// 相对 brute.cpp 的推进：把“枚举所有买卖点对”的 O(k^2) 换成一次 O(k) 扫描。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 30% 子任务 n <= 100

vector<int> g[MAXN]; // g[u]：与城市 u 直接相连的城市
ll price[MAXN];      // price[u]：城市 u 当前的宝石价格

int path[MAXN]; // path[1..path_len]：本次询问 a -> b 路径上依次经过的城市
int path_len;   // 路径上的城市个数

// 从 u 往 target 方向 DFS，把途经城市按旅行顺序写进 path[]。
// 返回值表示“u 的子树里找到了 target”，上层据此决定是否保留 u。
bool dfs_path(int u, int father, int target) {
    path[++path_len] = u;
    if (u == target) return true;
    for (int v : g[u]) {
        if (v == father) continue;
        if (dfs_path(v, u, target)) return true;
    }
    path_len--; // 这条分支没通向 target，退掉
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &price[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int a, b;
        ll v;
        scanf("%d %d %lld", &a, &b, &v);

        path_len = 0;
        dfs_path(a, 0, b);

        // 一次扫描求最大利润：利润 = 当前价格 - 之前出现过的最低价格。
        ll best = 0;
        ll lowest = price[path[1]]; // 到目前位置为止最低的买入价
        for (int i = 2; i <= path_len; i++) {
            ll now = price[path[i]];
            if (now - lowest > best) best = now - lowest;
            if (now < lowest) lowest = now; // 更便宜的买点留给后面
        }
        printf("%lld\n", best);

        // 路过的城市价格整体上涨 v。
        for (int i = 1; i <= path_len; i++) price[path[i]] += v;
    }
    return 0;
}
