/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 10:33
 * update_at: 2026-08-12 15:02
 */
// main-queue.cpp：另一种分段模拟，用两个队列维护当前剩余序列的连续原数组段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

struct Segment {
    int pos;   // 这一段在当前序列中的起始排名
    int start; // 这一段在原数组中的起始下标
    int len;   // 这一段连续长度
};

int n;
int a[MAXN];
queue<Segment> q1, q2; // q1 本轮开始时的旧段，q2 本轮生成的新段（本轮的删除只看 q1）
int cube_pos[105];     // 本轮所有完全立方排名 1, 8, 27, ...，递增
int cube_cnt;
vector<vector<int> > rounds;

// 生成长度为 len 时的全部完全立方排名。
void build_cube_positions(int len) {
    cube_cnt = 0;
    for (long long x = 1; x * x * x <= len; x++) {
        cube_cnt++;
        cube_pos[cube_cnt] = (int)(x * x * x);
    }
}

// 把一个保留段推入新队列 q2。
void push_segment(int pos, int start, int len) {
    if (len <= 0) return;
    Segment seg;
    seg.pos = pos;
    seg.start = start;
    seg.len = len;
    q2.push(seg);
}

// 读入原数组。
void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

// 处理一轮：扫描 q1 中的旧段，收集本轮删除的元素值，并把保留段生成到 q2。
// new_len 通过引用带回本轮保留的元素总数。
vector<int> process_one_round(int len, int &new_len) {
    build_cube_positions(len);
    vector<int> deleted_values;

    // ptr 指向下一个要处理的立方排名；new_len 统计本轮保留的元素总数。
    int ptr = 1;
    new_len = 0;
    while (!q1.empty()) {
        Segment seg = q1.front();
        q1.pop();

        int seg_l = seg.pos;
        int seg_r = seg.pos + seg.len - 1;
        // 跳过段之前已经处理完的立方排名。
        while (ptr <= cube_cnt && cube_pos[ptr] < seg_l) ptr++;

        int last_offset = 0; // 已经处理到段内 0-based 的 last_offset 之前
        while (ptr <= cube_cnt && cube_pos[ptr] <= seg_r) {
            int offset = cube_pos[ptr] - seg.pos; // 0-based 段内偏移
            deleted_values.push_back(a[seg.start + offset]);

            // 该删除点之前没被删的部分作为保留段，进入下一轮。
            int keep_len = offset - last_offset;
            if (keep_len > 0) {
                push_segment(new_len + 1, seg.start + last_offset, keep_len);
                new_len += keep_len;
            }

            last_offset = offset + 1;
            ptr++;
        }

        // 段尾剩余部分保留。
        int tail_len = seg.len - last_offset;
        if (tail_len > 0) {
            push_segment(new_len + 1, seg.start + last_offset, tail_len);
            new_len += tail_len;
        }
    }

    return deleted_values;
}

// 逐轮删除，直到序列为空，把每轮删除的元素值存进 rounds。
void solve() {
    // 初始整个序列是一个段：排名从 1 开始，对应原数组 [1, n]。
    Segment first;
    first.pos = 1;
    first.start = 1;
    first.len = n;
    q1.push(first);

    int len = n; // 当前剩余序列长度
    while (len > 0) {
        int new_len = 0;
        rounds.push_back(process_one_round(len, new_len));
        swap(q1, q2); // 下一轮处理本轮生成的保留段
        len = new_len;
    }
}

// 输出轮数与每轮删除的元素。
void print_answers() {
    cout << rounds.size() << '\n';
    for (int i = 0; i < (int)rounds.size(); i++) {
        for (int j = 0; j < (int)rounds[i].size(); j++) {
            if (j) cout << ' ';
            cout << rounds[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    print_answers();

    return 0;
}
