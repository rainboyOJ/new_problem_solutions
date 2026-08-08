#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int best_min = -1;
    int best_cnt = -1;
    int ans_a = -1, ans_b = -1, ans_c = -1;

    for (int a = 0; 7 * a <= n; a++) {
        for (int b = 0; 7 * a + 4 * b <= n; b++) {
            int left = n - 7 * a - 4 * b;
            if (left % 3) continue;
            int c = left / 3;
            int mn = min(a, min(b, c));
            int cnt = a + b + c;
            if (mn > best_min || (mn == best_min && cnt > best_cnt)) {
                best_min = mn;
                best_cnt = cnt;
                ans_a = a;
                ans_b = b;
                ans_c = c;
            }
        }
    }

    if (best_min == -1) {
        cout << -1 << '\n';
    } else {
        cout << ans_a << ' ' << ans_b << ' ' << ans_c << '\n';
    }
    return 0;
}
