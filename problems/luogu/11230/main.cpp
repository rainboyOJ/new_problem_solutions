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
const int MAXE = 200005;   // 所有值出现位置总数（序列总长度）

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
        memset(head, -1, sizeof(head)); // -1 表示链表尾
    }

    // 往值 u 加一条边：第 p 个人的第 pos 位置是 u
    void add(int u, int p, int pos) {
        e[edge_cnt] = {p, pos, head[u]};
        head[u] = edge_cnt++;
    }
} occ;  // occ[v] → 值 v 的所有出现位置

// ---------- 轮次状态 ----------
// last1[v]：值 v 在上一轮的第一个生产者（最近一轮的最近一次）
// last2[v]：值 v 在上一轮的第二个生产者（同一轮中另一个不同的人）
// -1 表示不可达，0 表示第 0 轮（初始状态）
int last1[MAXV], last2[MAXV];

// 判断值 v 是否可以作为本轮 person 的起始：
// 必须上轮有人产生 v，且本轮的人不能和上轮第一个生产者相同
// 除非上轮还有另一个不同的人也产生了 v
bool can_start(int v, int person) {
    if (last1[v] == -1) return false;     // 上轮没人产生 v
    if (last1[v] == 0) return true;       // 第 0 轮产生的 v（初始状态），任何人都可用
    if (last1[v] != person) return true;  // 上轮产生 v 的不是这个人
    return last2[v] != -1;                // 同一个人，但上上轮还有其他人产生过 v
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
        vector<vector<int>> seq(n + 1);  // seq[p]：第 p 个人的序列
        occ.reset();
        int total_pos = 0; // 统计总位置数
        for (int p = 1; p <= n; p++) {
            int len;
            cin >> len;
            seq[p].resize(len + 1);
            for (int j = 1; j <= len; j++) {
                cin >> seq[p][j];
                occ.add(seq[p][j], p, j); // 值 v → (人p, 位置j)
                total_pos++;
            }
        }

        // 读入所有查询，确定最大轮数
        vector<int> query_r(q + 1), query_c(q + 1);
        int max_r = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            if (query_r[i] > max_r) max_r = query_r[i];
        }

        // reachable[r][v]：第 r 轮结束时值 v 是否可达
        vector<vector<unsigned char>> reachable(max_r + 1,
                                                vector<unsigned char>(MAXV, 0));

        // 初始化：第 0 轮状态，值 1 可达（作为游戏起点）
        memset(last1, -1, sizeof(last1));
        memset(last2, -1, sizeof(last2));
        last1[1] = 0;  // 第 0 轮值 1 可达，且轮 0 没有具体选手

        // ---- 逐轮 DP ----
        // next1[v], next2[v]：本轮产生的值的最近两个生产者
        int next1[MAXV], next2[MAXV];

        for (int round = 1; round <= max_r; round++) {
            memset(next1, -1, sizeof(next1));
            memset(next2, -1, sizeof(next2));

            for (int p = 1; p <= n; p++) {
                int reach_until = 0; // 当前人已确定的可达最远位置
                int len = (int)seq[p].size() - 1;

                for (int pos = 1; pos <= len; pos++) {
                    int v = seq[p][pos];

                    // 位置 pos 在最远可达范围内 → v 是本轮的可达值
                    if (pos <= reach_until) {
                        // 记录 v 被第 p 个人产生（保留最近两个生产者）
                        if (next1[v] == -1) {
                            next1[v] = p;
                        } else if (next2[v] == -1 && next1[v] != p) {
                            next2[v] = p;
                        }
                        reachable[round][v] = 1;
                    }

                    // 检查当前 v 是否可以作为下一段的开头
                    if (can_start(v, p)) {
                        // 从 pos 出发，最远可达 pos + k - 1
                        reach_until = max(reach_until, pos + k - 1);
                    }
                }
            }

            // 本轮状态 → 成为下一轮的 "上一轮" 状态
            memcpy(last1, next1, sizeof(last1));  // 本轮第一生产者 → last1
            memcpy(last2, next2, sizeof(last2));  // 本轮第二生产者 → last2
        }

        // ---- 回答查询 ----
        for (int i = 1; i <= q; i++) {
            int r = query_r[i];
            int c = query_c[i];
            if (c < MAXV && reachable[r][c]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}
