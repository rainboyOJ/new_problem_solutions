// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long ignored_n;
    int q;
    cin >> ignored_n >> q;

    deque<i64> que;

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;
            for (int v = 1; v <= x; v++) {
                que.push_back(v);
            }
        } else if (op == 2) {
            int y;
            cin >> y;
            while (y--) que.pop_front();
        } else if (op == 3) {
            int z;
            cin >> z;
            cout << que[z - 1] << '\n';
        } else {
            i64 mx = 0;
            for (int j = 0; j < (int)que.size(); j++) {
                mx = max(mx, que[j]);
            }
            cout << mx << '\n';
        }
    }

    return 0;
}
