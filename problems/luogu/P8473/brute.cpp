#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护当前活跃线段集合，然后暴力模拟染色闭包。

const int MAXN = 105;
const int MAXQ = 105;

int n, q;
int pos_arr[MAXN];
int color_arr[MAXN];
int add_l[MAXQ], add_r[MAXQ];
int add_ok[MAXQ];
int cnt_seg[MAXN][MAXN];

bool simulate() {
    int black[MAXN];
    for (int i = 1; i <= n; i++) {
        black[i] = color_arr[i];
    }

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                if (cnt_seg[i][j] == 0) {
                    continue;
                }
                if (black[i] == 0 || black[j] == 0) {
                    continue;
                }
                for (int k = i; k <= j; k++) {
                    if (black[k] == 0) {
                        black[k] = 1;
                        changed = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (black[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> pos_arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> color_arr[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cnt_seg[i][j] = 0;
        }
    }

    cout << (simulate() ? "Yes" : "No") << '\n';

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        add_ok[i] = 0;

        if (op == 1) {
            int l, r;
            cin >> l >> r;

            int L = lower_bound(pos_arr + 1, pos_arr + n + 1, l) - pos_arr;
            int R = (int)(upper_bound(pos_arr + 1, pos_arr + n + 1, r) - pos_arr) - 1;

            if (L <= R) {
                add_ok[i] = 1;
                add_l[i] = L;
                add_r[i] = R;
                for (int x = L; x <= R; x++) {
                    for (int y = x; y <= R; y++) {
                        cnt_seg[x][y]++;
                    }
                }
            }
        } else {
            int x;
            cin >> x;
            if (add_ok[x]) {
                for (int i1 = add_l[x]; i1 <= add_r[x]; i1++) {
                    for (int j1 = i1; j1 <= add_r[x]; j1++) {
                        cnt_seg[i1][j1]--;
                    }
                }
            }
        }

        cout << (simulate() ? "Yes" : "No") << '\n';
    }

    return 0;
}
