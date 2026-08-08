#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

i64 n, m, k, p;
i64 x[25];
bool found = false;

void print_answer() {
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << x[i] << ' ' << (m - x[i]) << '\n';
    }
}

void dfs(int pos, i64 left) {
    if (found) {
        return;
    }

    if (pos == n + 1) {
        if (left != 0) {
            return;
        }

        i64 mx = -1;
        for (int i = 1; i <= n; i++) {
            mx = max(mx, x[i]);
        }

        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (x[i] == mx) {
                cnt++;
            }
        }

        if (cnt == p) {
            found = true;
            print_answer();
        }
        return;
    }

    for (i64 take = 0; take <= m && take <= left; take++) {
        x[pos] = take;
        dfs(pos + 1, left - take);
        if (found) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> p;
    dfs(1, k);

    if (!found) {
        cout << "NO\n";
    }

    return 0;
}
