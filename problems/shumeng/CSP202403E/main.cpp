/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, operation_count;
vector<int> original_child[MAXN]; // 原树的子节点，用来计算 DFS 序
int parent[MAXN], depth[MAXN], tin[MAXN], tout[MAXN]; // 原树的父、深度与 DFS 子树区间
// 当前树的兄弟链表：head/tail 是首子/尾子，prev_sib/next_sib 是兄弟前驱/后继
int head[MAXN], tail[MAXN], prev_sib[MAXN], next_sib[MAXN];
int child_count[MAXN];   // 当前文件夹的直接子节点数量
long long folder_data[MAXN]; // 当前文件夹直接拥有的数据量
int fenwick[MAXN];       // 树状数组，维护 DFS 序上的区间差分
int timer_count;         // DFS 计时器

// 树状数组：单点加
void bit_add(int pos, int value) {
    for (int i = pos; i <= n; i += i & -i) fenwick[i] += value;
}

// 树状数组：前缀和
int bit_query(int pos) {
    int result = 0;
    for (int i = pos; i > 0; i -= i & -i) result += fenwick[i];
    return result;
}

// 树状数组差分：区间 [left, right] 加 value
void range_add(int left, int right, int value) {
    bit_add(left, value);
    bit_add(right + 1, -value);
}

// 迭代 DFS 计算每个节点的 DFS 子树区间，避免原树是长链时递归栈溢出
void dfs(int root) {
    vector<int> next_child(n + 1, 0); // 记录每个节点已经处理到第几个子节点
    vector<int> stack;
    stack.push_back(root);
    tin[root] = ++timer_count;
    while (!stack.empty()) {
        int current = stack.back();
        if (next_child[current] < (int)original_child[current].size()) {
            int child = original_child[current][next_child[current]];
            next_child[current]++;
            depth[child] = depth[current] + 1;
            tin[child] = ++timer_count;
            stack.push_back(child);
        } else {
            tout[current] = timer_count;
            stack.pop_back();
        }
    }
}

// 从节点 node 的链表头部取走一个子节点并返回
int pop_child(int node) {
    int child = head[node];
    head[node] = next_sib[child];
    if (head[node] == 0) {
        tail[node] = 0;
    } else {
        prev_sib[head[node]] = 0;
    }
    next_sib[child] = 0;
    prev_sib[child] = 0;
    child_count[node]--;
    return child;
}

// 把 source 的整条子链表接到 target 的子链表尾部，并清空 source
void append_children(int target, int source) {
    if (head[source] == 0) return;
    if (tail[target] == 0) {
        head[target] = head[source];
        tail[target] = tail[source];
        prev_sib[head[target]] = 0;
    } else {
        next_sib[tail[target]] = head[source];
        prev_sib[head[source]] = tail[target];
        tail[target] = tail[source];
    }
    child_count[target] += child_count[source];
    head[source] = 0;
    tail[source] = 0;
    child_count[source] = 0;
}

// 合并文件夹 node：删除其当前所有直接子节点，数据并入 node，子链表上提
void merge_folder(int node) {
    int original_count = child_count[node];
    for (int i = 0; i < original_count; i++) {
        int child = pop_child(node);
        folder_data[node] += folder_data[child];
        append_children(node, child);
        // 删除的 child 成为路径上被跳过的祖先，对它的原树后代区间加 -1
        range_add(tin[child], tout[child], -1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> operation_count;
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        original_child[parent[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> folder_data[i];

    dfs(1);

    // 初始时按原父子关系建立兄弟链表
    for (int node = 2; node <= n; node++) {
        int p = parent[node];
        if (head[p] == 0) {
            head[p] = node;
        } else {
            prev_sib[node] = tail[p];
            next_sib[tail[p]] = node;
        }
        tail[p] = node;
        child_count[p]++;
    }

    while (operation_count--) {
        int type, node;
        cin >> type >> node;
        if (type == 1) {
            merge_folder(node);
            cout << child_count[node] << ' ' << folder_data[node] << '\n';
        } else {
            // 当前层数 = 原树深度 + 1，减去路径上已删除的祖先数量
            cout << depth[node] + 1 + bit_query(tin[node]) << '\n';
        }
    }

    return 0;
}