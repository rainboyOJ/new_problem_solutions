/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:55
 */
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int size;
    vector<int> tree;

    void init(int n) {
        size = n;
        tree.assign(n + 1, 0);
    }

    void add(int position, int value) {
        for (int i = position; i <= size; i += i & -i) tree[i] += value;
    }

    int query(int position) {
        int result = 0;
        for (int i = position; i > 0; i -= i & -i) result += tree[i];
        return result;
    }

    void range_add(int left, int right, int value) {
        add(left, value);
        add(right + 1, -value);
    }
};

int n, operation_count, timer_count;
vector<vector<int> > original_child; // 原树的子节点，用来计算 DFS 序
vector<int> parent, depth, tin, tout;
vector<int> head, tail, previous_sibling, next_sibling, child_count;
// 当前树的兄弟链表，以及每个节点当前的直接子节点数量。
// head、tail、previous_sibling、next_sibling 分别表示首子、尾子、前驱和后继。
// folder_data 只记录当前文件夹直接拥有的数据。
vector<long long> folder_data;
Fenwick deleted_ancestor; // 原树路径上已删除祖先的数量（用负数维护）

void dfs(int node) {
    // 迭代 DFS 避免原树是一条长链时递归栈溢出。
    vector<int> next_child(n + 1, 0);
    vector<int> stack;
    stack.push_back(node);
    tin[node] = ++timer_count;
    while (!stack.empty()) {
        int current = stack.back();
        int &index = next_child[current];
        if (index < (int)original_child[current].size()) {
            int child = original_child[current][index];
            index++;
            depth[child] = depth[current] + 1;
            tin[child] = ++timer_count;
            stack.push_back(child);
        } else {
            tout[current] = timer_count;
            stack.pop_back();
        }
    }
}

int pop_child(int node) {
    int child = head[node];
    head[node] = next_sibling[child];
    if (head[node] == 0) tail[node] = 0;
    else previous_sibling[head[node]] = 0;
    next_sibling[child] = 0;
    previous_sibling[child] = 0;
    child_count[node]--;
    return child;
}

void append_children(int target, int source) {
    if (head[source] == 0) return;
    if (tail[target] == 0) {
        head[target] = head[source];
        tail[target] = tail[source];
        previous_sibling[head[target]] = 0;
    } else {
        next_sibling[tail[target]] = head[source];
        previous_sibling[head[source]] = tail[target];
        tail[target] = tail[source];
    }
    child_count[target] += child_count[source];
    head[source] = 0;
    tail[source] = 0;
    child_count[source] = 0;
}

void merge_folder(int node) {
    int original_count = child_count[node];
    for (int i = 0; i < original_count; i++) {
        int child = pop_child(node);
        folder_data[node] += folder_data[child];
        append_children(node, child);
        deleted_ancestor.range_add(tin[child], tout[child], -1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> operation_count;
    parent.assign(n + 1, 0);
    original_child.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        original_child[parent[i]].push_back(i);
    }
    folder_data.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> folder_data[i];

    depth.assign(n + 1, 0);
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    dfs(1);
    deleted_ancestor.init(n + 1);

    head.assign(n + 1, 0);
    tail.assign(n + 1, 0);
    previous_sibling.assign(n + 1, 0);
    next_sibling.assign(n + 1, 0);
    child_count.assign(n + 1, 0);
    for (int node = 2; node <= n; node++) {
        int p = parent[node];
        if (head[p] == 0) head[p] = node;
        else {
            previous_sibling[node] = tail[p];
            next_sibling[tail[p]] = node;
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
            cout << depth[node] + 1 + deleted_ancestor.query(tin[node]) << '\n';
        }
    }

    return 0;
}
