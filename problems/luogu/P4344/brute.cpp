#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, m;
int a[MAXN];

int query_best_zero(int l, int r) {
    int best = 0;
    int cur = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == 0) {
            cur++;
            best = max(best, cur);
        } else {
            cur = 0;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个直接模拟：
    // 把区间真的改掉，再线性统计最长连续 0。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        a[i] = 1;
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 0) {
            int l, r;
            cin >> l >> r;
            for (int i = l; i <= r; i++) {
                a[i] = 0;
            }
        } else if (op == 1) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            int healthy_cnt = 0;
            for (int i = x1; i <= y1; i++) {
                if (a[i] == 1) {
                    healthy_cnt++;
                }
            }
            for (int i = x1; i <= y1; i++) {
                a[i] = 0;
            }
            for (int i = x2; i <= y2 && healthy_cnt > 0; i++) {
                if (a[i] == 0) {
                    a[i] = 1;
                    healthy_cnt--;
                }
            }
        } else {
            int l, r;
            cin >> l >> r;
            cout << query_best_zero(l, r) << '\n';
        }
    }

    return 0;
}
