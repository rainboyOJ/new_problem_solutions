// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, w;
int a[MAXN];
vector<int> scores;

void solve() {
    for (int i = 1; i <= n; i++) {
        scores.push_back(a[i]);
        vector<int> b = scores;
        sort(b.begin(), b.end(), greater<int>());

        int need = i * w / 100;
        if (need < 1) {
            need = 1;
        }

        int line = b[need - 1];
        if (i > 1) {
            cout << ' ';
        }
        cout << line;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
