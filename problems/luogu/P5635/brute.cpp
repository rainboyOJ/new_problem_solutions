// brute.cpp：小数据直接模拟，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int t, p;

int brute_one(int x, int y) {
    x %= p;
    y %= p;

    set<tuple<int, int, int> > vis;
    int turn = 0;

    while (true) {
        tuple<int, int, int> state = make_tuple(x, y, turn);
        if (vis.count(state)) {
            return -1;
        }
        vis.insert(state);

        if (turn == 0) {
            x = (x + y) % p;
            if (x == 0) {
                return 1;
            }
        }
        else {
            y = (x + y) % p;
            if (y == 0) {
                return 2;
            }
        }

        turn ^= 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> p;
    while (t--) {
        int x, y;
        cin >> x >> y;
        int ret = brute_one(x, y);
        if (ret == -1) {
            cout << "error\n";
        }
        else {
            cout << ret << '\n';
        }
    }

    return 0;
}
