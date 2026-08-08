// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

struct Constraint {
    int pos;
    int value;
};

int T, n, m, v;
Constraint cons[15];
int edge_a[15], edge_b[15];
long long ans;

bool check_assignment(int pos, int x[]) {
    if (pos > n) {
        for (int i = 1; i <= m; i++) {
            if (x[cons[i].pos] != cons[i].value) {
                return false;
            }
        }

        for (int i = 1; i < n; i++) {
            if (x[i] == edge_a[i] && x[i + 1] != edge_b[i]) {
                return false;
            }
        }
        return true;
    }

    for (int value = 1; value <= v; value++) {
        x[pos] = value;
        if (check_assignment(pos + 1, x)) {
            return true;
        }
    }
    return false;
}

void enumerate_edges(int id) {
    if (id == n) {
        int x[15];
        if (check_assignment(1, x)) {
            ans++;
        }
        return;
    }

    for (int a = 1; a <= v; a++) {
        for (int b = 1; b <= v; b++) {
            edge_a[id] = a;
            edge_b[id] = b;
            enumerate_edges(id + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m >> v;
        for (int i = 1; i <= m; i++) {
            cin >> cons[i].pos >> cons[i].value;
        }

        ans = 0;
        enumerate_edges(1);
        cout << ans << '\n';
    }

    return 0;
}
