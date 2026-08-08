#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int a[MAXN];

int query_mode(int l, int r) {
    int best_value = 0;
    int best_count = -1;

    // 枚举区间里的每一个数，重新数它出现了多少次。
    for (int i = l; i <= r; i++) {
        int cur_value = a[i];
        int cur_count = 0;

        for (int j = l; j <= r; j++) {
            if (a[j] == cur_value) {
                cur_count++;
            }
        }

        if (cur_count > best_count ||
            (cur_count == best_count && cur_value < best_value)) {
            best_count = cur_count;
            best_value = cur_value;
        }
    }

    return best_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int flag, x, y;
        cin >> flag >> x >> y;

        if (flag == 0) {
            cout << query_mode(x, y) << '\n';
        }
        else {
            a[x] = y;
        }
    }

    return 0;
}
