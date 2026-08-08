#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int adjacent_pairs = max(0, 2 * n - m);
    cout << 2 * adjacent_pairs << '\n';

    return 0;
}
