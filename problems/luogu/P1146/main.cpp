#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    cout << n << '\n';
    for (int step = 1; step <= n; step++) {
        for (int i = 1; i <= n; i++) {
            int bit;
            if (step & 1) {
                bit = (i <= step ? 0 : 1);
            } else {
                bit = (i <= step ? 1 : 0);
            }
            cout << bit;
        }
        cout << '\n';
    }

    return 0;
}
