// brute.cpp：小数据暴力解，显式枚举每个人词库产生的所有有色边。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int person;
};

const int MAXV = 205;

vector<Edge> edges[MAXV];
bool cur[MAXV][15], nxt[MAXV][15];
bool answer[105][MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k, q;
        cin >> n >> k >> q;

        for (int i = 0; i < MAXV; i++) {
            edges[i].clear();
            for (int p = 0; p < 15; p++) {
                cur[i][p] = false;
                nxt[i][p] = false;
            }
            for (int r = 0; r < 105; r++) {
                answer[r][i] = false;
            }
        }

        vector<vector<int> > seq(n + 1);
        for (int p = 1; p <= n; p++) {
            int len;
            cin >> len;
            seq[p].resize(len + 1);
            for (int i = 1; i <= len; i++) {
                cin >> seq[p][i];
            }
            for (int l = 1; l <= len; l++) {
                for (int r = l + 1; r <= len && r <= l + k - 1; r++) {
                    int from = seq[p][l];
                    int to = seq[p][r];
                    if (from < MAXV && to < MAXV) {
                        edges[from].push_back({to, p});
                    }
                }
            }
        }

        vector<int> query_r(q + 1), query_c(q + 1);
        int max_r = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            max_r = max(max_r, query_r[i]);
        }

        cur[1][0] = true;
        for (int round = 1; round <= max_r; round++) {
            for (int v = 0; v < MAXV; v++) {
                for (int p = 0; p < 15; p++) {
                    nxt[v][p] = false;
                }
            }

            for (int from = 1; from < MAXV; from++) {
                for (int i = 0; i < (int)edges[from].size(); i++) {
                    int to = edges[from][i].to;
                    int person = edges[from][i].person;
                    bool ok = false;
                    for (int last = 0; last <= n; last++) {
                        if (cur[from][last] && last != person) {
                            ok = true;
                        }
                    }
                    if (ok) {
                        nxt[to][person] = true;
                        answer[round][to] = true;
                    }
                }
            }

            for (int v = 0; v < MAXV; v++) {
                for (int p = 0; p < 15; p++) {
                    cur[v][p] = nxt[v][p];
                }
            }
        }

        for (int i = 1; i <= q; i++) {
            int r = query_r[i];
            int c = query_c[i];
            if (c < MAXV && answer[r][c]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}
