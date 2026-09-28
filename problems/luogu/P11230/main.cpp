/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-05 21:47
 * update_at: 2026-09-28 10:54
 */
// main.cpp：按人扫描序列做轮次 DP，用覆盖区间批量标记可达值。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;   // 值的范围
const int MAXN = 100005;   // 人数
const int MAXE = 200005;   // 序列总长度
const int MAXR = 105;      // 询问中的最大轮数不超过 100

int n, k, q;
int max_round;

// ---------- 所有人序列的平铺存储 ----------
int seq_vals[MAXE + 5];     // 所有人的序列值拼接
int seq_start[MAXN + 5];    // seq_start[p] = 第 p 个人的序列起始下标（1-indexed）
int seq_len[MAXN + 5];      // seq_len[p] = 第 p 个人序列的长度

// ---------- 询问 ----------
int query_round[MAXN];
int query_value[MAXN];

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

    int cur = 1;
    for (int person = 1; person <= n; person++) {
        cin >> seq_len[person];
        seq_start[person] = cur;
        for (int i = 1; i <= seq_len[person]; i++) {
            cin >> seq_vals[cur];
            cur++;
        }
    }

    max_round = 0;
    for (int i = 1; i <= q; i++) {
        cin >> query_round[i] >> query_value[i];
        max_round = max(max_round, query_round[i]);
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

// 固定本轮接龙人，扫描他的整个序列。
void scan_person(int person, int round) {
    int range_start = 1;
    int range_end = 0;
    int base = seq_start[person] - 1;
    int len = seq_len[person];

    for (int pos = 1; pos <= len; pos++) {
        int value = seq_vals[base + pos];

        // 合法起点 pos 能覆盖后面的 [pos + 1, pos + k - 1]。
        if (can_start(value, person)) {
            int new_end = min(len, pos + k - 1);
            if (range_end < pos) {
                range_start = pos + 1;
                range_end = new_end;
            } else {
                range_end = max(range_end, new_end);
            }
        }

        // pos 被某个更早的合法起点覆盖，因此能作为本轮结尾。
        if (pos >= range_start && pos <= range_end) {
            add_next_state(value, person);
            reachable[round][value] = true;
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
        int round = query_round[i];
        int value = query_value[i];
        cout << (reachable[round][value] ? 1 : 0) << '\n';
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
