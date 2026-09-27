/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:38
 * update_at: 2026-09-27 21:38
 */
// subtask_15.cpp：测试点 1 特判；测试点 2、3 建边后逐询问记忆化搜索。
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
vector<char> one_round;
map<long long, int> memo; // 1 表示失败，2 表示成功。

long long make_key(int round, int value, int last_person) {
    return ((long long)round * (max_value + 1) + value) * (n + 1) + last_person;
}

bool dfs_game(int round, int value, int last_person) {
    if (round == target_round) {
        return value == target_value;
    }

    long long key = make_key(round, value, last_person);
    map<long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second == 2;
    }

    for (int i = 0; i < (int)edges[value].size(); i++) {
        int to = edges[value][i].to;
        int person = edges[value][i].person;
        if (person == last_person) continue;
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
    one_round.assign(max_value + 1, 0);

    for (int person = 1; person <= n; person++) {
        int len = (int)seq[person].size() - 1;
        for (int left = 1; left <= len; left++) {
            int right_end = min(len, left + k - 1);
            for (int right = left + 1; right <= right_end; right++) {
                int from = seq[person][left];
                int to = seq[person][right];

                Edge e;
                e.to = to;
                e.person = person;
                edges[from].push_back(e);

                if (from == 1) {
                    one_round[to] = 1;
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
            if (query_r[i] == 1) {
                cout << (one_round[query_c[i]] ? 1 : 0) << '\n';
                continue;
            }

            target_round = query_r[i];
            target_value = query_c[i];
            memo.clear();
            cout << (dfs_game(0, 1, 0) ? 1 : 0) << '\n';
        }
    }

    return 0;
}
