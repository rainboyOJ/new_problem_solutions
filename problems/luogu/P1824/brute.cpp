#include <bits/stdc++.h>
using namespace std;

int n, m;
int x[105];

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

    int ans = 0;
    for (int dist = 0; dist <= x[n] - x[1]; dist++) {
        if (canPut(dist)) ans = dist;
    }

    cout << ans << '\n';
    return 0;
}
