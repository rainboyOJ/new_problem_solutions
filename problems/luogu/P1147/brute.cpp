#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m;
    cin >> m;

    for (ll left_pos = 1; left_pos <= m / 2; ++left_pos) {
        ll sum = 0;
        for (ll right_pos = left_pos; right_pos <= m; ++right_pos) {
            sum += right_pos;
            if (sum == m && right_pos > left_pos) {
                cout << left_pos << ' ' << right_pos << '\n';
            }
            if (sum >= m) {
                break;
            }
        }
    }

    return 0;
}
