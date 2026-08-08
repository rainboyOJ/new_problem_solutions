#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> alive(n + 1, 1);
    alive[0] = alive[1] = 0;

    int cnt = 0;
    while (true) {
        int p = 0;
        for (int i = 2; i <= n; i++) {
            if (alive[i]) {
                p = i;
                break;
            }
        }

        for (int x = p; x <= n; x += p) {
            if (!alive[x]) continue;
            alive[x] = 0;
            cnt++;
            if (cnt == k) {
                cout << x << '\n';
                return 0;
            }
        }
    }

    return 0;
}
