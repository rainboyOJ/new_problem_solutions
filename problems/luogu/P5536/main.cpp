/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 17:45
 * update_at: 2026-10-24 17:45
 */
// P5536 【XR-3】核心城市
// 直径中点视角：最优核心一定包含直径中点 c。以 c 为根把树定向后，
// 每个点有一个「向下高度」h(u)；取 h 最大的 k 个点当核心，答案是第 k+1 大的 h 再加 1。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 城市数上限

typedef long long ll;

ll n;                 // 城市数
ll k;                 // 核心城市个数
vector<int> g[maxn];  // g[u]：与城市 u 直接相连的城市
int parent_arr[maxn]; // parent_arr[u]：以当前根为根时 u 的父亲
int depth_arr[maxn];  // depth_arr[u]：u 到当前根的深度
int height_arr[maxn]; // height_arr[u]：u 向下（不回头走父亲）能走的最远步数

// 以 u 为根遍历一次：记录父亲与深度，并回报「最远点」和「最远距离」。
void dfs_far(int u, int fa, int d, int &far_node, int &far_dist) {
    parent_arr[u] = fa;
    depth_arr[u] = d;
    if (d > far_dist) {
        far_dist = d;
        far_node = u;
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_far(v, u, d + 1, far_node, far_dist);
    }
}

// 以 u 为根遍历一次：后序回推每个点向下的高度 h(u)（叶子为 0）。
void dfs_height(int u, int fa) {
    height_arr[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_height(v, u);
        height_arr[u] = max(height_arr[u], height_arr[v] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 第一步：任取 1 号点出发找到最远点 a，a 必是直径的一个端点。
    int a = 1, far_dist = -1;
    dfs_far(1, 0, 0, a, far_dist);

    // 第二步：从 a 出发再找最远点 b，路径 a→b 就是一条直径，长度为 far_dist。
    int b = a;
    far_dist = -1;
    dfs_far(a, 0, 0, b, far_dist);

    // 第三步：从 b 沿父亲往上走 round_up(D/2) 步，落到直径中点上
    // （D 为偶数时唯一；D 为奇数时有两个中点，取靠近 a 的那个）。
    int center = b;
    for (int step = 1; step <= (far_dist + 1) / 2; step++) {
        center = parent_arr[center];
    }

    // 第四步：以 diameter 中点为根求所有点向下高度。
    dfs_height(center, 0);

    // 第五步：h 越大越靠近树中心。前 k 大的点一定构成连通块且包含中点
    // （父亲的高度严格大于儿子），拿它们当核心；排在第 k+1 位的点离核心
    // 只有一步，它下面最深的叶子还要走 h 步，所以答案是 h_{k+1} + 1。
    sort(height_arr + 1, height_arr + n + 1, greater<int>());
    cout << height_arr[k + 1] + 1 << '\n';

    return 0;
}
