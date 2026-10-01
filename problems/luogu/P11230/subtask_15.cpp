/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:38
 * update_at: 2026-10-01 18:42
 */
// subtask_15.cpp：测试点 1 特判；测试点 2、3 逐询问记忆化搜索。
// 不保存边表：搜索到某个状态时，现场扫描所有人的序列，
// 枚举以当前值开头的合法接龙序列（有色边），用完即丢。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXV = 200005;   // 值的范围
const int MAXR = 10;       // 测试点 2、3 保证 r <= 5，留富余
const int MAXP = 12;       // 测试点 2、3 保证 n <= 10，留富余

// 一个询问：恰好 r 轮接龙后，最后一个元素是否恰好为 v
struct Query {
    ll r;
    ll v;
};

ll n, k, q;
ll max_value;
ll target_round, target_value;

vector<vector<ll> > seq;    // seq[person] = 第 person 个人的序列，下标从 1 开始用
vector<char> one_round;     // one_round[v] = 1 表示一轮就能以 v 结尾

// memo[round][value][person]：状态 (round, value, person) 的搜索结果
//   0 = 还没搜过，1 = 失败，2 = 成功
// person = 0 表示还没有真正的上一轮接龙人（第 0 轮）。
char memo[MAXR][MAXV][MAXP];

// 从 (round, value, last_person) 出发，判断能否恰好 target_round 轮后以 target_value 结尾。
bool dfs_game(ll round, ll value, ll last_person) {
    if (round == target_round) {
        return value == target_value;
    }

    // 同样的状态搜过一次就够了，直接复用上次的结论。
    if (memo[round][value][last_person] != 0) {
        return memo[round][value][last_person] == 2;
    }

    // 现场枚举所有以 value 开头、接龙人不是 last_person 的合法接龙序列。
    for (ll person = 1; person <= n; person++) {
        if (person == last_person) continue;

        vector<ll>& s = seq[person];
        ll len = s.size() - 1;
        for (ll left = 1; left <= len; left++) {
            if (s[left] != value) continue;

            // 接龙序列长度在 [2, k]，结尾 right ∈ [left + 1, left + k - 1]
            ll right_end = min(len, left + k - 1);
            for (ll right = left + 1; right <= right_end; right++) {
                if (dfs_game(round + 1, s[right], person)) {
                    memo[round][value][last_person] = 2;
                    return true;
                }
            }
        }
    }

    memo[round][value][last_person] = 1;
    return false;
}

// 测试点 1（r = 1）：枚举所有以 1 开头的合法接龙序列，标记一轮可达的结尾值。
void compute_one_round() {
    one_round.assign(max_value + 1, 0);

    for (ll person = 1; person <= n; person++) {
        vector<ll>& s = seq[person];
        ll len = s.size() - 1;
        for (ll left = 1; left <= len; left++) {
            if (s[left] != 1) continue;

            ll right_end = min(len, left + k - 1);
            for (ll right = left + 1; right <= right_end; right++) {
                one_round[s[right]] = 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;
    while (T--) {
        cin >> n >> k >> q;

        seq.assign(n + 1, vector<ll>());
        max_value = 1;
        for (ll person = 1; person <= n; person++) {
            ll len;
            cin >> len;
            seq[person].resize(len + 1);
            for (ll i = 1; i <= len; i++) {
                cin >> seq[person][i];
                max_value = max(max_value, seq[person][i]);
            }
        }

        vector<Query> queries(q + 1);
        for (ll i = 1; i <= q; i++) {
            cin >> queries[i].r >> queries[i].v;
            max_value = max(max_value, queries[i].v);
        }

        compute_one_round();

        for (ll i = 1; i <= q; i++) {
            if (queries[i].r == 1) {
                cout << (one_round[queries[i].v] ? 1 : 0) << '\n';
                continue;
            }

            target_round = queries[i].r;
            target_value = queries[i].v;

            // 目标变了，把上一个询问留下的搜索结果清掉。
            for (ll r = 0; r < target_round; r++) {
                memset(memo[r], 0, sizeof(memo[r]));
            }

            cout << (dfs_game(0, 1, 0) ? 1 : 0) << '\n';
        }
    }

    return 0;
}
