/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 16:59
 * update_at: 2026-10-21 18:20
 */
// 营救的第四种解法：二分答案 + 并查集。
// 与 main3.cpp（二分 + BFS）思路相同——答案具有单调性，二分拥挤度上界 L；
// 差别只在 check 的实现：这里不建邻接表、不做搜索，而是
//   把所有权 <= L 的边用并查集合并，最后判断 s 与 t 是否同块。
//
// 为什么这样也对：并查集合并完权 <= L 的全部边后，同一集合恰好是
// 「只走权 <= L 的边时互相连通的点」，于是「s 与 t 同块」等价于
// 「只走权 <= L 的边时 s 能到 t」，正是 BFS 要判的东西。
//
// 与 main3.cpp 的取舍：
//   BFS 版每次 check 要遍历邻接表 O(n+m)，并查集版每次 check 只扫一遍边表 O(m)
//   并且不用建邻接表；但并查集版每轮都要重新初始化 parent，常数略大。
//   两者同阶，都是 O(m log W)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5;  // 区数上界 n <= 1e4
const int MAXM = 20000 + 5;  // 大道数上界 m <= 2e4

struct Edge {
    int u;  // 起点
    int v;  // 终点
    ll w;   // 拥挤度
};

int n, m, start_node, target_node;
Edge edges[MAXM];
int dsu_parent[MAXN];  // dsu_parent[x]：x 的父节点，x 是根时等于 x

// 找 x 所在集合的根，顺路把路径上的点直接挂到根上（路径压缩）。
int dsu_find(int x) {
    if (dsu_parent[x] == x) return x;
    dsu_parent[x] = dsu_find(dsu_parent[x]);
    return dsu_parent[x];
}

// 只保留拥挤度 <= limit 的边做合并，判断 s 与 t 是否连通
bool connected_within(ll limit) {
    for (int i = 1; i <= n; i++) dsu_parent[i] = i;  // 每轮 check 都要重建并查集

    for (int i = 0; i < m; i++) {
        if (edges[i].w > limit) continue;  // 拥挤度超限的大道不能走
        // 路径压缩足够：单次操作摊还 O(log n)，本题 n <= 1e4 已经够
        dsu_parent[dsu_find(edges[i].u)] = dsu_find(edges[i].v);
    }

    return dsu_find(start_node) == dsu_find(target_node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_node >> target_node;

    ll max_w = 0;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        max_w = max(max_w, edges[i].w);
    }

    if (start_node == target_node) {
        cout << 0 << '\n';  // 不用走路，没有任何一段拥挤度
        return 0;
    }

    // 二分最小的可行上界：[low, high] 内一定存在答案
    ll low = 1, high = max_w;
    while (low < high) {
        ll mid = low + (high - low) / 2;
        if (connected_within(mid)) {
            high = mid;  // mid 可行，答案可能是 mid 或更小
        } else {
            low = mid + 1;  // mid 不可行，答案一定更大
        }
    }

    cout << low << '\n';
    return 0;
}
