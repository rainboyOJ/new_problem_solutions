/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:29
 * update_at: 2026-10-01 15:37
 */
// subtask_60.cpp：按人扫描序列，双重循环枚举所有合法连续子序列（最坏 O(L^2)），
// 不显式存边，适合 sum(l) <= 2000、r <= 10 的测试点。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;   // 值的范围
const int MAXR = 105;      // 询问中的最大轮数不超过 100

// 一个询问：恰好 r 轮接龙后，最后一个元素是否恰好为 v
struct Query {
    int r;
    int v;
};

int n, k, q;
int max_round;              // 所有询问中的最大轮数

vector<vector<int> > seq;   // seq[person] = 第 person 个人的序列，下标从 1 开始用
vector<Query> queries;      // 全部询问

// reachable[r][v]：第 r 轮结束时值 v 是否可达
bool reachable[MAXR][MAXV];

// ---------- 轮次状态 ----------
// last1[v]：值 v 在上一轮的第一个生产者
// last2[v]：值 v 在上一轮的第二个生产者（同一轮中另一个不同的人）
// -1 不可达，0 第 0 轮（初始状态，任何人都可用）
int last1[MAXV], last2[MAXV];
int next1[MAXV], next2[MAXV];

// 读入一组数据，并求出询问中的最大轮数。
void read_input() {
    cin >> n >> k >> q;

    seq.assign(n + 1, vector<int>());
    for (int person = 1; person <= n; person++) {
        int len;
        cin >> len;
        seq[person].resize(len + 1);   // 下标 0 不用，方便和题面下标对应
        for (int i = 1; i <= len; i++) {
            cin >> seq[person][i];
        }
    }

    queries.resize(q + 1);
    max_round = 0;
    for (int i = 1; i <= q; i++) {
        cin >> queries[i].r >> queries[i].v;
        max_round = max(max_round, queries[i].r);
    }
}

// 判断值 v 是否可以作为本轮 person 的开头：
// 上轮必须有人以 v 结尾，且本轮的人不能与上轮第一生产者相同
// 除非上轮还有另一个不同的人也以 v 结尾
bool can_start(int v, int person) {
    if (last1[v] == -1) return false;
    if (last1[v] == 0) return true;
    if (last1[v] != person) return true;
    return last2[v] != -1;
}

// 记录“本轮可以由 person 接到 value”。
// 每个值只保留两个不同的人，已经足够判断下一轮能否换人。
void add_next_state(int value, int person) {
    if (next1[value] == -1) {
        next1[value] = person;
    } else if (next1[value] != person && next2[value] == -1) {
        next2[value] = person;
    }
}

// 固定本轮接龙人，双重循环枚举他的所有合法接龙序列 seq[person][left..right]。
void scan_person(int person, int round) {
    vector<int>& s = seq[person];
    int len = (int)s.size() - 1;

    for (int left = 1; left <= len; left++) {
        int from_value = s[left];
        if (!can_start(from_value, person)) continue;

        // 接龙序列长度必须在 [2, k]，所以结尾 right ∈ [left + 1, left + k - 1]
        int right_end = min(len, left + k - 1);
        for (int right = left + 1; right <= right_end; right++) {
            int to_value = s[right];
            add_next_state(to_value, person);
            reachable[round][to_value] = true;
        }
    }
}

// 从上一轮状态计算指定轮的全部可达状态。
void transfer_one_round(int round) {
    memset(next1, -1, sizeof(next1));
    memset(next2, -1, sizeof(next2));

    for (int person = 1; person <= n; person++) {
        scan_person(person, round);
    }

    memcpy(last1, next1, sizeof(last1));
    memcpy(last2, next2, sizeof(last2));
}

void preprocess_answers() {
    memset(last1, -1, sizeof(last1));
    memset(last2, -1, sizeof(last2));
    memset(reachable, 0, sizeof(reachable));

    // 第 0 轮从值 1 开始，0 表示还没有真正的上一轮接龙人。
    last1[1] = 0;

    for (int round = 1; round <= max_round; round++) {
        transfer_one_round(round);
    }
}

void print_answers() {
    for (int i = 1; i <= q; i++) {
        cout << (reachable[queries[i].r][queries[i].v] ? 1 : 0) << '\n';
    }
}

void solve() {
    read_input();
    preprocess_answers();
    print_answers();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
