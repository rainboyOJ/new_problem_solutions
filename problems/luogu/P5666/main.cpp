/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:34
 * update_at: 2026-08-12 22:48
 */
// main.cpp：对每条边断开，用“沿最大子树方向倍增”求两侧连通块的重心编号和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOGN = 20; // 2^19 > 3e5，跳表需要 0..19 共 20 层

int n;
vector<int> g[MAXN];          // 邻接表存树
int sz[MAXN];                 // 当前定向下以 i 为根的子树大小（定向根的大小为 n）
int fa[MAXN];                 // 当前定向下 i 的父节点
int heavy_son[MAXN];          // 初始定向下 i 的最大子节点
int jump_table[MAXN][LOGN];   // jump_table[i][k]：沿 heavy 链向下跳 2^k 步到达的点
long long answer;             // 所有边断开后两侧重心编号和的总和

// 重新构建节点 u 的倍增表。换根只会改变 u 一层的 heavy 方向，其余节点不变。
void rebuild_jump(int u) {
    for (int k = 1; k < LOGN; k++) {
        jump_table[u][k] = jump_table[jump_table[u][k - 1]][k - 1];
    }
}

// 求“以 root 为根、大小为 sz[root] 的连通块”的重心编号和（重心可能有 1 或 2 个）。
// 从 root 出发沿最大子树方向下降，走到最后一个满足“子树不小于一半”的节点；
// 若最大子树恰好为一半，说明它和父节点是两个重心，两个编号都要计入。
void add_centroid_sum(int root) {
    int total = sz[root];
    int u = root;

    // 倍增贪心：大步到小步，能跳就跳（子树大小不小于 half）。
    for (int k = LOGN - 1; k >= 0; k--) {
        int v = jump_table[u][k];
        if (v != 0 && sz[v] * 2 >= total) {
            u = v;
        }
    }

    answer += u;
    if (sz[u] * 2 == total) {
        answer += fa[u];
    }
}

// 求节点 u 在当前定向下最大、次大的相邻组件大小对应的邻居。
// first/second 用于换根时把 v 排除后重选 u 的最大子树方向。
void largest_two(int u, int& first, int& second) {
    first = second = 0;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (sz[v] >= sz[first]) {
            second = first;
            first = v;
        } else if (sz[v] >= sz[second]) {
            second = v;
        }
    }
}

// 换根 DFS 的显式栈帧：node 的邻居已处理到 stack_idx[top]，
// stack_first/stack_second 是进入该帧时算好的最大、次大相邻组件。
int stack_node[MAXN], stack_father[MAXN], stack_idx[MAXN];
int stack_first[MAXN], stack_second[MAXN];

// 帧弹出时恢复的现场（由父帧在压入时保存）：
// changed_node 与 changed_child 是换根时被修改的边两端点。
int restore_fa_node[MAXN], restore_fa_child[MAXN];
int restore_sz_node[MAXN], restore_sz_child[MAXN];
int restore_jump0[MAXN], restore_changed_node[MAXN], restore_changed_child[MAXN];

// 第一遍 BFS 的顺序与队列（迭代写法避免 3e5 深度递归爆栈）。
int order_arr[MAXN], order_cnt;
int bfs_queue[MAXN];

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        sz[i] = 1;
        fa[i] = 0;
        heavy_son[i] = 0;
        for (int k = 0; k < LOGN; k++) {
            jump_table[i][k] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 第一遍：以 1 为根做 BFS，得到 fa[] 与遍历顺序 order_arr[]。
    order_cnt = 0;
    int head_q = 0, tail_q = 0;
    fa[1] = 0;
    bfs_queue[tail_q++] = 1;
    while (head_q < tail_q) {
        int u = bfs_queue[head_q++];
        order_arr[order_cnt++] = u;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            bfs_queue[tail_q++] = v;
        }
    }

    // 逆序遍历求 sz[] 与 heavy_son[]（保证子节点的信息先算好）。
    sz[0] = 0;
    for (int i = n - 1; i >= 1; i--) { // order_arr[0] 是根 1，跳过
        int u = order_arr[i];
        int p = fa[u];
        sz[p] += sz[u];
        if (sz[u] > sz[heavy_son[p]]) {
            heavy_son[p] = u;
        }
    }

    // 构建初始倍增表：jump_table[u][0] 就是 heavy 方向。
    // 必须按层构建：第 k 层只依赖第 k-1 层，保证任意节点的下层都已完成。
    for (int u = 1; u <= n; u++) {
        jump_table[u][0] = heavy_son[u];
    }
    for (int k = 1; k < LOGN; k++) {
        for (int u = 1; u <= n; u++) {
            jump_table[u][k] = jump_table[jump_table[u][k - 1]][k - 1];
        }
    }

    // 第二遍：显式栈模拟换根 DFS，枚举每条边并统计两侧重心。
    answer = 0;
    int top = 1;
    stack_node[1] = 1;
    stack_father[1] = 0;
    stack_idx[1] = 0;
    largest_two(1, stack_first[1], stack_second[1]);

    while (top >= 1) {
        int node = stack_node[top];
        int father = stack_father[top];

        if (stack_idx[top] == (int)g[node].size()) {
            // 本帧处理完毕：弹出并恢复父帧换根时保存的现场（根帧无需恢复）。
            if (top >= 2) {
                int cn = restore_changed_node[top];
                int cc = restore_changed_child[top];
                fa[cn] = restore_fa_node[top];
                fa[cc] = restore_fa_child[top];
                sz[cn] = restore_sz_node[top];
                sz[cc] = restore_sz_child[top];
                jump_table[cn][0] = restore_jump0[top];
                rebuild_jump(cn);
            }
            top--;
            continue;
        }

        int v = g[node][stack_idx[top]];
        stack_idx[top]++;
        if (v == father) {
            continue;
        }

        // 边 (node, v) 断开后，v 一侧就是当前定向下 v 的子树，直接求重心。
        add_centroid_sum(v);

        // 保存现场，准备把 v 临时变成定向根。
        restore_fa_node[top + 1] = fa[node];
        restore_fa_child[top + 1] = fa[v];
        restore_sz_node[top + 1] = sz[node];
        restore_sz_child[top + 1] = sz[v];
        restore_jump0[top + 1] = jump_table[node][0];
        restore_changed_node[top + 1] = node;
        restore_changed_child[top + 1] = v;

        // 换根：node 的 heavy 方向变成“除 v 外最大的相邻组件”。
        jump_table[node][0] = (v == stack_first[top]) ? stack_second[top] : stack_first[top];
        rebuild_jump(node);
        sz[node] -= sz[v];
        sz[v] += sz[node];

        // node 一侧是“补树”（整棵树去掉 v 的子树），求重心。
        add_centroid_sum(node);

        // 更新父指针，进入 v 的子树继续枚举。
        fa[node] = v;
        fa[v] = father;

        top++;
        stack_node[top] = v;
        stack_father[top] = node;
        stack_idx[top] = 0;
        largest_two(v, stack_first[top], stack_second[top]);
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
