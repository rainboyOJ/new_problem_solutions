#include <bits/stdc++.h>
using namespace std;

int n;
long long need;
int h[105];

long long wood(int cutHeight) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (h[i] > cutHeight) sum += h[i] - cutHeight;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> need;
    int maxH = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        maxH = max(maxH, h[i]);
    }

    int ans = 0;
    for (int cutHeight = 0; cutHeight <= maxH; cutHeight++) {
        if (wood(cutHeight) >= need) ans = cutHeight;
    }

    cout << ans << '\n';
    return 0;
}
