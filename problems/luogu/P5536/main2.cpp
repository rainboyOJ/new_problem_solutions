/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 12:00
 * update_at: 2026-10-24 12:32
 */
// P5536 【XR-3】核心城市
// 直径视角：以直径中点 c 为根，令 h(u) 为 u 向下的最大深度。
// 取 h 最大的 k 个点作核心（一定连通且含 c），答案是第 k+1 大的 h 加 1。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 城市数上限

typedef long long ll;

ll n;                    // 城市数
ll k;                    // 核心城市个数
vector<int> g[maxn];     // g[u]：与城市 u 直接相连的所有城市
int parent_arr[maxn];    // parent_arr[u]：以当前根为根时 u 的父亲
int depth_arr[maxn];     // depth_arr[u]：u 到当前根的深度
int height_arr[maxn];    // height_arr[u]：u 向下（不回头走父亲）能走到的最深距离
int furthest;            // 距当前根最远的点
int deepest;             // furthest 到当前根的距离

// 以 u 为根遍历一遍树：记录父亲、深度，并顺手更新最远点。
void dfs_deepest(int u, int fa, int d) {
    parent_arr[u] = fa;
    depth_arr[u] = d;
    if (d > deepest) {
        deepest = d;
        furthest = u;
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_deepest(v, u, d + 1);
    }
}

// 以 u 为根遍历一遍树：记录深度，并后序回推每个点向下的最大深度。
void dfs_height(int u, int fa, int d) {
    depth_arr[u] = d;
    height_arr[u] = 0; // 叶子向下的最大深度是 0
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_height(v, u, d + 1);
        height_arr[u] = max(height_arr[u], height_arr[v] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 第一步：任取 1 号点出发找最远点 b，b 一定是直径的一端。
    deepest = -1;
    dfs_deepest(1, 0, 0);
    int b = furthest;

    // 第二步：从 b 出发再找最远点 c，路径 b→c 就是一条直径。
    deepest = -1;
    dfs_deepest(b, 0, 0);
    int c = furthest;
    int diameter = deepest;

    // 第三步：从 c 沿父亲往 b 走 ceil(diameter / 2) 步，落在直径中点上。
    // 直径长为奇数时有两个中点，这里取靠近 b 的那个，两者答案相同。
    int center = c;
    for (int i = 1; i <= (diameter + 1) / 2; i++) {
        center = parent_arr[center];
    }

    // 第四步：以直径中点为根，求每个点向下的最大深度。
    dfs_height(center, 0, 0);

    // 第五步：h 大的点优先当核心；排在第 k+1 位的 h 加 1 就是答案
    // （那个点离核心一步，再往下走 h 步才能到最深的非核心叶子）。
    sort(height_arr + 1, height_arr + n + 1, greater<int>());
    cout << height_arr[k + 1] + 1 << '\n';

    return 0;
}
