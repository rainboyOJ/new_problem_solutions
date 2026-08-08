#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    bool first = true;
    for (long long i = 1; i * i <= n; i++) {
        if (!first) cout << ' ';
        cout << i * i;
        first = false;
    }
    cout << '\n';

    return 0;
}
