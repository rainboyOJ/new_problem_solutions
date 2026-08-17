/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:52
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
vector<int> graph[MAXN]; // 邻接表存树：交换机 1..n，电脑编号为 n+1..n+m

// 从 start 出发 BFS，返回 {最远节点, 到该节点的距离}。
pair<int, int> bfs(int start, int total_nodes) {
    vector<int> distance(total_nodes + 1, -1);
    queue<int> q;
    q.push(start);
    distance[start] = 0;
    int farthest = start;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (distance[u] > distance[farthest]) farthest = u;
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (distance[v] != -1) continue;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }
    return make_pair(farthest, distance[farthest]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // 交换机按树状结构连接，第 i 台交换机连到上一层的交换机。
    for (int child = 2; child <= n; child++) {
        int parent;
        cin >> parent;
        graph[parent].push_back(child);
        graph[child].push_back(parent);
    }
    // 每台电脑作为新的叶子节点挂在对应的交换机上。
    for (int computer = 1; computer <= m; computer++) {
        int parent;
        cin >> parent;
        int node = n + computer;
        graph[parent].push_back(node);
        graph[node].push_back(parent);
    }

    // 整张网络是一棵树，树的直径 = 两次 BFS：任取一点找最远点，再从该点找最远距离。
    int total_nodes = n + m;
    int endpoint = bfs(1, total_nodes).first;
    cout << bfs(endpoint, total_nodes).second << '\n';

    return 0;
}
