#include <bits/stdc++.h>
using namespace std;

int used[10];

int check(int x) {
    memset(used, 0, sizeof(used));

    for (int t = x; t <= x * 3; t += x) {
        int cur = t;
        while (cur > 0) {
            int d = cur % 10;
            if (d == 0 || used[d]) {
                return 0;
            }
            used[d] = 1;
            cur /= 10;
        }
    }

    for (int d = 1; d <= 9; d++) {
        if (used[d] == 0) {
            return 0;
        }
    }
    return 1;
}

void solve() {
    for (int x = 123; x <= 329; x++) {
        if (check(x)) {
            cout << x << ' ' << x * 2 << ' ' << x * 3 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
