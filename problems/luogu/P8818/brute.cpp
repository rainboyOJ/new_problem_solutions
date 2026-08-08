#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, q;
ll a[205], b[205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        // brute.cpp：枚举小 L 选哪个 x，再枚举小 Q 选哪个 y，直接按题意做极大极小。
        ll answer = -(1LL << 60);
        for (int x = l1; x <= r1; x++) {
            ll worst = (1LL << 60);
            for (int y = l2; y <= r2; y++) {
                worst = min(worst, a[x] * b[y]);
            }
            answer = max(answer, worst);
        }
        cout << answer << '\n';
    }

    return 0;
}
