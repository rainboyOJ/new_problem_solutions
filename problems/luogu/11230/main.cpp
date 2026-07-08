/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main.cpp：链式前向星存每个值的出现位置，按人扫描序列做轮次 DP。
// 建图：值 v → (person, pos) 边，表示 person 的序列在第 pos 位置是 v。
// 每轮：对每个人线性扫描序列，用 reach_until 技巧批量标记可达值。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;   // 值的范围
const int MAXN = 100005;   // 人数
const int MAXE = 200005;   // 序列总长度
const int MAXQ = 200005;   // 查询数

// ---------- 链式前向星：每个值存所有出现位置 ----------
struct linkList {
    struct edge {
        int person;  // 哪个人
        int pos;     // 在这个人序列的第几个位置
        int next;    // 下一个边（同值下一个出现位置）
    };
    edge e[MAXE];
    int head[MAXV], edge_cnt;

    linkList() { reset(); }

    void reset() {
        edge_cnt = 0;
        memset(head, -1, sizeof(head));
    }

    // 往值 u 加一条边：第 p 个人的第 pos 位置是 u
    void add(int u, int p, int pos) {
        e[edge_cnt] = {p, pos, head[u]};
        head[u] = edge_cnt++;
    }
} occ;  // occ[v] → 值 v 的所有出现位置

// ---------- 所有人序列的平铺存储 ----------
// seq_vals[seq_start[p] .. seq_start[p]+seq_len[p]-1] 是第 p 个人的序列（1-indexed）
int seq_vals[MAXE + 5];     // 所有人的序列值拼接
int seq_start[MAXN + 5];    // seq_start[p] = 第 p 个人的序列起始下标（从 1 开始）
int seq_len[MAXN + 5];      // seq_len[p] = 第 p 个人序列的长度

// ---------- 轮次状态 ----------
// last1[v]：值 v 在上一轮的第一个生产者（最近一轮）
// last2[v]：值 v 在上一轮的第二个生产者（同一轮中另一个不同的人）
// -1 不可达，0 表示第 0 轮（初始状态，任何人都可用）
int last1[MAXV], last2[MAXV];

// 判断值 v 是否可以作为本轮 person 的起始：
// 必须上轮有人产生 v，且本轮的人不能和上轮第一个生产者相同
// 除非上轮还有另一个不同的人也产生了 v
bool can_start(int v, int person) {
    if (last1[v] == -1) return false;
    if (last1[v] == 0) return true;
    if (last1[v] != person) return true;
    return last2[v] != -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k, q;
        cin >> n >> k >> q;

        // 读入每个人的序列，同时建图
        occ.reset();
        int cur = 1;  // seq_vals 当前写入位置（1-indexed）
        for (int p = 1; p <= n; p++) {
            int len;
            cin >> len;
            seq_start[p] = cur;
            seq_len[p] = len;
            for (int j = 1; j <= len; j++) {
                cin >> seq_vals[cur];
                occ.add(seq_vals[cur], p, j);  // 值 v → (人p, 位置j)
                cur++;
            }
        }

        // 读入所有查询，确定最大轮数
        int query_r[MAXQ + 5], query_c[MAXQ + 5];
        int max_r = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            if (query_r[i] > max_r) max_r = query_r[i];
        }

        // reachable[r * MAXV + v]：第 r 轮结束时值 v 是否可达
        unsigned char* reachable = new unsigned char[(max_r + 1) * MAXV]();

        // 初始化第 0 轮状态
        memset(last1, -1, sizeof(last1));
        memset(last2, -1, sizeof(last2));
        last1[1] = 0;  // 第 0 轮值 1 可达

        // ---- 逐轮 DP ----
        int next1[MAXV], next2[MAXV]; // 本轮新产生的值的第一、第二生产者

        for (int round = 1; round <= max_r; round++) {
            memset(next1, -1, sizeof(next1));
            memset(next2, -1, sizeof(next2));

            for (int p = 1; p <= n; p++) {
                int reach_until = 0;  // 当前人已确定的可达最远位置
                int base = seq_start[p] - 1;  // seq_vals 基址（转为 0-indexed）
                int len = seq_len[p];

                for (int pos = 1; pos <= len; pos++) {
                    int v = seq_vals[base + pos];

                    // 位置 pos 在最远可达范围内 → v 是本轮的可达值
                    if (pos <= reach_until) {
                        // 记录 v 被第 p 个人产生（保留最近两个不同生产者）
                        if (next1[v] == -1) {
                            next1[v] = p;
                        } else if (next2[v] == -1 && next1[v] != p) {
                            next2[v] = p;
                        }
                        reachable[round * MAXV + v] = 1;
                    }

                    // 检查当前 v 是否可以作为下一段的开头
                    if (can_start(v, p)) {
                        reach_until = max(reach_until, pos + k - 1);
                    }
                }
            }

            // 本轮状态 → 下一轮的 "上一轮" 状态
            memcpy(last1, next1, sizeof(last1));
            memcpy(last2, next2, sizeof(last2));
        }

        // ---- 回答查询 ----
        for (int i = 1; i <= q; i++) {
            int r = query_r[i];
            int c = query_c[i];
            if (c < MAXV && reachable[r * MAXV + c]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }

        delete[] reachable;
    }

    return 0;
}
