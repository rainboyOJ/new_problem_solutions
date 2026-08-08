#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, d;
long long p;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举答案区间，再枚举要清零的那一段。
    // 只适合小数据，用来帮助理解题意并辅助对拍。
    cin >> n >> p >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    for (int left = 1; left <= n; left++) {
        long long total = 0;
        for (int right = left; right <= n; right++) {
            total += a[right];

            long long best_zero = 0;
            for (int x = left; x <= right; x++) {
                long long sum = 0;
                for (int y = x; y <= right && y - x + 1 <= d; y++) {
                    sum += a[y];
                    if (sum > best_zero) {
                        best_zero = sum;
                    }
                }
            }

            if (total - best_zero <= p) {
                int len = right - left + 1;
                if (len > ans) {
                    ans = len;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
