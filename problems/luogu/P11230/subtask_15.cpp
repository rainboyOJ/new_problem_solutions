/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:38
 * update_at: 2026-10-01 16:00
 */
// subtask_15.cpp：测试点 1 特判；测试点 2、3 逐询问记忆化搜索。
// 不保存边表：搜索到某个状态时，现场扫描所有人的序列，
// 枚举以当前值开头的合法接龙序列（有色边），用完即丢。
#include <bits/stdc++.h>
using namespace std;

// 一个询问：恰好 r 轮接龙后，最后一个元素是否恰好为 v
struct Query {
    int r;
    int v;
};

int n, k, q;
int max_value;
int target_round, target_value;

vector<vector<int> > seq;   // seq[person] = 第 person 个人的序列，下标从 1 开始用
vector<char> one_round;     // one_round[v] = 1 表示一轮就能以 v 结尾
map<long long, int> memo;   // 1 表示失败，2 表示成功。

long long make_key(int round, int value, int last_person) {
    return ((long long)round * (max_value + 1) + value) * (n + 1) + last_person;
}

// 从 (round, value, last_person) 出发，判断能否恰好 target_round 轮后以 target_value 结尾。
bool dfs_game(int round, int value, int last_person) {
    if (round == target_round) {
        return value == target_value;
    }

    long long key = make_key(round, value, last_person);
    map<long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second == 2;
    }

    // 现场枚举所有以 value 开头、接龙人不是 last_person 的合法接龙序列。
    for (int person = 1; person <= n; person++) {
        if (person == last_person) continue;

        vector<int>& s = seq[person];
        int len = (int)s.size() - 1;
        for (int left = 1; left <= len; left++) {
            if (s[left] != value) continue;

            // 接龙序列长度在 [2, k]，结尾 right ∈ [left + 1, left + k - 1]
            int right_end = min(len, left + k - 1);
            for (int right = left + 1; right <= right_end; right++) {
                if (dfs_game(round + 1, s[right], person)) {
                    memo[key] = 2;
                    return true;
                }
            }
        }
    }

    memo[key] = 1;
    return false;
}

// 测试点 1（r = 1）：枚举所有以 1 开头的合法接龙序列，标记一轮可达的结尾值。
void compute_one_round() {
    one_round.assign(max_value + 1, 0);

    for (int person = 1; person <= n; person++) {
        vector<int>& s = seq[person];
        int len = (int)s.size() - 1;
        for (int left = 1; left <= len; left++) {
            if (s[left] != 1) continue;

            int right_end = min(len, left + k - 1);
            for (int right = left + 1; right <= right_end; right++) {
                one_round[s[right]] = 1;
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

        vector<Query> queries(q + 1);
        for (int i = 1; i <= q; i++) {
            cin >> queries[i].r >> queries[i].v;
            max_value = max(max_value, queries[i].v);
        }

        compute_one_round();

        for (int i = 1; i <= q; i++) {
            if (queries[i].r == 1) {
                cout << (one_round[queries[i].v] ? 1 : 0) << '\n';
                continue;
            }

            target_round = queries[i].r;
            target_value = queries[i].v;
            memo.clear();
            cout << (dfs_game(0, 1, 0) ? 1 : 0) << '\n';
        }
    }

    return 0;
}
