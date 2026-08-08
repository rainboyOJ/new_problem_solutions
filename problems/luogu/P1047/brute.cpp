// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXL = 10010;

int l, m;
int removed[MAXL]; // removed[i] = 1 表示位置 i 的树被移走

void solve() {
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        for (int j = u; j <= v; j++) {
            removed[j] = 1;
        }
    }

    int ans = 0;
    for (int i = 0; i <= l; i++) {
        if (removed[i] == 0) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> m;
    solve();

    return 0;
}
