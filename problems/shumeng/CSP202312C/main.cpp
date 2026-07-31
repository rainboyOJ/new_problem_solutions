/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:50
 */
#include <bits/stdc++.h>
using namespace std;

struct DecisionNode {
    int question;
    int yes_child;
    int no_child;
};

int n, m, timer_count;
vector<long long> weight;
vector<int> tin, tout;
vector<vector<int> > child;
vector<DecisionNode> decision;

void dfs(int node) {
    tin[node] = ++timer_count;
    for (int i = 0; i < (int)child[node].size(); i++) dfs(child[node][i]);
    tout[node] = timer_count;
}

bool in_subtree(int node, int root) {
    return tin[root] <= tin[node] && tin[node] <= tout[root];
}

int build_decision_tree(const vector<char> &active) {
    int active_count = 0;
    for (int i = 1; i <= n; i++) active_count += active[i];
    int current = decision.size();
    decision.push_back({0, -1, -1});
    if (active_count == 1) return current;

    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix[tin[i]] = active[i] ? weight[i] : 0;
    }
    for (int i = 1; i <= n; i++) prefix[i] += prefix[i - 1];

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

    vector<char> yes_active(n + 1, 0), no_active(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!active[i]) continue;
        if (in_subtree(i, best_question)) yes_active[i] = 1;
        else no_active[i] = 1;
    }
    decision[current].question = best_question;
    decision[current].yes_child = build_decision_tree(yes_active);
    if (active_count > 1) {
        int no_count = 0;
        for (int i = 1; i <= n; i++) no_count += no_active[i];
        if (no_count > 0) decision[current].no_child = build_decision_tree(no_active);
    }
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

    vector<char> active(n + 1, 1);
    decision.reserve(2 * n);
    build_decision_tree(active);

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
            if (in_subtree(target, question)) current = decision[current].yes_child;
            else current = decision[current].no_child;
        }
        cout << '\n';
    }

    return 0;
}
