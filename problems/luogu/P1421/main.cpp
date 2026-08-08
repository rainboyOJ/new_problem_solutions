#include <bits/stdc++.h>
using namespace std;

int a, b;

void solve() {
    int money = a * 10 + b;
    cout << money / 19 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    solve();

    return 0;
}
