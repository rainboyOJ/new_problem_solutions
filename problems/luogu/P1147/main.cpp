#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m;
    cin >> m;

    ll left_pos = 1;
    ll right_pos = 1;
    ll sum = 1;

    while (left_pos <= m / 2) {
        if (sum < m) {
            ++right_pos;
            sum += right_pos;
        } else {
            if (sum == m && right_pos > left_pos) {
                cout << left_pos << ' ' << right_pos << '\n';
            }
            sum -= left_pos;
            ++left_pos;
        }
    }

    return 0;
}
