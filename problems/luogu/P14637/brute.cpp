// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n, m;
vector<int> sons[MAXN];
int value_a[MAXN];
int best_answer;

void collect_values(int u, set<int> &values) {
    values.insert(value_a[u]);
    for (int i = 0; i < (int)sons[u].size(); i++) {
        collect_values(sons[u][i], values);
    }
}

int calc_mex_for_node(int u) {
    set<int> values;
    collect_values(u, values);
    int mex = 0;
    while (values.count(mex)) {
        mex++;
    }
    return mex;
}

void dfs_assign(int pos) {
    if (pos > n) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += calc_mex_for_node(i);
        }
        best_answer = max(best_answer, sum);
        return;
    }

    for (int x = 0; x <= n; x++) {
        value_a[pos] = x;
        dfs_assign(pos + 1);
    }
}

void solve_case() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        sons[i].clear();
    }

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        sons[p].push_back(i);
    }

    best_answer = 0;
    dfs_assign(1);
    cout << best_answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
