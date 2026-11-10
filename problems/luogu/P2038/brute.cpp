/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:45
 * update_at: 2026-11-11 01:45
 */

// brute.cpp：小数据验证基线
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int x, y, k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, n;
    if (!(cin >> d >> n)) return 0;
    vector<Node> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y >> pts[i].k;

    int max_val = -1, cnt = 0;
    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            int tot = 0;
            for (const auto& p : pts) {
                if (max(abs(p.x - x), abs(p.y - y)) <= d) {
                    tot += p.k;
                }
            }
            if (tot > max_val) {
                max_val = tot;
                cnt = 1;
            } else if (tot == max_val) {
                cnt++;
            }
        }
    }
    cout << cnt << " " << max_val << "\n";
    return 0;
}
