#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        i64 a, b, c;
        cin >> a >> b >> c;

        vector<pair<i64, i64> > all_sol;

        for (i64 x = -200; x <= 200; x++) {
            for (i64 y = -200; y <= 200; y++) {
                if (a * x + b * y == c) {
                    all_sol.push_back(make_pair(x, y));
                }
            }
        }

        if (all_sol.empty()) {
            cout << -1 << '\n';
            continue;
        }

        vector<pair<i64, i64> > pos_sol;
        i64 min_pos_x = (1LL << 60);
        i64 min_pos_y = (1LL << 60);

        for (size_t i = 0; i < all_sol.size(); i++) {
            i64 x = all_sol[i].first;
            i64 y = all_sol[i].second;
            if (x > 0 && x < min_pos_x) {
                min_pos_x = x;
            }
            if (y > 0 && y < min_pos_y) {
                min_pos_y = y;
            }
            if (x > 0 && y > 0) {
                pos_sol.push_back(all_sol[i]);
            }
        }

        if (!pos_sol.empty()) {
            sort(pos_sol.begin(), pos_sol.end());
            i64 xmin = pos_sol.front().first;
            i64 xmax = pos_sol.back().first;
            i64 ymin = (1LL << 60), ymax = 0;
            for (size_t i = 0; i < pos_sol.size(); i++) {
                ymin = min(ymin, pos_sol[i].second);
                ymax = max(ymax, pos_sol[i].second);
            }
            cout << pos_sol.size() << ' ' << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
        }
        else {
            cout << min_pos_x << ' ' << min_pos_y << '\n';
        }
    }

    return 0;
}
