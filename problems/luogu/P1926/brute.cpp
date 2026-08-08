#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, r;
    cin >> n >> m >> k >> r;

    vector<int> like(n), homework_time(m), homework_score(m);
    for (int i = 0; i < n; ++i) {
        cin >> like[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> homework_time[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> homework_score[i];
    }

    int best = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        int used = 0;
        int score = 0;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                used += homework_time[i];
                score += homework_score[i];
            }
        }
        if (score < k || used > r) {
            continue;
        }

        int left_time = r - used;
        for (int sub = 0; sub < (1 << n); ++sub) {
            int cost = 0;
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (sub & (1 << i)) {
                    cost += like[i];
                    ++cnt;
                }
            }
            if (cost <= left_time) {
                best = max(best, cnt);
            }
        }
    }

    cout << best << '\n';
    return 0;
}
