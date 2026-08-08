#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int n;
long long need;
int h[MAXN];

bool enough(int cutHeight) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (h[i] > cutHeight) {
            sum += h[i] - cutHeight;
            if (sum >= need) return true;
        }
    }
    return sum >= need;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> need;
    int maxH = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        if (h[i] > maxH) maxH = h[i];
    }

    int l = 0, r = maxH;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (enough(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << l << '\n';
    return 0;
}
