/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:01
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 100005;

struct Edge {
    int to; // 边的另一端
    int id; // 边的编号，用于标记是否已使用
};

// 邻接表按终点升序排序，保证 Hierholzer 走出的路径字典序最小。
bool compare_edge(const Edge &left, const Edge &right) {
    return left.to < right.to;
}

int n, m;
vector<Edge> graph[MAXN]; // 邻接表存无向图
int degree[MAXN];         // 每个点的度数
int used[MAXM];           // used[id] 标记第 id 条边是否已走过
int pointer[MAXN];        // 每个点当前扫描到第几条边
vector<int> stack_nodes;  // Hierholzer 的递归栈
vector<int> path;         // 最终欧拉路径的顶点序列（逆序记录）

// 判断是否存在从 1 出发、经过所有边恰好一次的欧拉路，并输出字典序最小的路径。
// 欧拉路存在条件：奇度点数为 0（欧拉回路）或 2（欧拉路）；
// 若为 2，起点 1 必须是其中一个奇度点。
bool euler_path_exists() {
    int odd_count = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 == 1) odd_count++;
    }
    if (odd_count != 0 && odd_count != 2) return false;
    if (odd_count == 2 && degree[1] % 2 == 0) return false;
    return true;
}

// Hierholzer 算法：每次优先走当前编号最小的未用边，
// 走不动时把顶点压入 path，最后整体反转得到欧拉路。
void build_euler_path() {
    stack_nodes.push_back(1);
    while (!stack_nodes.empty()) {
        int u = stack_nodes.back();
        // 跳过已经使用过的边。
        while (pointer[u] < (int)graph[u].size() && used[graph[u][pointer[u]].id]) {
            pointer[u]++;
        }
        if (pointer[u] == (int)graph[u].size()) {
            // 当前点的边都走完了，回溯并记录顶点。
            path.push_back(u);
            stack_nodes.pop_back();
        } else {
            Edge edge = graph[u][pointer[u]++];
            used[edge.id] = 1;
            stack_nodes.push_back(edge.to);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back((Edge){v, i});
        graph[v].push_back((Edge){u, i});
        degree[u]++;
        degree[v]++;
    }

    if (!euler_path_exists()) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end(), compare_edge);
    }

    build_euler_path();

    // 顶点数应为 m+1（每条边贡献一个顶点）；否则说明图不连通，无解。
    if ((int)path.size() != m + 1) {
        cout << -1 << '\n';
        return 0;
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        if (i > 0) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}