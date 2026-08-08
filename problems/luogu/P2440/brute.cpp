#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
long long k;
long long wood[MAXN];

bool check(long long len) {
    long long cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += wood[i] / len;
        if (cnt >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> wood[i];
        mx = max(mx, wood[i]);
    }

    long long ans = 0;
    while (ans + 1 <= mx && check(ans + 1)) {
        ans++;
    }

    cout << ans << '\n';
    return 0;
}
