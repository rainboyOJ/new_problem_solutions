/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:29
 * update_at: 2026-09-27 21:29
 */
// subtask_60.cpp：显式建立所有有色边，适合 sum(l) <= 2000、r <= 10。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;
const int MAXR = 105;

struct Edge {
    int from;
    int to;
    int person;
};

vector<Edge> edges;
int last1[MAXV], last2[MAXV];
int next1[MAXV], next2[MAXV];
bool answer[MAXR][MAXV];

bool can_start(int value, int person) {
    if (last1[value] == -1) return false;
    if (last1[value] == 0) return true;
    if (last1[value] != person) return true;
    return last2[value] != -1;
}

void add_state(int value, int person) {
    if (next1[value] == -1) {
        next1[value] = person;
    } else if (next1[value] != person && next2[value] == -1) {
        next2[value] = person;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k, q;
        cin >> n >> k >> q;

        edges.clear();
        for (int person = 1; person <= n; person++) {
            int len;
            cin >> len;
            vector<int> seq(len + 1);
            for (int i = 1; i <= len; i++) {
                cin >> seq[i];
            }

            // 一个合法连续子序列对应一条带有接龙人编号的边。
            for (int left = 1; left <= len; left++) {
                int right_end = min(len, left + k - 1);
                for (int right = left + 1; right <= right_end; right++) {
                    Edge e;
                    e.from = seq[left];
                    e.to = seq[right];
                    e.person = person;
                    edges.push_back(e);
                }
            }
        }

        vector<int> query_r(q + 1), query_c(q + 1);
        int max_round = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            max_round = max(max_round, query_r[i]);
        }

        memset(last1, -1, sizeof(last1));
        memset(last2, -1, sizeof(last2));
        memset(answer, 0, sizeof(answer));
        last1[1] = 0;

        for (int round = 1; round <= max_round; round++) {
            memset(next1, -1, sizeof(next1));
            memset(next2, -1, sizeof(next2));

            for (int i = 0; i < (int)edges.size(); i++) {
                Edge e = edges[i];
                if (can_start(e.from, e.person)) {
                    add_state(e.to, e.person);
                    answer[round][e.to] = true;
                }
            }

            memcpy(last1, next1, sizeof(last1));
            memcpy(last2, next2, sizeof(last2));
        }

        for (int i = 1; i <= q; i++) {
            cout << (answer[query_r[i]][query_c[i]] ? 1 : 0) << '\n';
        }
    }

    return 0;
}
