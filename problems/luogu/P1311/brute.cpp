#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, k, p;
int color[MAXN], costv[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for (int i = 1; i <= n; i++) {
        cin >> color[i] >> costv[i];
    }

    // brute.cpp：小数据暴力解。
    // 直接枚举所有同色的住宿方案，再检查区间里有没有消费 <= p 的咖啡店。
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (color[i] != color[j]) {
                continue;
            }

            bool ok = false;
            for (int t = i; t <= j; t++) {
                if (costv[t] <= p) {
                    ok = true;
                    break;
                }
            }

            if (ok) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
