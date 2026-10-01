/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 15:46
 * update_at: 2026-10-01 15:46
 */
// main_no_last2.cpp：main.cpp 的简化版，只用一个 last[v] 记录上一轮接龙人，
// 不再分开保存 last1 / last2。扫描窗口做法不变。
//
// last[v] 的编码：
//   -1     ：值 v 不可达，谁都不能拿它开头；
//    0     ：上一轮至少有两个不同的人到达 v（或第 0 轮的初始值 1），
//            下一轮任何人都可以拿它开头；
//    p (>=1)：上一轮只有人 p 到达 v，下一轮只有 p 不能拿它开头。
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
int last[MAXV];             // 上一轮状态，编码见文件头
int next_last[MAXV];          // 本轮状态，扫描完再整体复制到 last

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

// 判断值 v 是否可以作为本轮 person 的开头。
bool can_start(int v, int person) {
    if (last[v] == -1) return false;   // 不可达
    if (last[v] == 0) return true;     // 至少两个不同的人（或初始状态）
    return last[v] != person;          // 唯一生产者不是 person 才行
}

// 记录“本轮可以由 person 接到 value”。
// 只有一个生产者时记下他，出现第二个不同的人就改记 0。
void add_next_laststate(int value, int person) {
    if (next_last[value] == -1) {
        next_last[value] = person;
    } else if (next_last[value] != person) {
        next_last[value] = 0;
    }
}

// 固定本轮接龙人，扫描他的整个序列。
void scan_person(int person, int round) {
    vector<int>& s = seq[person];
    int len = (int)s.size() - 1;

    int range_start = 1;
    int range_end = 0;

    for (int pos = 1; pos <= len; pos++) {
        int value = s[pos];

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
            add_next_laststate(value, person);
            reachable[round][value] = true;
        }
    }
}

// 从上一轮状态计算指定轮的全部可达状态。
void transfer_one_round(int round) {
    memset(next_last, -1, sizeof(next_last));

    for (int person = 1; person <= n; person++) {
        scan_person(person, round);
    }

    memcpy(last, next_last, sizeof(last));
}

void preprocess_answers() {
    memset(last, -1, sizeof(last));
    memset(reachable, 0, sizeof(reachable));

    // 第 0 轮从值 1 开始，且还没有真正的上一轮接龙人，
    // 任何人开头都可以，正好用 0 表示。
    last[1] = 0;

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
