#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> on(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            on[j] ^= 1;
        }
    }

    bool first = true;
    for (int i = 1; i <= n; i++) {
        if (!on[i]) continue;
        if (!first) cout << ' ';
        cout << i;
        first = false;
    }
    cout << '\n';

    return 0;
}
