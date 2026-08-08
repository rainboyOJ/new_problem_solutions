// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
long long x;
map<long long, int> mp;

void solve() {
    for (int i = 1; i <= n; i++) {
        cin >> x;
        mp[x]++;
    }

    for (map<long long, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        cout << it->first << ' ' << it->second << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    solve();

    return 0;
}
