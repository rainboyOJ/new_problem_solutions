#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n, m;
long long h[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    for (int i = 1; i <= m; i++) {
        long long x;
        cin >> x;

        // 如果第一头牛已经能吃完整根糖果棒，后面的牛不可能再吃到。
        if (x <= h[1]) {
            h[1] += x;
            continue;
        }

        long long taken = 0; // 当前已经被吃到的最高位置
        for (int j = 1; j <= n && taken < x; j++) {
            long long reach = min(h[j], x);
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
