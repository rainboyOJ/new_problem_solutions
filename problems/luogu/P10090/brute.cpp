#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int T;
int n, a, b;

i64 solve_one() {
    i64 ans = 0;
    for (int x = 0; x <= a; x++) {
        for (int y = 0; y <= b; y++) {
            if (x + y == 0) {
                continue;
            }
            if ((x + y) % n == 0) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> a >> b;
        cout << solve_one() << '\n';
    }

    return 0;
}
