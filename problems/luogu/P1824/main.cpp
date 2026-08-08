#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
int n, m;
int x[MAXN];

bool canPut(int dist) {
    int cnt = 1;
    int last = x[1];
    for (int i = 2; i <= n; i++) {
        if (x[i] - last >= dist) {
            cnt++;
            last = x[i];
            if (cnt >= m) return true;
        }
    }
    return cnt >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i];

    sort(x + 1, x + n + 1);

    int l = 0, r = x[n] - x[1];
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (canPut(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << l << '\n';
    return 0;
}
