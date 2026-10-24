/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 17:45
 * update_at: 2026-10-24 17:45
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个城市是否设为核心城市。
// choose[i] = 1 表示第 i 座城市是核心城市；枚举出完整序列后统一检查
// 「恰好 k 个」与「连通」，再用多源 BFS 算每个非核心城市到核心的距离。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 20; // 只适合 n <= 18 的小数据

typedef long long ll;

ll n;                 // 城市数
ll k;                 // 核心城市个数
vector<int> g[maxn];  // g[u]：与城市 u 直接相连的城市
int choose[maxn];     // choose[i]：第 i 座城市是否被选为核心城市
int vis[maxn];        // BFS 访问标记（判连通与算距离共用）
int core_cnt;         // 当前方案选了几个核心城市
ll best = 1e9;        // 当前最优拥堵度

// 只经过核心城市做一次 BFS，判断 k 个核心城市是否两两可达。
bool connected() {
    int start = 0;
    for (int u = 1; u <= n; u++) {
        if (choose[u]) {
            start = u;
            break;
        }
    }
    if (start == 0) return false;

    for (int u = 1; u <= n; u++) vis[u] = 0;
    queue<int> q;
    vis[start] = 1;
    q.push(start);
    int reached = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        reached++;
        for (int v : g[u]) {
            if (choose[v] && !vis[v]) { // 只能踩核心城市
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    return reached == core_cnt;
}

// 从非核心城市 start 出发 BFS，返回它到最近核心城市的距离。
int dist_to_core(int start) {
    for (int u = 1; u <= n; u++) vis[u] = 0;
    queue<int> q;      // 队列里存城市编号
    int depth[maxn];   // depth[u]：从 start 走到 u 的步数
    vis[start] = 1;
    depth[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (choose[u]) return depth[u];
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    return -1; // 树连通，不会走到这里
}

// 01 序列递归：第 dep 层决定第 dep 座城市当不当核心城市。
void dfs_choose(int dep) {
    if (dep == n + 1) { // 完整方案已生成，统一检查与统计
        if (core_cnt != k) return;
        if (!connected()) return;
        ll worst = 0;
        for (int u = 1; u <= n; u++) {
            if (!choose[u]) worst = max(worst, (ll)dist_to_core(u));
        }
        best = min(best, worst);
        return;
    }
    // 这一层选择：第 dep 座城市不设为核心
    choose[dep] = 0;
    dfs_choose(dep + 1);
    // 这一层选择：第 dep 座城市设为核心
    choose[dep] = 1;
    core_cnt++;
    dfs_choose(dep + 1);
    core_cnt--;
    choose[dep] = 0;
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

    core_cnt = 0;
    dfs_choose(1);
    cout << best << '\n';
    return 0;
}
