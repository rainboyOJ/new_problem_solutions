/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:19
 * update_at: 2026-10-06 01:19
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int MAXM = 6005;

typedef long long ll;

int n, m, k;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt; // 链式前向星存图
int in_deg[MAXN];                             // 每个节点的入度，用于拓扑排序
int sg[MAXN];                                 // sg[u] 表示节点 u 的 SG 值
int q[MAXN];                                  // 拓扑排序的手写队列
int piece[MAXN];                              // 每颗棋子的初始位置
bool vis[MAXN];                               // 求 mex 时的标记数组

// 加一条 u -> v 的有向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    in_deg[v]++;
}

// 读入图和棋子位置。
void read_input() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }
    for (int i = 1; i <= k; i++) {
        cin >> piece[i];
    }
}

// 拓扑排序后按拓扑逆序自底向上计算每个节点的 SG 值。
void solve() {
    // 入度为 0 的节点先进队，这些是 DAG 上没有前驱的节点
    int qhead = 1, qtail = 0;
    for (int i = 1; i <= n; i++) {
        if (in_deg[i] == 0) {
            qtail++;
            q[qtail] = i;
        }
    }
    while (qhead <= qtail) {
        int u = q[qhead];
        qhead++;
        // u 的 SG 值等于其后继 SG 值集合的 mex
        // 求 mex：先标记所有后继的 SG 值，再从小到大找第一个没出现的非负整数
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (sg[v] < n) {
                vis[sg[v]] = true;
            }
        }
        int mex = 0;
        while (vis[mex]) {
            mex++;
        }
        sg[u] = mex;
        for (int i = 0; i < mex; i++) {
            vis[i] = false; // 只清理实际标记过的范围
        }
        // 把后继的入度减一，减到 0 就入队
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            in_deg[v]--;
            if (in_deg[v] == 0) {
                qtail++;
                q[qtail] = v;
            }
        }
    }

    // SG 定理：整体胜负等于所有棋子所在位置 SG 值的异或和
    int xorsum = 0;
    for (int i = 1; i <= k; i++) {
        xorsum ^= sg[piece[i]];
    }
    if (xorsum != 0) {
        cout << "win" << endl;
    } else {
        cout << "lose" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
