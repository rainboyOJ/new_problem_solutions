// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 20;

int n, m;
long long b[MAXN];      // 输入给出的最终数组
int op[MAXM], x[MAXM], y[MAXM];
long long cur[MAXN];
long long ans[MAXN];
int found;

void simulate() {
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) {
            cur[x[i]] = cur[x[i]] + cur[y[i]];
        }
        else {
            cur[x[i]] = cur[x[i]] * cur[y[i]];
        }
    }
}

void dfs(int dep) {
    if (found) {
        return;
    }
    if (dep > n) {
        long long bak[MAXN];
        for (int i = 1; i <= n; i++) {
            bak[i] = cur[i];
        }

        simulate();

        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (cur[i] != b[i]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            found = 1;
            for (int i = 1; i <= n; i++) {
                ans[i] = bak[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            cur[i] = bak[i];
        }
        return;
    }

    for (int v = 1; v <= 4; v++) {
        cur[dep] = v;
        dfs(dep + 1);
        if (found) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i] >> x[i] >> y[i];
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
