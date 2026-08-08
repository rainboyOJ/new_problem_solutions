#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护每一段铁路当前已占用的座位数。

const int MAXC = 60000 + 5;

int used[MAXC];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int city_cnt, seat_cnt, req_cnt;
    cin >> city_cnt >> seat_cnt >> req_cnt;

    for (int i = 1; i <= req_cnt; i++) {
        int o, d, n;
        cin >> o >> d >> n;

        int mx = 0;
        for (int j = o; j <= d - 1; j++) {
            mx = max(mx, used[j]);
        }

        if (mx + n <= seat_cnt) {
            cout << "T\n";
            for (int j = o; j <= d - 1; j++) {
                used[j] += n;
            }
        } else {
            cout << "N\n";
        }
    }

    return 0;
}
