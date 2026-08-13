/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:27
 * update_at: 2026-08-12 22:27
 */
// brute.cpp：小数据暴力解，枚举每个点作为会议地点，再 BFS 计算距离和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
vector<int> g[MAXN]; // 树的邻接表

// 以 start 为会议地点做一次 BFS，返回所有点到它的距离和。
long long calc_sum_from(int start) {
    static int dist[MAXN]; // dist[u]：start 到 u 的距离，-1 表示尚未访问
    for (int i = 1; i <= n; i++) dist[i] = -1;

    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += dist[i];
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 枚举每个点作为会议地点；距离和更小才更新，相等时保留编号小者。
    int best_node = 1;
    long long best_sum = calc_sum_from(1);
    for (int i = 2; i <= n; i++) {
        long long now = calc_sum_from(i);
        if (now < best_sum) {
            best_sum = now;
            best_node = i;
        }
    }

    cout << best_node << " " << best_sum << "\n";

    return 0;
}
