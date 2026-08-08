#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    if (n % 2 == 1) {
        cout << -1 << '\n';
        return;
    }

    bool first = true;
    for (int p = 1 << 23; p >= 2; p >>= 1) {
        if (n >= p) {
            n -= p;
            if (!first) {
                cout << ' ';
            }
            first = false;
            cout << p;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    solve();

    return 0;
}
