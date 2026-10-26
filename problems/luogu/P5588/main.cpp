/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 09:20
 * update_at: 2026-10-26 09:20
 */
// main.cpp：O(n) 线性解法。自底向上扫一遍，对每个节点 u 看与 u 同色的其他节点
// 分布在几个方向上：含同色点的儿子子树各算一个方向，u 的子树外若还有同色点
// 再算一个。方向数 >= 3 说明同色点不共线，答案 0；恰好 1 说明 u 是同色点集合
// 最外层的端点，一个颜色最多两个端点，两端「外侧连通块大小」相乘即答案。
// 树可能退化成深度 10^6 的链，递归必然爆栈，所以按仓库规矩改为显式栈迭代 DFS。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005; // n <= 10^6

int n;
int color[MAXN]; // color[i]：节点 i 的颜色

int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt; // 链式前向星存树

int parent[MAXN];  // parent[x]：树上父亲（根 1 的父亲为 0）
int subtree[MAXN]; // subtree[x]：以 x 为根的子树大小

int total_cnt[MAXN];  // total_cnt[c]：颜色 c 的节点总数
int first_node[MAXN]; // first_node[c]：颜色 c 出现的第一个节点，供单点补集计算使用
int done_cnt[MAXN];   // done_cnt[c]：颜色 c 中已经处理完（子树扫完）的节点个数

int leaf_cnt[MAXN];          // leaf_cnt[c]：颜色 c 已经找到的端点个数
int too_many[MAXN];          // too_many[c]：颜色 c 的分叉方向 >= 3，答案必为 0
long long side_first[MAXN];  // side_first[c]：颜色 c 第一个端点外侧连通块的大小
long long side_second[MAXN]; // side_second[c]：颜色 c 第二个端点外侧连通块的大小

long long answer[MAXN]; // answer[c]：颜色 c 的答案

// 迭代 DFS 的一帧，记录"正在处理节点 u 及其儿子"这件事进行到哪了。
struct Frame {
    int u;          // 当前节点
    int edge;       // 下一条待处理的出边（链式前向星指针，0 表示儿子已全部处理完）
    long long sub;  // subtree[u] 的累加值
    int same;       // 子树中颜色为 color[u] 的节点数（含 u 自己）
    int positive;   // 已处理完的儿子中，子树里含 color[u] 的个数
    int only_child; // 最近一个含 color[u] 的儿子（方向数为 1 时用它算外侧大小）
    int before;     // 进入当前儿子之前 done_cnt[color[u]] 的快照
};
Frame stk[MAXN]; // 手工递归栈，最深可达 n 层，所以开成全局数组

// 加一条无向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 快读：n 可达 10^6，输入约 3*10^6 个整数，用 getchar 手写读入更稳。
int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

// 压入节点 u 的一帧，开始处理它的儿子。
void push_frame(int& top, int u) {
    top++;
    stk[top].u = u;
    stk[top].edge = head[u];
    stk[top].sub = 1;
    stk[top].same = 1;
    stk[top].positive = 0;
    stk[top].only_child = 0;
    stk[top].before = 0;
}

// u 的子树全部处理完时调用：判断 u 是不是颜色 color[u] 的端点。
// inside 是 u 子树内（含 u）的同色节点数，positive 是含同色节点的儿子个数。
void finish_node(int u, int inside, int positive, int only_child) {
    int c = color[u];
    if (total_cnt[c] == 1) {
        return; // 只有 1 个同色节点，答案按补集单独算
    }

    // 同色点分布在几个方向：每个含同色点的儿子算一个方向，
    // u 的子树外若还有同色点，再算一个方向。
    int outside = total_cnt[c] - inside;
    int dirs = positive + (outside > 0 ? 1 : 0);

    if (dirs >= 3) {
        too_many[c] = 1; // 同色点朝三个方向散开，不存在能装下它们的路径
        return;
    }
    if (dirs != 1) {
        return; // dirs == 2：u 夹在中间，是同色点集合的内部节点，不是端点
    }

    // dirs == 1：同色点全在 u 的一侧，u 就是最外层的端点。
    // 外侧连通块大小 = 切掉"含同色点的那一侧"之后，u 这侧剩下的点数。
    long long side;
    if (positive == 1) {
        // 同色点全在儿子 only_child 的子树里：u 这侧 = 整棵树去掉 only_child 的子树。
        side = 1LL * n - subtree[only_child];
    } else {
        // 同色点全在 u 子树外：u 这侧就是自己的整棵子树。
        side = subtree[u];
    }
    leaf_cnt[c]++;
    if (leaf_cnt[c] == 1) {
        side_first[c] = side;
    } else if (leaf_cnt[c] == 2) {
        side_second[c] = side;
    }
}

