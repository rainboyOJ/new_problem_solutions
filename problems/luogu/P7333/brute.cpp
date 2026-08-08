#include <bits/stdc++.h>
using namespace std;

int n;
int a[1005], b[1005];

int ring_distance(int x, int y) {
    int d = abs(x - y);
    return min(d, n - d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    // brute.cpp：直接枚举每个 i 与所有 j，找满足 a[j] >= b[i] 的最小环距离。
    for (int i = 1; i <= n; i++) {
        int best = n + 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            if (a[j] >= b[i]) {
                best = min(best, ring_distance(i, j));
            }
        }
        if (best == n + 1) {
            best = -1;
        }
        cout << best << (i == n ? '\n' : ' ');
    }

    return 0;
}
