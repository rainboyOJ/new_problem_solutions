/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-20 11:28
 * update_at: 2026-08-20 11:28
 */
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Edge = struct { int to; ll w; }; // 树边：to 是另一端点，w 是边权
using Graph = std::vector<Edge>;

const int MAXN = 1000000 + 5; // 节点数上限

int n; // 国家数
Graph tree[MAXN]; // 全局邻接表数组：直接向 tree[u] 加带权边

int parent_arr[MAXN];  // parent_arr[u] 表示 u 在根化后的父亲节点
int parent_w[MAXN];    // parent_w[u] 表示 u 与其父亲的连边权值
int subtree_size[MAXN]; // subtree_size[u] 表示以 u 为根的子树大小
int order_arr[MAXN];    // BFS 得到的节点访问顺序
int order_cnt;          // 访问过的节点数

// 从任意点 s 出发 BFS 建父子关系与访问顺序。
// BFS 是队列迭代遍历，n 达到 1e6 时也不会深递归爆栈。
void bfs_build(int s) {
    queue<int> q;
    q.push(s);
    parent_arr[s] = 0; // 根没有父亲
    order_cnt = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order_arr[++order_cnt] = u;

        for (Edge e : tree[u]) {
            int v = e.to;
            if (v == parent_arr[u]) {
                continue; // 跳过父亲方向，避免走回上一步
            }
            parent_arr[v] = u;
            parent_w[v] = e.w;
            q.push(v);
        }
    }
}

// 逆序遍历顺序回推子树大小，同时累加每条父子边的修建费用。
// 断开父子边 (fa, u) 后，u 一侧有 subtree_size[u] 个节点，
// 另一侧为 n - subtree_size[u]，费用 = 边权 * |2*子树大小 - n|。
ll calc_cost() {
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        subtree_size[i] = 1;
    }

    // BFS 顺序中子节点一定在父节点之后，
    // 从后往前即可保证算完每个 u 时子树大小已完整。
    for (int i = order_cnt; i >= 2; i--) {
        int u = order_arr[i];
        ll diff = llabs(1LL * n - 2LL * subtree_size[u]);
        ans += 1LL * parent_w[u] * diff;
        subtree_size[parent_arr[u]] += subtree_size[u];
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    bfs_build(1);
    cout << calc_cost() << '\n';

    return 0;
}