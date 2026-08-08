// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXM = 25;
const int MOD = 998244353;

int n;
int a[MAXN];
int m;
int typ[MAXM];
int pos_[MAXM];
int val_[MAXM];
vector<int> calls[MAXM];
int qnum;
vector<int> queries;

void exec_func(int id) {
    if (typ[id] == 1) {
        a[pos_[id]] += val_[id];
        a[pos_[id]] %= MOD;
    } else if (typ[id] == 2) {
        for (int i = 1; i <= n; i++) {
            a[i] = 1LL * a[i] * val_[id] % MOD;
        }
    } else {
        for (int v : calls[id]) {
            exec_func(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> typ[i];
        calls[i].clear();

        if (typ[i] == 1) {
            cin >> pos_[i] >> val_[i];
            val_[i] %= MOD;
        } else if (typ[i] == 2) {
            cin >> val_[i];
            val_[i] %= MOD;
        } else {
            int c;
            cin >> c;
            calls[i].resize(c);
            for (int j = 0; j < c; j++) {
                cin >> calls[i][j];
            }
        }
    }

    cin >> qnum;
    queries.resize(qnum);
    for (int i = 0; i < qnum; i++) {
        cin >> queries[i];
    }

    for (int x : queries) {
        exec_func(x);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
