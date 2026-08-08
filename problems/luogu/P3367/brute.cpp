// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> comp(n + 1);
    for (int i = 1; i <= n; i++) {
        comp[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            if (comp[x] == comp[y]) {
                continue;
            }
            int old_id = comp[y];
            int new_id = comp[x];
            for (int j = 1; j <= n; j++) {
                if (comp[j] == old_id) {
                    comp[j] = new_id;
                }
            }
        } else {
            cout << (comp[x] == comp[y] ? 'Y' : 'N') << '\n';
        }
    }

    return 0;
}
