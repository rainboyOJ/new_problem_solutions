/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:03
 * update_at: 2026-11-10 23:03
 */
#include <iostream>

using namespace std;

// 暴力判定单个数字是否合法
bool has_seven(int v) {
    while (v > 0) {
        if (v % 10 == 7) return true;
        v /= 10;
    }
    return false;
}

bool is_bad(int v) {
    for (int d = 1; d * d <= v; ++d) {
        if (v % d == 0) {
            if (has_seven(d) || has_seven(v / d)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int x;
        cin >> x;
        if (is_bad(x)) {
            cout << -1 << "\n";
        } else {
            int y = x + 1;
            while (is_bad(y)) {
                ++y;
            }
            cout << y << "\n";
        }
    }

    return 0;
}
