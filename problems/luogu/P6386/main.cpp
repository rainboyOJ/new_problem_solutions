#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;
int p, m, g;

// 判断某条狗在第 t 分钟时是否处于暴躁状态。
int is_angry(int angry, int calm, int t) {
    int len = angry + calm;
    int pos = t % len;
    if (pos != 0 && pos <= angry) {
        return 1;
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
