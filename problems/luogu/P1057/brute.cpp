#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力搜索每一步往左传还是往右传。

int n, m;
long long ans;

int left_pos(int x) {
    if (x == 1) {
        return n;
    }
    return x - 1;
}

int right_pos(int x) {
    if (x == n) {
        return 1;
    }
    return x + 1;
}

void dfs(int step, int pos) {
    if (step == m) {
        if (pos == 1) {
            ans++;
        }
        return;
    }

    dfs(step + 1, left_pos(pos));
    dfs(step + 1, right_pos(pos));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    ans = 0;
    dfs(0, 1);

    cout << ans << '\n';
    return 0;
}
