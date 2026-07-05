#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200000;

int first_last[MAXV + 5], second_last[MAXV + 5];
int next_first[MAXV + 5], next_second[MAXV + 5];

bool allowed_start(int value, int person) {
    if (first_last[value] == -1) {
        return false;
    }
    if (first_last[value] == 0) {
        return true;
    }
    if (first_last[value] != person) {
        return true;
    }
    return second_last[value] != -1;
}

void add_state(int value, int person) {
    if (next_first[value] == person || next_second[value] == person) {
        return;
    }
    if (next_first[value] == -1) {
        next_first[value] = person;
    } else if (next_second[value] == -1) {
        next_second[value] = person;
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

        vector<vector<int> > seq(n + 1);
        for (int i = 1; i <= n; i++) {
            int len;
            cin >> len;
            seq[i].resize(len + 1);
            for (int j = 1; j <= len; j++) {
                cin >> seq[i][j];
            }
        }

        vector<int> query_r(q + 1), query_c(q + 1);
        int max_r = 0;
        for (int i = 1; i <= q; i++) {
            cin >> query_r[i] >> query_c[i];
            max_r = max(max_r, query_r[i]);
        }

        vector<vector<unsigned char> > reachable(max_r + 1, vector<unsigned char>(MAXV + 1, 0));

        fill(first_last, first_last + MAXV + 1, -1);
        fill(second_last, second_last + MAXV + 1, -1);
        first_last[1] = 0; // 第 0 轮结束在 1，且还没有上一位接龙的人。

        for (int round = 1; round <= max_r; round++) {
            fill(next_first, next_first + MAXV + 1, -1);
            fill(next_second, next_second + MAXV + 1, -1);

            for (int person = 1; person <= n; person++) {
                int reach_until = 0;
                int len = (int)seq[person].size() - 1;

                for (int pos = 1; pos <= len; pos++) {
                    int value = seq[person][pos];

                    // 当前位置可以作为某个接龙序列的结尾。
                    if (reach_until >= pos) {
                        add_state(value, person);
                        reachable[round][value] = 1;
                    }

                    // 当前位置可以作为下一段接龙序列的开头，结尾必须在它之后。
                    if (allowed_start(value, person)) {
                        reach_until = max(reach_until, pos + k - 1);
                    }
                }
            }

            for (int value = 1; value <= MAXV; value++) {
                first_last[value] = next_first[value];
                second_last[value] = next_second[value];
            }
        }

        for (int i = 1; i <= q; i++) {
            int r = query_r[i];
            int c = query_c[i];
            if (c <= MAXV && reachable[r][c]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}
