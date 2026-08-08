#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXL = 8;
const int INF = 0x3f3f3f3f;

int n, q;
int a[MAXN];
int pw10[MAXL + 1];

void init_pow10() {
    pw10[0] = 1;
    for (int i = 1; i <= MAXL; i++) {
        pw10[i] = pw10[i - 1] * 10;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_pow10();

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= q; i++) {
        int len, need;
        int ans = INF;
        cin >> len >> need;

        // 逐本书检查后 len 位是否等于需求码。
        for (int j = 1; j <= n; j++) {
            if (a[j] % pw10[len] == need) {
                ans = min(ans, a[j]);
            }
        }

        if (ans == INF) {
            cout << -1 << '\n';
        }
        else {
            cout << ans << '\n';
        }
    }

    return 0;
}
