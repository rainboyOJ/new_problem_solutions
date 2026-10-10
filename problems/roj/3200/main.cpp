/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 棋盘覆盖：黑白染色建二分图，最大匹配数就是最多骨牌数（Hopcroft-Karp）
#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1 << 30;

int main() {
    int n, t;
    if (scanf("%d %d", &n, &t) != 2) {
        return 0;
    }
    int width = n + 2;
    vector<char> banned((long long)width * width, 0);
    for (int i = 0; i < width; i++) { // 四周边界也标成禁止格，越界判断直接省掉
        banned[i] = 1;
        banned[i * width] = 1;
        banned[i * width + width - 1] = 1;
        banned[width * (width - 1) + i] = 1;
    }
    for (int i = 0; i < t; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        banned[x * width + y] = 1;
    }

    int size = width * width;
    vector<vector<int> > adj(size);
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            int v = r * width + c;
            if (banned[v] || ((r + c) & 1)) {
                continue;
            }
            int nb[4] = {v - width, v + width, v - 1, v + 1};
            for (int s = 0; s < 4; s++) {
                if (!banned[nb[s]]) {
                    adj[v].push_back(nb[s]);
                }
            }
        }
    }

    vector<int> match_l(size, -1), match_r(size, -1), dist(size, INF);
    int total = 0;
    while (true) {
        // 分层：未匹配左部点入队，沿「未匹配边 → 匹配边」交替走
        vector<int> q;
        for (int u = 0; u < size; u++) {
            bool free_l = !banned[u] && !((u / width + u % width) & 1) &&
                          (match_l[u] < 0);
            dist[u] = free_l ? 0 : INF;
            if (free_l) {
                q.push_back(u);
            }
        }
        int shortest = INF;
        for (int h = 0; h < (int)q.size(); h++) {
            int u = q[h];
            if (dist[u] >= shortest) {
                continue;
            }
            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i];
                int nx = match_r[v];
                if (nx < 0) {
                    shortest = dist[u] + 1;
                } else if (dist[nx] == INF) {
                    dist[nx] = dist[u] + 1;
                    q.push_back(nx);
                }
            }
        }
        if (shortest == INF) {
            break; // 不存在增广路 ⇒ 已是最大匹配
        }
        // 沿长度恰为 shortest 的增广路逐条增广（用显式栈避免深递归）
        for (int root = 0; root < size; root++) {
            if (banned[root] || ((root / width + root % width) & 1) || match_l[root] >= 0) {
                continue;
            }
            if (dist[root] >= shortest) {
                continue;
            }
            vector<int> su, si, sv;
            su.push_back(root);
            si.push_back(0);
            sv.push_back(-1);
            bool found = false;
            while (!su.empty()) {
                int u = su.back(), i = si.back();
                if (i >= (int)adj[u].size()) {
                    dist[u] = INF;
                    su.pop_back();
                    si.pop_back();
                    sv.pop_back();
                    continue;
                }
                si.back() = i + 1;
                int v = adj[u][i];
                int nx = match_r[v];
                if (nx < 0) {
                    if (dist[u] + 1 != shortest) {
                        continue;
                    }
                    match_r[v] = u;
                    match_l[u] = v;
                    for (int z = (int)su.size() - 1; z > 0; z--) { // 交替路整体翻转
                        match_r[sv[z]] = su[z - 1];
                        match_l[su[z - 1]] = sv[z];
                    }
                    total++;
                    found = true;
                    break;
                }
                if (dist[nx] == dist[u] + 1) { // 只能沿分层方向往下走
                    su.push_back(nx);
                    si.push_back(0);
                    sv.push_back(v);
                }
            }
            if (found) {
                continue;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}
