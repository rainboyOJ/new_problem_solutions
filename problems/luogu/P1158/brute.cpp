/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:45
 * update_at: 2026-11-10 23:45
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 暴力做法：枚举 r1^2 的所有可能取值，遍历核算对应的最小 r2^2
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x1, y1, x2, y2;
    if (!(cin >> x1 >> y1 >> x2 >> y2)) return 0;

    int n;
    cin >> n;

    vector<long long> d1(n), d2(n);
    vector<long long> r1_candidates;
    r1_candidates.push_back(0);

    for (int i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;
        d1[i] = (x - x1) * (x - x1) + (y - y1) * (y - y1);
        d2[i] = (x - x2) * (x - x2) + (y - y2) * (y - y2);
        r1_candidates.push_back(d1[i]);
    }

    long long ans = -1;

    for (long long r1 : r1_candidates) {
        long long r2 = 0;
        for (int i = 0; i < n; ++i) {
            if (d1[i] > r1) {
                r2 = max(r2, d2[i]);
            }
        }
        long long cost = r1 + r2;
        if (ans == -1 || cost < ans) {
            ans = cost;
        }
    }

    cout << ans << "\n";

    return 0;
}
