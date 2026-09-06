/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
// brute.cpp：小数据暴力解，逐台维护所有可达钱数，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, q;
    cin >> n >> x >> q;
    set<int> states;
    states.insert(x);
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        set<int> next_states;
        if (type == 0) {
            int a, b;
            cin >> a >> b;
            for (int value : states) {
                if (value >= a) {
                    next_states.insert(value - a + b);
                } else {
                    next_states.insert(value);
                }
            }
        } else {
            int a, b, c;
            cin >> a >> b >> c;
            for (int value : states) {
                next_states.insert(value);
                if (value >= a) {
                    next_states.insert(value - a + b);
                    next_states.insert(value - a + c);
                }
            }
        }
        states.swap(next_states);
    }
    while (q--) {
        int y;
        cin >> y;
        cout << (states.count(y) ? 1 : 0) << '\n';
    }
    return 0;
}
