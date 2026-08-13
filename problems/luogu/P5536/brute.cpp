/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-08-13 08:02
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个城市是否为核心城市。
// choose[i] = 1 表示第 i 个城市是核心城市；枚举完整序列后检查连通性并统计答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, k;
vector<int> g[MAXN]; // 邻接表存树
int choose[MAXN];    // choose[i]：第 i 个城市是否被选为核心城市
int vis[MAXN];       // 连通性检查与 BFS 共用标记
int best = 1e9;

// 检查当前核心集合是否连通（只经过核心城市能否互相到达）。
bool check_connected() {
    int start = -1;
    for (int i = 1; i <= n; i++) {
        if (choose[i]) {
            start = i;
            break;
        }
    }
    if (start == -1)
        return false;
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    queue<int> q;
    vis[start] = 1;
    q.push(start);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (choose[v] && !vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    return cnt == k;
}

// 计算非核心城市 start 到最近核心城市的距离。
int dist_to_core(int start) {
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    queue<pair<int, int> > q; // 队列元素：(节点, 距离)
    vis[start] = 1;
    q.push(make_pair(start, 0));
    while (!q.empty()) {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        if (choose[u])
            return d;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (!vis[v]) {
                vis[v] = 1;
                q.push(make_pair(v, d + 1));
            }
        }
    }
    return -1; // 不会到达
}

// 生成完整 01 序列后在叶子节点统一检查、统计。
void dfs(int dep, int cnt) {
    if (dep == n + 1) {
        if (cnt != k || !check_connected())
            return;
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            if (!choose[i])
                cur = max(cur, dist_to_core(i));
        }
        if (cur < best)
            best = cur;
        return;
    }
    // 这一层决定第 dep 个城市选不选。
    choose[dep] = 0;
    dfs(dep + 1, cnt);
    choose[dep] = 1;
    dfs(dep + 1, cnt + 1);
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

    dfs(1, 0);
    cout << best << '\n';
    return 0;
}
