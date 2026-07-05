// brute_01_style.cpp：另一种小数据暴力写法，把每一轮选择哪条接龙边看成选择序列。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int person;
};

int n, k, q;
int max_value;
int target_round, target_value;
vector<vector<int> > seq;
vector<vector<Edge> > edges;
map<long long, int> memo; // 0 表示未知，1 表示失败，2 表示成功。

long long make_key(int round, int value, int last_person) {
    return ((long long)round * (max_value + 1) + value) * (n + 1) + last_person;
}

bool dfs_game(int round, int value, int last_person) {
    if (round == target_round) {
        return value == target_value;
    }
    if (value < 0 || value > max_value) {
        return false;
    }

    long long key = make_key(round, value, last_person);
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second == 2;
    }

    // 下一轮可以选择一条从当前值出发、且不是同一个人的边。
    for (int i = 0; i < (int)edges[value].size(); i++) {
        int to = edges[value][i].to;
        int person = edges[value][i].person;
        if (person == last_person) {
            continue;
        }
        if (dfs_game(round + 1, to, person)) {
            memo[key] = 2;
            return true;
        }
    }

    memo[key] = 1;
    return false;
}

void build_edges() {
    edges.assign(max_value + 1, vector<Edge>());

    for (int person = 1; person <= n; person++) {
        int len = (int)seq[person].size() - 1;
        for (int l = 1; l <= len; l++) {
            for (int r = l + 1; r <= len && r <= l + k - 1; r++) {
                int from = seq[person][l];
                int to = seq[person][r];
                if (from <= max_value && to <= max_value) {
                    Edge e;
                    e.to = to;
                    e.person = person;
                    edges[from].push_back(e);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> k >> q;

        seq.assign(n + 1, vector<int>());
        max_value = 1;
        for (int person = 1; person <= n; person++) {
            int len;
            cin >> len;
            seq[person].resize(len + 1);
            for (int i = 1; i <= len; i++) {
                cin >> seq[person][i];
                max_value = max(max_value, seq[person][i]);
            }
        }

        vector<int> query_r(q + 1), query_c(q + 1);
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            max_value = max(max_value, query_c[i]);
        }

        build_edges();

        for (int i = 1; i <= q; i++) {
            target_round = query_r[i];
            target_value = query_c[i];
            memo.clear();

            if (dfs_game(0, 1, 0)) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}
