#include <bits/stdc++.h>
using namespace std;

const int maxn = 80000 + 5;

int n;
long long h[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (h[j] >= h[i]) {
                break;
            }
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
