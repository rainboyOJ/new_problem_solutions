/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 車的放置：行与列传匹配，每个非禁格是一条边，最大匹配 = 最多車数
#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1 << 30;

int n, m;
vector<vector<int> > adj;
vector<int> match_l, match_r, dist;

// Hopcroft-Karp 增广（递归深度不超过层数）
bool dfs_augment(int u) {
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        int w = match_r[v];
        if (w < 0 || (dist[w] == dist[u] + 1 && dfs_augment(w))) {
            match_l[u] = v;
            match_r[v] = u;
            return true;
        }
    }
    dist[u] = INF; // 本轮失败，剪枝
    return false;
}

int main() {
    int t;
    if (scanf("%d %d %d", &n, &m, &t) != 3) {
        return 0;
    }
    vector<char> ok((long long)n * m, 1);
    for (int i = 0; i < t; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        ok[(long long)(x - 1) * m + (y - 1)] = 0; // 禁格坐标 1-indexed
    }
    adj.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ok[(long long)i * m + j]) {
                adj[i].push_back(j);
            }
        }
    }

    match_l.assign(n, -1);
    match_r.assign(m, -1);
    dist.assign(n, INF);
    int ans = 0;
    while (true) {
        vector<int> q;
        for (int u = 0; u < n; u++) {
            bool free_l = match_l[u] == -1;
            dist[u] = free_l ? 0 : INF;
            if (free_l) {
                q.push_back(u);
            }
        }
        bool found = false;
        for (int h = 0; h < (int)q.size(); h++) {
            int u = q[h];
            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i];
                int w = match_r[v];
                if (w == -1) {
                    found = true; // 到达未匹配右点，存在增广路
                } else if (dist[w] == INF) {
                    dist[w] = dist[u] + 1;
                    q.push_back(w);
                }
            }
        }
        if (!found) {
            break;
        }
        for (int u = 0; u < n; u++) {
            if (match_l[u] == -1 && dfs_augment(u)) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
