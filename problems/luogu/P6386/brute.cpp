// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;
int p, m, g;

// 直接按分钟模拟到第 t 分钟，看这一分钟狗是否在叫。
int is_angry(int angry, int calm, int t) {
    int len = angry + calm;
    int now = 1;

    while (now <= t) {
        for (int i = 1; i <= angry && now <= t; i++, now++) {
            if (now == t) {
                return 1;
            }
        }
        for (int i = 1; i <= calm && now <= t; i++, now++) {
            if (now == t) {
                return 0;
            }
        }
    }

    return 0;
}

void print_state(int t) {
    int cnt = 0;
    cnt += is_angry(a, b, t);
    cnt += is_angry(c, d, t);

    if (cnt == 2) {
        cout << "both\n";
    }
    else if (cnt == 1) {
        cout << "one\n";
    }
    else {
        cout << "none\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> d;
    cin >> p >> m >> g;

    print_state(p);
    print_state(m);
    print_state(g);

    return 0;
}
