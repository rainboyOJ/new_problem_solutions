/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-12 14:24
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const int MAXM = 6005;

struct Edge {
    int from;
    int to;
    int answer; // 0：保持输入方向，1：反转，-1：尚未定向
};

struct AdjEdge {
    int to;
    int id;
};

int n, m, k;
Edge edges[MAXM];
vector<AdjEdge> graph[MAXN];

int parentNode[MAXN];
int parentEdge[MAXN];
int depth[MAXN];
int distToCore[MAXN];

int cycleU, cycleV, cycleEdge;

void clearCase() {
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        parentNode[i] = -1;
        parentEdge[i] = 0;
        depth[i] = 0;
        distToCore[i] = -1;
    }
    cycleU = cycleV = cycleEdge = 0;
}

// 把第 id 条边定向为 u -> v。
void setDirection(int id, int u, int v) {
    edges[id].answer = (edges[id].from == u && edges[id].to == v ? 0 : 1);
}

// 建立以 k 为根的 BFS 树，并找到第一条非树边。
void findCycle() {
    queue<int> q;
    parentNode[k] = 0;
    q.push(k);

    while (!q.empty() && cycleEdge == 0) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].to;
            int id = graph[u][i].id;

            if (parentNode[v] == -1) {
                parentNode[v] = u;
                parentEdge[v] = id;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
            // 简单图没有父子平行边，排除父节点就等价于排除唯一的父边。
            else if (v != parentNode[u]) {
                cycleU = u;
                cycleV = v;
                cycleEdge = id;
                break;
            }
        }
    }
}

int findLca(int u, int v) {
    while (depth[u] > depth[v]) u = parentNode[u];
    while (depth[v] > depth[u]) v = parentNode[v];

    while (u != v) {
        u = parentNode[u];
        v = parentNode[v];
    }
    return u;
}

// 构造“有向环 + 通向 k 的尾巴”。
void buildCore() {
    int exitNode = findLca(cycleU, cycleV);

    // cycleU -> cycleV -> ... -> exitNode -> ... -> cycleU
    setDirection(cycleEdge, cycleU, cycleV);

    int x = cycleV;
    while (x != exitNode) {
        distToCore[x] = 0;
        setDirection(parentEdge[x], x, parentNode[x]);
        x = parentNode[x];
    }

    distToCore[exitNode] = 0;
    x = cycleU;
    while (x != exitNode) {
        distToCore[x] = 0;
        setDirection(parentEdge[x], parentNode[x], x);
        x = parentNode[x];
    }

    // 环的出口沿 BFS 树走向 k。
    x = exitNode;
    while (x != k) {
        distToCore[x] = 0;
        setDirection(parentEdge[x], x, parentNode[x]);
        x = parentNode[x];
    }
    distToCore[k] = 0;
}

// 其余边全部朝远离核心的方向定向。
void directRemainingEdges() {
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (distToCore[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].to;
            if (distToCore[v] == -1) {
                distToCore[v] = distToCore[u] + 1;
                q.push(v);
            }
        }
    }

    for (int id = 1; id <= m; id++) {
        if (edges[id].answer != -1) continue;

        int u = edges[id].from;
        int v = edges[id].to;

        // 同一弱连通分量内朝远离核心定向；其他分量两端距离都是 -1，方向任意。
        if (distToCore[u] <= distToCore[v]) {
            setDirection(id, u, v);
        }
        else {
            setDirection(id, v, u);
        }
    }
}

void solveCase() {
    findCycle();
    if (cycleEdge == 0) {
        cout << "No\n";
        return;
    }

    buildCore();
    directRemainingEdges();

    cout << "Yes\n";
    for (int i = 1; i <= m; i++) {
        cout << edges[i].answer;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m >> k;
        clearCase();

        for (int i = 1; i <= m; i++) {
            cin >> edges[i].from >> edges[i].to;
            edges[i].answer = -1;

            int u = edges[i].from;
            int v = edges[i].to;
            graph[u].push_back({v, i});
            graph[v].push_back({u, i});
        }

        solveCase();
    }
    return 0;
}
