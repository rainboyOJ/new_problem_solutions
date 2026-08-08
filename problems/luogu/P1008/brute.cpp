// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int p[10];
int vis[10];

int get_num(int l, int r) {
    int x = 0;
    for (int i = l; i <= r; i++) {
        x = x * 10 + p[i];
    }
    return x;
}

void dfs(int dep) {
    if (dep == 10) {
        int a = get_num(1, 3);
        int b = get_num(4, 6);
        int c = get_num(7, 9);

        if (a * 2 == b && a * 3 == c) {
            cout << a << ' ' << b << ' ' << c << '\n';
        }
        return;
    }

    for (int d = 1; d <= 9; d++) {
        if (vis[d]) {
            continue;
        }
        vis[d] = 1;
        p[dep] = d;
        dfs(dep + 1);
        vis[d] = 0;
    }
}

void solve() {
    dfs(1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
