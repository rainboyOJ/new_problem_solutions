/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:35
 * update_at: 2026-11-10 23:35
 */
// brute.cpp：基于拓扑排序剥叶子找最小环的基准算法
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 200005;

int to_node[MAXN];
int in_degree[MAXN];
bool vis[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> to_node[i];
        in_degree[to_node[i]]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // 拓扑排序消去所有树枝节点
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = true;

        int v = to_node[u];
        in_degree[v]--;
        if (in_degree[v] == 0) {
            q.push(v);
        }
    }

    int min_cycle = n + 1;

    // 遍历所有环
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            int len = 0;
            int cur = i;
            while (!vis[cur]) {
                vis[cur] = true;
                cur = to_node[cur];
                len++;
            }
            min_cycle = min(min_cycle, len);
        }
    }

    cout << min_cycle << "\n";

    return 0;
}
