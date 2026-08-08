#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int a[25];
int choose_idx[25];
int ans[1005];

void dfs(int pos, int last) {
    if (pos == k + 1) {
        int g = 0;
        for (int i = 1; i <= k; i++) {
            g = std::gcd(g, a[choose_idx[i]]);
        }
        ans[g]++;
        return;
    }

    for (int i = last + 1; i <= n; i++) {
        choose_idx[pos] = i;
        dfs(pos + 1, i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i <= m; i++) {
        ans[i] = 0;
    }

    dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        cout << ans[i];
        if (i == m) {
            cout << '\n';
        }
        else {
            cout << ' ';
        }
    }

    return 0;
}
