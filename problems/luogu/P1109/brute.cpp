// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int INF = 1e9;

int n;
int a[MAXN];
int l, r;
int best;

void dfs(int idx, int left_sum, int moved_out) {
    if (idx > n) {
        if (left_sum == 0) {
            best = min(best, moved_out);
        }
        return;
    }

    int remain = n - idx;
    for (int v = l; v <= r; v++) {
        int rest = left_sum - v;
        if (rest < 0) {
            continue;
        }
        if (rest < remain * l || rest > remain * r) {
            continue;
        }
        dfs(idx + 1, rest, moved_out + max(0, a[idx] - v));
    }
}

void solve() {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
    }

    if (sum < n * l || sum > n * r) {
        cout << -1 << '\n';
        return;
    }

    best = INF;
    dfs(1, sum, 0);
    cout << best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> l >> r;

    solve();

    return 0;
}
