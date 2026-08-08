// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];

void solve() {
    vector<int> diff;

    for (int i = 1; i < n; i++) {
        diff.push_back(abs(a[i + 1] - a[i]));
    }

    sort(diff.begin(), diff.end());

    for (int i = 1; i <= n - 1; i++) {
        if (diff[i - 1] != i) {
            cout << "Not jolly\n";
            return;
        }
    }

    cout << "Jolly\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
