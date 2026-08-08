#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
pair<int, int> bottle[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        bottle[i] = make_pair(x, i);
    }

    sort(bottle + 1, bottle + n + 1);

    int q;
    cin >> q;
    while (q--) {
        int need;
        cin >> need;

        int pos = lower_bound(bottle + 1, bottle + n + 1, make_pair(need, 0)) - bottle;
        if (pos <= n && bottle[pos].first == need) {
            cout << bottle[pos].second << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}
