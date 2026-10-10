/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 任务安排：Hopcroft-Karp 二分图最大匹配（多组数据，读到 0 结束）
#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1 << 30;

int n, right_size;
vector<vector<int> > adj;
vector<int> match_l, match_r, dist;

// 给左部点分层，返回最短增广路的边数；没有增广路时返回 INF
int shortest_augmenting_length() {
    vector<int> q;
    for (int u = 0; u < n; u++) {
        bool free_l = match_l[u] < 0;
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
    return shortest;
}

// 从已分层的左部点 u 出发找长度恰为 shortest 的增广路，成功就翻转匹配
bool try_augment(int u, int shortest) {
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        int nx = match_r[v];
        bool grown;
        if (nx < 0) {
            grown = (dist[u] + 1 == shortest);
        } else {
            grown = (dist[nx] == dist[u] + 1) && try_augment(nx, shortest);
        }
        if (grown) {
            match_l[u] = v;
            match_r[v] = u;
            return true;
        }
    }
    dist[u] = INF; // 这个点往下到不了自由右部点，本轮放弃它
    return false;
}

int max_matching() {
    int total = 0;
    while (true) {
        int shortest = shortest_augmenting_length();
        if (shortest == INF) {
            return total;
        }
        for (int u = 0; u < n; u++) {
            if (match_l[u] < 0 && try_augment(u, shortest)) {
                total++;
            }
        }
    }
}

int main() {
    int printed = 0;
    while (true) {
        if (scanf("%d", &n) != 1) {
            break;
        }
        if (n == 0) {
            break;
        }
        int m, k;
        scanf("%d %d", &m, &k);
        adj.assign(n, vector<int>());
        for (int i = 0; i < k; i++) {
            int task, a, b;
            scanf("%d %d %d", &task, &a, &b);
            if (a && b) { // 用初始模式就能做的任务不产生约束
                adj[a].push_back(b);
            }
        }
        right_size = m;
        match_l.assign(n, -1);
        match_r.assign(m, -1);
        dist.assign(n, INF);
        printf("%d\n", max_matching());
        printed++;
    }
    if (printed == 0) {
        printf("\n");
    }
    return 0;
}
