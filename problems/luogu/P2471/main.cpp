#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;
const int LOG = 17;

int n;
int year_arr[MAXN];
int rain_arr[MAXN];
int lg2_arr[MAXN];
int st[LOG + 1][MAXN];

void build_sparse_table() {
    lg2_arr[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg2_arr[i] = lg2_arr[i / 2] + 1;
    }

    for (int i = 1; i <= n; i++) {
        st[0][i] = rain_arr[i];
    }

    for (int k = 1; k <= LOG; k++) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; i++) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + half]);
        }
    }
}

int query_max(int l, int r) {
    if (l > r) {
        return -1;
    }
    int k = lg2_arr[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> year_arr[i] >> rain_arr[i];
    }

    build_sparse_table();

    int m;
    cin >> m;
    while (m--) {
        int y, x;
        cin >> y >> x;

        int pos_y = lower_bound(year_arr + 1, year_arr + n + 1, y) - year_arr;
        int pos_x = lower_bound(year_arr + 1, year_arr + n + 1, x) - year_arr;

        bool has_y = (pos_y <= n && year_arr[pos_y] == y);
        bool has_x = (pos_x <= n && year_arr[pos_x] == x);

        int left = pos_y;
        if (has_y) {
            left++;
        }

        int right = pos_x - 1;
        if (!has_x) {
            right = pos_x - 1;
        }

        int middle_max = query_max(left, right);

        if (has_y && has_x) {
            if (rain_arr[pos_x] > rain_arr[pos_y] || middle_max >= rain_arr[pos_x]) {
                cout << "false\n";
                continue;
            }

            // 若区间内每一年都有记录，则结论已经被完全确定。
            if (pos_x - pos_y == x - y) {
                cout << "true\n";
            } else {
                cout << "maybe\n";
            }
        }
        else if (has_y && !has_x) {
            if (middle_max >= rain_arr[pos_y]) {
                cout << "false\n";
            } else {
                cout << "maybe\n";
            }
        }
        else if (!has_y && has_x) {
            if (middle_max >= rain_arr[pos_x]) {
                cout << "false\n";
            } else {
                cout << "maybe\n";
            }
        }
        else {
            cout << "maybe\n";
        }
    }

    return 0;
}
