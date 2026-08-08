#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200 + 5;

int n;
int year_arr[MAXN];
int rain_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> year_arr[i] >> rain_arr[i];
    }

    int m;
    cin >> m;
    while (m--) {
        int y, x;
        cin >> y >> x;

        int pos_y = -1;
        int pos_x = -1;
        for (int i = 1; i <= n; i++) {
            if (year_arr[i] == y) {
                pos_y = i;
            }
            if (year_arr[i] == x) {
                pos_x = i;
            }
        }

        bool has_y = (pos_y != -1);
        bool has_x = (pos_x != -1);

        if (has_y && has_x) {
            bool ok = true;
            if (rain_arr[pos_x] > rain_arr[pos_y]) {
                ok = false;
            }
            for (int i = 1; i <= n; i++) {
                if (y < year_arr[i] && year_arr[i] < x && rain_arr[i] >= rain_arr[pos_x]) {
                    ok = false;
                }
            }

            if (!ok) {
                cout << "false\n";
                continue;
            }

            bool full = true;
            int cur = y;
            for (int i = pos_y; i <= pos_x; i++) {
                if (year_arr[i] != cur) {
                    full = false;
                    break;
                }
                cur++;
            }
            if (cur != x + 1) {
                full = false;
            }

            if (full) {
                cout << "true\n";
            } else {
                cout << "maybe\n";
            }
        }
        else if (has_y && !has_x) {
            bool bad = false;
            for (int i = 1; i <= n; i++) {
                if (y < year_arr[i] && year_arr[i] < x && rain_arr[i] >= rain_arr[pos_y]) {
                    bad = true;
                }
            }

            if (bad) {
                cout << "false\n";
            } else {
                cout << "maybe\n";
            }
        }
        else if (!has_y && has_x) {
            bool bad = false;
            for (int i = 1; i <= n; i++) {
                if (y < year_arr[i] && year_arr[i] < x && rain_arr[i] >= rain_arr[pos_x]) {
                    bad = true;
                }
            }

            if (bad) {
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
