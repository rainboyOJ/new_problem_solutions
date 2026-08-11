/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 10:33
 * update_at: 2026-08-11 10:33
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
queue<Segment> q1, q2;
int cube_pos[105];
int cube_cnt;
vector<vector<int> > rounds;

void build_cube_positions(int len) {
    cube_cnt = 0;
    for (long long x = 1; x * x * x <= len; x++) {
        cube_cnt++;
        cube_pos[cube_cnt] = (int)(x * x * x);
    }
}

void push_segment(int pos, int start, int len) {
    if (len <= 0) return;
    Segment seg;
    seg.pos = pos;
    seg.start = start;
    seg.len = len;
    q2.push(seg);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    Segment first;
    first.pos = 1;
    first.start = 1;
    first.len = n;
    q1.push(first);

    int len = n;
    while (len > 0) {
        build_cube_positions(len);
        vector<int> deleted_values;

        int ptr = 1;
        int new_len = 0;
        while (!q1.empty()) {
            Segment seg = q1.front();
            q1.pop();

            int seg_l = seg.pos;
            int seg_r = seg.pos + seg.len - 1;
            while (ptr <= cube_cnt && cube_pos[ptr] < seg_l) ptr++;

            int last_offset = 0; // 已经处理到段内 0-based 的 last_offset 之前
            while (ptr <= cube_cnt && cube_pos[ptr] <= seg_r) {
                int offset = cube_pos[ptr] - seg.pos; // 0-based 段内偏移
                deleted_values.push_back(a[seg.start + offset]);

                int keep_len = offset - last_offset;
                if (keep_len > 0) {
                    push_segment(new_len + 1, seg.start + last_offset, keep_len);
                    new_len += keep_len;
                }

                last_offset = offset + 1;
                ptr++;
            }

            int tail_len = seg.len - last_offset;
            if (tail_len > 0) {
                push_segment(new_len + 1, seg.start + last_offset, tail_len);
                new_len += tail_len;
            }
        }

        rounds.push_back(deleted_values);
        swap(q1, q2);
        len = new_len;
    }

    cout << rounds.size() << '\n';
    for (int i = 0; i < (int)rounds.size(); i++) {
        for (int j = 0; j < (int)rounds[i].size(); j++) {
            if (j) cout << ' ';
            cout << rounds[i][j];
        }
        cout << '\n';
    }
    return 0;
}
