#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    set<pair<int, int>> blocked;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        blocked.insert({x, y});
    }

    vector<pair<int, int>> pts;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!blocked.count({i, j})) {
                pts.push_back({i, j});
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < (int) pts.size(); i++) {
        for (int j = i; j < (int) pts.size(); j++) {
            ans += llabs(pts[i].first - pts[j].first)
                 + llabs(pts[i].second - pts[j].second);
        }
    }

    cout << ans << '\n';
    return 0;
}
