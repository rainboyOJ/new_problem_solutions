#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> room_cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    room_cnt.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> room_cnt[i];
    }

    for (int i = 1; i <= m; i++) {
        long long d;
        int s, t;
        cin >> d >> s >> t;

        bool ok = true;
        for (int day = s; day <= t; day++) {
            if (room_cnt[day] < d) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << -1 << '\n';
            cout << i << '\n';
            return 0;
        }

        // 按题意真正扣掉这份订单占用的教室。
        for (int day = s; day <= t; day++) {
            room_cnt[day] -= d;
        }
    }

    cout << 0 << '\n';
    return 0;
}
