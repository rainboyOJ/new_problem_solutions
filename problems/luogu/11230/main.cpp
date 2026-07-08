/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main.cpp：按人扫描序列做轮次 DP，用 reach_until 技巧批量标记可达值。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;   // 值的范围
const int MAXN = 100005;   // 人数
const int MAXE = 200005;   // 序列总长度
const int MAXR = 105;      // 最大轮数（游戏状态在此之内必收敛）

// ---------- 所有人序列的平铺存储 ----------
int seq_vals[MAXE + 5];     // 所有人的序列值拼接
int seq_start[MAXN + 5];    // seq_start[p] = 第 p 个人的序列起始下标（1-indexed）
int seq_len[MAXN + 5];      // seq_len[p] = 第 p 个人序列的长度

// reachable[r][v]：第 r 轮结束时值 v 是否可达
bool reachable[MAXR][MAXV];

// ---------- 轮次状态 ----------
// last1[v]：值 v 在上一轮的第一个生产者
// last2[v]：值 v 在上一轮的第二个生产者（同一轮中另一个不同的人）
// -1 不可达，0 第 0 轮（初始状态，任何人都可用）
int last1[MAXV], last2[MAXV];

// 判断值 v 是否可以作为本轮 person 的起始
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

        // 读入每个人的序列
        int cur = 1;
        for (int p = 1; p <= n; p++) {
            int len;
            cin >> len;
            seq_start[p] = cur;
            seq_len[p] = len;
            for (int j = 1; j <= len; j++) {
                cin >> seq_vals[cur];
                cur++;
            }
        }

        // 读入所有查询，确定最大轮数
        int query_r[MAXN], query_c[MAXN];
        int max_r = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            if (query_r[i] > max_r) max_r = query_r[i];
        }

        // 初始化第 0 轮状态
        memset(last1, -1, sizeof(last1));
        memset(last2, -1, sizeof(last2));
        memset(reachable, 0, sizeof(reachable));
        last1[1] = 0;  // 第 0 轮值 1 可达

        // ---- 逐轮 DP ----
        int next1[MAXV], next2[MAXV]; // 本轮新产生的值的第一、第二生产者

        for (int round = 1; round <= max_r; round++) {
            memset(next1, -1, sizeof(next1));
            memset(next2, -1, sizeof(next2));

            for (int p = 1; p <= n; p++) {
                int reach_until = 0;
                int base = seq_start[p] - 1;  // 转为 0-indexed
                int len = seq_len[p];

                for (int pos = 1; pos <= len; pos++) {
                    int v = seq_vals[base + pos];

                    // 位置 pos 在最远可达范围内 → v 是本轮的可达值
                    if (pos <= reach_until) {
                        if (next1[v] == -1) {
                            next1[v] = p;
                        } else if (next2[v] == -1 && next1[v] != p) {
                            next2[v] = p;
                        }
                        reachable[round][v] = true;
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
            if (c < MAXV && reachable[r][c]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }

    }

    return 0;
}
