/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 电话网络：点连通度，拆点建图后对每个点对求最大流（Dinic）
#include <cstdio>
#include <vector>
using namespace std;

const int BIG = 1 << 20; // “不可割断”的容量
const int INF = 1 << 30;

int node_cnt;
vector<int> to, cap, nxt_e, head;
vector<int> level, it;

// 连一条有向弧 u->v，紧跟一条残量 0 的反向弧，返回正向弧的边号
int link(int u, int v, int c) {
    to.push_back(v);
    cap.push_back(c);
    nxt_e.push_back(head[u]);
    head[u] = (int)to.size() - 1;
    to.push_back(u);
    cap.push_back(0);
    nxt_e.push_back(head[v]);
    head[v] = (int)to.size() - 1;
    return (int)to.size() - 2;
}

// BFS 分层，汇点不可达时返回 false
bool bfs_level(int s, int t) {
    level.assign(node_cnt, -1);
    vector<int> q;
    level[s] = 0;
    q.push_back(s);
    for (int h = 0; h < (int)q.size(); h++) {
        int u = q[h];
        for (int e = head[u]; e != -1; e = nxt_e[e]) {
            int v = to[e];
            if (cap[e] > 0 && level[v] < 0) {
                level[v] = level[u] + 1;
                q.push_back(v);
            }
        }
    }
    return level[t] >= 0;
}

// 沿分层图找一条增广路并推送流量
int dfs_flow(int u, int t, int limit) {
    if (u == t) {
        return limit;
    }
    for (; it[u] != -1; it[u] = nxt_e[it[u]]) {
        int e = it[u];
        int v = to[e];
        if (cap[e] > 0 && level[v] == level[u] + 1) {
            int got = dfs_flow(v, t, cap[e] < limit ? cap[e] : limit);
            if (got > 0) {
                cap[e] -= got;
                cap[e ^ 1] += got;
                return got;
            }
        }
    }
    return 0;
}

int dinic(int s, int t) {
    int total = 0;
    while (bfs_level(s, t)) {
        it = head;
        while (true) {
            int f = dfs_flow(s, t, INF);
            if (f == 0) {
                break;
            }
            total += f;
        }
    }
    return total;
}

// 最少删几个点能让图不连通；删不掉时按题面要求返回 n
int vertex_connectivity(int n, const vector<int>& a, const vector<int>& b) {
    if (n == 0) {
        return 0;
    }
    vector<vector<int> > neighbors(n);
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] == b[i]) {
            continue; // 去掉自环与重边
        }
        bool dup = false;
        for (int t = 0; t < (int)neighbors[a[i]].size(); t++) {
            if (neighbors[a[i]][t] == b[i]) {
                dup = true;
            }
        }
        if (!dup) {
            neighbors[a[i]].push_back(b[i]);
            neighbors[b[i]].push_back(a[i]);
        }
    }

    // 先看原图是否已经断开（孤立点也算断开）
    vector<char> seen(n, 0);
    vector<int> stk;
    stk.push_back(0);
    seen[0] = 1;
    int cnt = 1;
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (int i = 0; i < (int)neighbors[u].size(); i++) {
            int v = neighbors[u][i];
            if (!seen[v]) {
                seen[v] = 1;
                cnt++;
                stk.push_back(v);
            }
        }
    }
    if (cnt != n) {
        return 0;
    }

    // 拆点建图：点 v 换成 2v -> 2v+1 的容量 1 弧，原图无向边换成容量 BIG 的双向弧
    int N = 2 * n;
    vector<int> split(n, -1), t2, c2, n2, h2;
    to.clear(); cap.clear(); nxt_e.clear();
    head.assign(N, -1);
    for (int v = 0; v < n; v++) {
        split[v] = link(2 * v, 2 * v + 1, 1);
    }
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < (int)neighbors[u].size(); i++) {
            int v = neighbors[u][i];
            if (u < v) {
                link(2 * u + 1, 2 * v, BIG);
                link(2 * v + 1, 2 * u, BIG);
            }
        }
    }
    t2 = to; c2 = cap; n2 = nxt_e; h2 = head; // 残量模板
    node_cnt = N;

    int best = n;
    for (int s = 0; s < n; s++) {
        for (int t = s + 1; t < n; t++) {
            to = t2; cap = c2; nxt_e = n2; head = h2;
            cap[split[s]] = cap[split[t]] = BIG; // 源、汇不许被删
            int flow = dinic(2 * s, 2 * t + 1);
            if (flow < best) {
                best = flow;
                if (best <= 1) { // 已经断开 / 只有割点
                    return best;
                }
            }
        }
    }
    return best;
}

int main() {
    // 一次读入全部内容，再按“整数出现顺序”抽取（坐标写成 (x,y) 也能正确抽出来）
    vector<char> buf;
    int ch;
    while ((ch = getchar()) != EOF) {
        buf.push_back((char)ch);
    }
    vector<int> flat;
    long long cur = -1;
    for (int i = 0; i <= (int)buf.size(); i++) {
        char c = (i < (int)buf.size()) ? buf[i] : ' ';
        if (c >= '0' && c <= '9') {
            if (cur < 0) {
                cur = 0;
            }
            cur = cur * 10 + (c - '0');
        } else {
            if (cur >= 0) {
                flat.push_back((int)cur);
                cur = -1;
            }
        }
    }

    int printed = 0;
    int pos = 0;
    while (pos + 1 < (int)flat.size()) {
        int n = flat[pos], m = flat[pos + 1];
        vector<int> a(m), b(m);
        for (int i = 0; i < m; i++) {
            a[i] = flat[pos + 2 + 2 * i];
            b[i] = flat[pos + 3 + 2 * i];
        }
        pos += 2 + 2 * m;
        printf("%d\n", vertex_connectivity(n, a, b));
        printed++;
    }
    if (printed == 0) {
        printf("\n");
    }
    return 0;
}
