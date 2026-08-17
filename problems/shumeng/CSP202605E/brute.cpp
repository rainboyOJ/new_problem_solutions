/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
// brute.cpp：小数据暴力，枚举每次聚拢时的节点和字符串排列，对完整状态去重。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> graph_brute[10];     // 树邻接表，只适合 n <= 10 的小数据
vector<vector<int> > best_answer; // 当前找到的最小最终串（只含一个非空串）
set<string> visited_state;       // 已访问过的完整状态，防止无限搜索

// 把当前状态编码成字符串，用于状态去重。
string encode_state(const vector<vector<int> >& state) {
    string result;
    for (int i = 0; i < n; i++) {
        result += '[';
        for (int j = 0; j < (int)state[i].size(); j++) {
            result += to_string(state[i][j]);
            result += ',';
        }
        result += ']';
    }
    return result;
}

// 判断 a 是否比当前最优答案更小。
bool lexicographically_smaller(const vector<int>& a,
                               const vector<int>& b) {
    if (b.empty()) {
        return true;
    }
    return a < b;
}

// 如果当前状态已经把全部字符合并成一个串，就尝试更新最优答案。
void update_answer(const vector<vector<int> >& state) {
    vector<int> answer;
    for (int i = 0; i < n; i++) {
        if (!state[i].empty()) {
            if (!answer.empty()) {
                return; // 还有多个非空串，尚未合并完成
            }
            answer = state[i];
        }
    }
    if (lexicographically_smaller(answer, best_answer.empty()
                                             ? vector<int>()
                                             : best_answer[0])) {
        best_answer.clear();
        best_answer.push_back(answer);
    }
}

// 深搜所有可能的聚拢操作序列。first_operation 标记是否第一次操作。
void search_state(const vector<vector<int> >& state, bool first_operation) {
    string key = encode_state(state);
    if (visited_state.count(key)) {
        return;
    }
    visited_state.insert(key);
    update_answer(state);

    // 枚举这次操作的中心节点
    for (int center = 0; center < n; center++) {
        vector<int> participating;
        participating.push_back(center);
        for (int i = 0; i < (int)graph_brute[center].size(); i++) {
            participating.push_back(graph_brute[center][i]);
        }

        // 收集中心及其邻点上的非空字符串
        vector<vector<int> > pieces;
        bool has_long_string = false;
        for (int i = 0; i < (int)participating.size(); i++) {
            int u = participating[i];
            if (!state[u].empty()) {
                pieces.push_back(state[u]);
                if (state[u].size() >= 2) {
                    has_long_string = true;
                }
            }
        }
        if (pieces.empty()) {
            continue;
        }
        // 除第一次操作外，参与串中必须有一个长度至少为 2 的串
        if (!first_operation && !has_long_string) {
            continue;
        }

        // 枚举这些串的拼接顺序
        sort(pieces.begin(), pieces.end());
        do {
            vector<vector<int> > next_state = state;
            for (int i = 0; i < (int)participating.size(); i++) {
                next_state[participating[i]].clear();
            }
            next_state[center].clear();
            for (int i = 0; i < (int)pieces.size(); i++) {
                next_state[center].insert(next_state[center].end(),
                                          pieces[i].begin(), pieces[i].end());
            }
            search_state(next_state, false);
        } while (next_permutation(pieces.begin(), pieces.end()));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph_brute[u].push_back(v);
        graph_brute[v].push_back(u);
    }

    // 初始状态：每个点只有一个只包含自己的字符
    vector<vector<int> > initial(n);
    for (int i = 0; i < n; i++) {
        initial[i].push_back(i);
    }
    search_state(initial, true);
    for (int i = 0; i < (int)best_answer[0].size(); i++) {
        cout << best_answer[0][i] + 1;
        if (i + 1 == (int)best_answer[0].size()) {
            cout << '\n';
        } else {
            cout << ' ';
        }
    }
    return 0;
}