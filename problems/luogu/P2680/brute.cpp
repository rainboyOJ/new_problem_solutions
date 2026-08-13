/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举每一条边变成虫洞（边权置 0），再逐条运输计划计算改造后的路径长度，
// 记录所有计划完成时间的最大值，最后取所有选择中的最小值。
// 复杂度 O(n*m)，只适合 n、m 很小的情况。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAXM = 55;

struct EdgeInfo {
    int u, v, w;
};

struct AdjEdge {
    int to, id; // 邻接点，以及经过的边编号
};

int n, m;
EdgeInfo edges[MAXN];
vector<AdjEdge> graph_edges[MAXN];
int query_u[MAXM], query_v[MAXM];
int full_length[MAXM];      // 每条计划的原始路径长度
int path_edge_ids[MAXM][MAXN]; // path_edge_ids[i] 保存第 i 条计划经过的边编号
int path_edge_cnt[MAXM];
int parent_node[MAXN], parent_edge_id[MAXN];

// 在树上从 start 走到 target：树只有唯一一条路径，
// BFS 记录路径上每个点从哪里来、经过哪条边，再沿父链收集路径。
void find_path(int start, int target, int length_path[], int &cnt) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = -1;
        parent_edge_id[i] = 0;
    }

    queue<int> que;
    que.push(start);
    parent_node[start] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == target) {
            break;
        }
        for (int i = 0; i < (int)graph_edges[u].size(); i++) {
            int v = graph_edges[u][i].to;
            int id = graph_edges[u][i].id;
            if (parent_node[v] == -1) {
                parent_node[v] = u;
                parent_edge_id[v] = id;
                que.push(v);
            }
        }
    }

    // 从 target 沿父链走回 start，路径上的边倒序收集。
    cnt = 0;
    int x = target;
    while (x != start) {
        length_path[cnt] = parent_edge_id[x];
        cnt++;
        x = parent_node[x];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        graph_edges[edges[i].u].push_back({edges[i].v, i});
        graph_edges[edges[i].v].push_back({edges[i].u, i});
    }

    for (int i = 1; i <= m; i++) {
        cin >> query_u[i] >> query_v[i];
    }

    // 预处理：每条计划的路径边集合与原始长度。
    for (int i = 1; i <= m; i++) {
        find_path(query_u[i], query_v[i], path_edge_ids[i], path_edge_cnt[i]);
        full_length[i] = 0;
        for (int k = 0; k < path_edge_cnt[i]; k++) {
            full_length[i] += edges[path_edge_ids[i][k]].w;
        }
    }

    int answer = 1000000000;

    // 枚举哪一条边变成虫洞。
    for (int free_edge = 1; free_edge < n; free_edge++) {
        int worst = 0; // 这条边变成虫洞后，所有计划完成时间的最大值

        // 逐条计划计算改造后的长度：
        // 计划经过虫洞边时长度减少该边权，否则长度不变。
        for (int i = 1; i <= m; i++) {
            int length = full_length[i];
            for (int k = 0; k < path_edge_cnt[i]; k++) {
                if (path_edge_ids[i][k] == free_edge) {
                    length -= edges[free_edge].w;
                }
            }
            worst = max(worst, length);
        }

        answer = min(answer, worst);
    }

    cout << answer << '\n';

    return 0;
}