// 显式栈迭代 DFS，等价于递归的"进入 u → 依次处理儿子 → 离开 u"。
// 离开 u 时儿子都已算完，可以确定 subtree[u] 并判断端点。
void dfs_all() {
    int top = -1;
    parent[1] = 0;
    push_frame(top, 1);

    while (top >= 0) {
        Frame &cur = stk[top];
        if (cur.edge != 0) {
            // 还有儿子没处理，取出一条出边。
            int v = to[cur.edge];
            cur.edge = nxt[cur.edge];
            if (v == parent[cur.u]) {
                continue; // 跳过父亲这条边（存的是无向边）
            }
            parent[v] = cur.u;
            cur.before = done_cnt[color[cur.u]]; // 进入儿子前的快照
            push_frame(top, v);                  // 先进入儿子，父亲这一帧留在栈里
            continue;
        }

        // 儿子都处理完了，可以结算 u。
        int u = cur.u;
        int inside = cur.same;
        int positive = cur.positive;
        int only_child = cur.only_child;
        long long sub = cur.sub;
        subtree[u] = sub;
        done_cnt[color[u]]++;
        top--;

        finish_node(u, inside, positive, only_child);

        if (top >= 0) {
            // 把 u 这棵子树的结果累加到父亲身上。
            Frame &p = stk[top];
            int parent_color = color[p.u];
            int added = done_cnt[parent_color] - p.before; // 这棵子树里的父颜色节点数
            p.sub += sub;
            p.same += added;
            if (added > 0) {
                p.positive++;
                p.only_child = u;
            }
        }
    }
}

int main() {
    n = read_int();
    for (int i = 1; i <= n; i++) {
        color[i] = read_int();
        total_cnt[color[i]]++;
        if (first_node[color[i]] == 0) {
            first_node[color[i]] = i;
        }
    }
    for (int i = 1; i < n; i++) {
        int u = read_int();
        int v = read_int();
        add_edge(u, v);
        add_edge(v, u);
    }

    long long all_pairs = 1LL * n * (n - 1) / 2; // 全部无序点对
    for (int c = 1; c <= n; c++) {
        answer[c] = all_pairs; // 没有该颜色节点时，所有点对都合法
    }

    dfs_all();

    for (int c = 1; c <= n; c++) {
        if (total_cnt[c] == 0) {
            continue;
        }
        if (total_cnt[c] == 1) {
            // 只有一个同色节点 x：路径必须经过 x，用补集减去"两端在同一连通块"。
            int x = first_node[c];
            long long out = n - subtree[x];
            long long excluded = out * (out - 1) / 2;
            for (int e = head[x]; e != 0; e = nxt[e]) {
                int v = to[e];
                if (parent[v] == x) {
                    long long s = subtree[v];
                    excluded += s * (s - 1) / 2;
                }
            }
            answer[c] = all_pairs - excluded;
        } else {
            // 恰好两个端点才共线；端点不是两个说明同色点不共线或分叉，答案为 0。
            answer[c] = (too_many[c] == 1 || leaf_cnt[c] != 2) ? 0 : side_first[c] * side_second[c];
        }
    }

    for (int c = 1; c <= n; c++) {
        printf("%lld\n", answer[c]);
    }

    return 0;
}
