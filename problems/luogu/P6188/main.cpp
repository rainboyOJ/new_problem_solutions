#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int t = n / 14;
    int rem = n % 14;
    if (rem == 1 || rem == 2 || rem == 5) {
        t--;
        rem += 14;
    }

    if (t < 0) {
        cout << -1 << '\n';
        return 0;
    }

    int best_a = -1, best_b = -1, best_c = -1;
    int best_cnt = -1;

    for (int a = 0; 7 * a <= rem; a++) {
        for (int b = 0; 7 * a + 4 * b <= rem; b++) {
            int left = rem - 7 * a - 4 * b;
            if (left % 3) continue;
            int c = left / 3;
            int cnt = a + b + c;
            if (cnt > best_cnt) {
                best_cnt = cnt;
                best_a = a;
                best_b = b;
                best_c = c;
            }
        }
    }

    if (best_cnt == -1) {
        cout << -1 << '\n';
        return 0;
    }

    cout << t + best_a << ' ' << t + best_b << ' ' << t + best_c << '\n';
    return 0;
}
