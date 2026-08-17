/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 决策树节点：question 是要问的类别，yes/no_child 为两个答案分支的节点下标
struct DecisionNode {
    int question;
    int yes_child;
    int no_child;
};

int n, m;
int timer_count;              // DFS 序计数器
vector<long long> weight;     // 每个类别的权重
vector<int> tin, tout;        // 每个节点的 DFS 进入/离开时间戳
vector<vector<int> > child;   // 类别树的子节点列表
vector<DecisionNode> decision; // 决策树

// 对类别树做 DFS，得到每个节点的子树区间 [tin, tout]
void dfs(int node) {
    tin[node] = ++timer_count;
    for (int i = 0; i < (int)child[node].size(); i++) {
        dfs(child[node][i]);
    }
    tout[node] = timer_count;
}

// 判断 node 是否在 root 的子树内（用 DFS 序区间判断）
bool in_subtree(int node, int root) {
    return tin[root] <= tin[node] && tin[node] <= tout[root];
}

// 递归构造决策树：active[i] 表示类别 i 是否还在当前候选集合中。
// 返回新建节点的下标。
int build_decision_tree(const vector<char> &active) {
    int active_count = 0;
    for (int i = 1; i <= n; i++) active_count += active[i];

    int current = decision.size();
    decision.push_back({0, -1, -1});
    if (active_count == 1) return current; // 只剩一个类别，叶子节点

    // 用 DFS 序前缀和计算每个类别子树内的候选权重
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix[tin[i]] = active[i] ? weight[i] : 0;
    }
    for (int i = 1; i <= n; i++) prefix[i] += prefix[i - 1];

    // 选出使 |子树权重 - 其余权重| 最小、编号最小的候选类别
    long long total = prefix[n];
    long long best_difference = LLONG_MAX;
    int best_question = 0;
    for (int i = 1; i <= n; i++) {
        if (!active[i]) continue;
        long long inside_weight = prefix[tout[i]] - prefix[tin[i] - 1];
        long long difference = llabs(total - 2 * inside_weight);
        if (difference < best_difference
                || (difference == best_difference && i < best_question)) {
            best_difference = difference;
            best_question = i;
        }
    }

    // 按目标是否在该子树中，把候选集合一分为二
    vector<char> yes_active(n + 1, 0), no_active(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!active[i]) continue;
        if (in_subtree(i, best_question)) yes_active[i] = 1;
        else no_active[i] = 1;
    }

    decision[current].question = best_question;
    decision[current].yes_child = build_decision_tree(yes_active);
    int no_count = 0;
    for (int i = 1; i <= n; i++) no_count += no_active[i];
    if (no_count > 0) decision[current].no_child = build_decision_tree(no_active);
    return current;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    weight.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> weight[i];

    child.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        child[parent].push_back(i);
    }
    tin.resize(n + 1);
    tout.resize(n + 1);
    dfs(1);

    // 从全集开始一次性构造与目标无关的决策树
    vector<char> active(n + 1, 1);
    decision.reserve(2 * n);
    build_decision_tree(active);

    // 每个测试目标只需沿决策树走一条路径
    while (m--) {
        int target;
        cin >> target;
        int current = 0;
        bool first = true;
        while (decision[current].question != 0) {
            int question = decision[current].question;
            if (!first) cout << ' ';
            first = false;
            cout << question;
            // 目标在子树内走 yes 分支，否则走 no 分支
            if (in_subtree(target, question)) current = decision[current].yes_child;
            else current = decision[current].no_child;
        }
        cout << '\n';
    }

    return 0;
}