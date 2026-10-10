/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, s;
vector<pair<int, int> > adj[305];   // (v, w)
int dist_from[305][305];            // dist_from[v-1][x] = x 到 v 的距离
int u0_, uk_;

// 树中离 src 最远的结点编号 + 各点到 src 的距离
void farthest(int src, int dist[]) {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[src] = 0;
    deque<int> q;
    q.push_back(src);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (dist[v] < 0) { dist[v] = dist[u] + w; q.push_back(v); }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }

    // 两次 BFS 定位直径
    farthest(1, dist_from[0]);
    int far1 = 1;
    for (int i = 2; i <= n; i++)
        if (dist_from[0][i] > dist_from[0][far1]) far1 = i;
    u0_ = far1;
    farthest(u0_, dist_from[0]);   // dist0
    int far2 = u0_;
    for (int i = 1; i <= n; i++)
        if (dist_from[0][i] > dist_from[0][far2]) far2 = i;
    uk_ = far2;
    int dist0[305], distK[305];
    for (int i = 1; i <= n; i++) dist0[i] = dist_from[0][i];
    farthest(uk_, distK);
    int diameter = dist0[uk_];

    // 直径上的结点，按位置排序
    vector<int> path;
    for (int x = 1; x <= n; x++)
        if (dist0[x] + distK[x] == diameter) path.push_back(x);
    sort(path.begin(), path.end(), [&](int a, int b) { return dist0[a] < dist0[b]; });
    int k = (int)path.size();
    vector<int> pos(k);
    for (int t = 0; t < k; t++) pos[t] = dist0[path[t]];

    // 全源距离
    for (int v = 1; v <= n; v++) farthest(v, dist_from[v - 1]);

    // depAt[t]：以 path[t] 为挂点的结点的最大距离
    vector<int> depAt(k, 0);
    for (int v = 1; v <= n; v++) {
        int near = 0;
        int best = 1 << 30;
        for (int t = 0; t < k; t++) {
            int dd = dist_from[v - 1][path[t]];
            if (dd < best) { best = dd; near = t; }
        }
        depAt[near] = max(depAt[near], dist_from[v - 1][path[near]]);
    }

    // 枚举候选核 [i..j]
    int ans = diameter;
    int j = 0;
    for (int i = 0; i < k; i++) {
        if (j < i) j = i;
        while (j + 1 < k && pos[j + 1] - pos[i] <= s) j++;
        int cover = 0;
        for (int t = i; t <= j; t++) cover = max(cover, depAt[t]);
        int left_tail = pos[i];
        int right_tail = diameter - pos[j];
        ans = min(ans, max(cover, max(left_tail, right_tail)));
    }
    cout << ans << "\n";
    return 0;
}
