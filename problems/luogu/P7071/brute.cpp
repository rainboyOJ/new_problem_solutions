// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> pw;
vector<int> ans;
vector<int> path;
bool found = false;

void dfs(int idx, int sum) {
    if (found) {
        return;
    }
    if (sum == n) {
        ans = path;
        found = true;
        return;
    }
    if (sum > n || idx < 0) {
        return;
    }

    path.push_back(pw[idx]);
    dfs(idx - 1, sum + pw[idx]);
    path.pop_back();
    dfs(idx - 1, sum);
}

void solve() {
    for (int x = 2; x <= n; x <<= 1) {
        pw.push_back(x);
    }

    dfs((int)pw.size() - 1, 0);
    if (!found) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    solve();

    return 0;
}
