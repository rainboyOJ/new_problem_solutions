#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int a[MAXN];

int query_mode(int l, int r) {
    map<int, int> cnt;
    int best_value = 0;
    int best_count = 0;

    for (int i = l; i <= r; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] > best_count ||
            (cnt[a[i]] == best_count && a[i] < best_value)) {
            best_count = cnt[a[i]];
            best_value = a[i];
        }
    }

    return best_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int flag, x, y;
        cin >> flag >> x >> y;

        if (flag == 0) {
            cout << query_mode(x, y) << '\n';
        }
        else {
            a[x] = y;
        }
    }

    return 0;
}
