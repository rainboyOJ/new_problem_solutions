#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
long long h[MAXN];
long long candy[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> candy[i];
    }

    // 朴素模拟：每根糖果棒都让所有奶牛按顺序尝试一次。
    for (int i = 1; i <= m; i++) {
        long long taken = 0;
        for (int j = 1; j <= n; j++) {
            long long reach = min(h[j], candy[i]);
            if (reach > taken) {
                h[j] += reach - taken;
                taken = reach;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << h[i] << '\n';
    }
    return 0;
}
