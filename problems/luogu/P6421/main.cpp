#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> removed(n + 1, 0);
    int cnt = 0;

    for (int p = 2; p <= n; p++) {
        if (removed[p]) continue;
        for (int x = p; x <= n; x += p) {
            if (removed[x]) continue;
            removed[x] = 1;
            cnt++;
            if (cnt == k) {
                cout << x << '\n';
                return 0;
            }
        }
    }

    return 0;
}
